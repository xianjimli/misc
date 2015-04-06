#include <stdio.h>
#include <string.h>
#include <asm-common.h>
#include <sys/select.h>
#include <rapi_device_default.h>
#include <rapi_device_connection_device.h>
#include <rrac_device_default.h>
#include <rrac_device_connection_cmd.h>
#include <rrac_device_connection_data.h>
#include <dlfcn.h>

typedef struct _AsmDevice
{
	AsmConnection*  device_connection;
	AsmConnection*  session_connections[RAPI_MAX_SESSION_NR];
	AsmConnection*  rrac_connections[RAPI_MAX_SESSION_NR * 2];

	RracDevice*     rrac_device;
	RapiDevice*     rapi_device;

	fd_set readset;
	
	char* host;
	void* sync_device_handle;
}AsmDevice;

static AsmRet  asm_device_save_session_cmd_data(AsmDevice* thiz, AsmConnection* session, AsmConnection* cmd, AsmConnection* data)
{
	int i = 0;
	asm_return_val_if_fail(thiz != NULL && session != NULL, ASM_RET_FAIL);
	
	for(i = 0; i < RAPI_MAX_SESSION_NR; i++)
	{
		if(thiz->session_connections[i] == session)
		{
			thiz->rrac_connections[2*i] = cmd;
			thiz->rrac_connections[2*i + 1] = data;

			return ASM_RET_OK;
		}
	}

	return ASM_RET_FAIL;
}

static AsmRet asm_device_on_cmd_data_broken(void* ctx, void* connection)
{
	int i = 0;
	AsmDevice* thiz = (AsmDevice*)ctx;

	for(i = 0; i < 2 * RAPI_MAX_SESSION_NR; i++)
	{
		if(thiz->rrac_connections[i] == connection)
		{
			thiz->rrac_connections[i] = NULL;
			
			return ASM_RET_OK;
		}
	}

	return ASM_RET_FAIL;
}

static AsmRet asm_device_on_device_broken(void* ctx, void* connection)
{
	AsmDevice* thiz = (AsmDevice*)ctx;
	
	thiz->device_connection = NULL;

	return ASM_RET_OK;
}

static AsmRet asm_device_on_session_command(void* ctx, AsmConnection* session, unsigned int cmd, int before, AsmRet result)
{
	AsmDevice* thiz = (AsmDevice*)ctx;
	RracDevice* device = thiz->rrac_device;

	if(cmd == RAPI_COMMAND_SYSTEM_START_REPLICATION && before)
	{
		AsmConnection* cmd_connection  = rrac_device_connection_cmd_create(thiz->host, RRAC_PORT, device);
		AsmConnection* data_connection = rrac_device_connection_data_create(thiz->host, RRAC_PORT, device);

		rrac_device_connection_cmd_set_data_connection(cmd_connection, data_connection);
		rrac_device_connection_data_set_cmd_connection(data_connection, cmd_connection);

		asm_connection_hook_destroy(cmd_connection, (AsmHookFunc)asm_device_on_cmd_data_broken, thiz);
		asm_connection_hook_destroy(data_connection, (AsmHookFunc)asm_device_on_cmd_data_broken, thiz);

		asm_device_save_session_cmd_data(thiz, session, cmd_connection, data_connection);
	}

	return ASM_RET_OK;
}

static AsmRet asm_device_on_sessions_changed(void* ctx, void* device_connection)
{
	AsmDevice* thiz = (AsmDevice*)ctx;
	
	thiz->session_connections;
	rapi_device_connection_device_get_connections(device_connection, thiz->session_connections, RAPI_MAX_SESSION_NR);

	size_t i = 0;
	for(i = 0; i < RAPI_MAX_SESSION_NR; i++)
	{
		if(thiz->session_connections[i] != NULL)
		{
			rapi_device_connection_hook_command(thiz->session_connections[i], asm_device_on_session_command, thiz);
		}
	}

	return ASM_RET_OK;
}

static int asm_device_select_connections(AsmDevice* thiz, AsmConnection** connections, size_t nr, int max_fd)
{
	size_t i = 0;
	fd_set* readset = &(thiz->readset);

	for(i = 0; i < nr; i++)
	{
		if(connections[i] != NULL)
		{
			int sock_no = asm_connection_get_fd(connections[i]);
			if(ASM_IS_SOCKET_VALID(sock_no))
			{
				FD_SET(sock_no, readset);
				if(max_fd < sock_no)
				{
					max_fd = sock_no;
				}
			}
		}
	}

	return max_fd;
}

static AsmRet asm_device_process_connections_event(AsmDevice* thiz, AsmConnection** connections, size_t nr)
{
	size_t i = 0;
	fd_set* readset = &(thiz->readset);

	for(i = 0; i < nr; i++)
	{
		if(connections[i] != NULL)
		{
			if(FD_ISSET(asm_connection_get_fd(connections[i]), readset))
			{
				asm_connection_process_event(connections[i]);
			}
		}
	}

	return ASM_RET_OK;
}

AsmRet asm_device_process_events(AsmDevice* thiz)
{
	size_t i = 0;
	int max_fd = -2;
	FD_ZERO(&(thiz->readset));

	max_fd = asm_device_select_connections(thiz, &(thiz->device_connection), 1, max_fd);
	max_fd = asm_device_select_connections(thiz, thiz->session_connections, RAPI_MAX_SESSION_NR, max_fd);
	max_fd = asm_device_select_connections(thiz, thiz->rrac_connections, RAPI_MAX_SESSION_NR * 2, max_fd);
	
	if(max_fd > 0)
	{
		struct timeval tv = {1000, 1000};
		int result = select(max_fd + 1, &(thiz->readset), NULL, NULL, &tv);
		if(result > 0)
		{
			asm_device_process_connections_event(thiz, &(thiz->device_connection), 1);
			asm_device_process_connections_event(thiz, thiz->session_connections, RAPI_MAX_SESSION_NR);
			asm_device_process_connections_event(thiz, thiz->rrac_connections, RAPI_MAX_SESSION_NR * 2);
			
			return ASM_RET_OK;
		}
	}

	return ASM_RET_FAIL;
}

AsmDevice* asm_device_create(RapiDevice* rapi_device, RracDevice* rrac_device, void* sync_device_handle, const char* host)
{
	AsmDevice* thiz = ASM_ALLOC(AsmDevice, 0);
	
	thiz->host = strdup(host);
	thiz->rapi_device = rapi_device;
	thiz->rrac_device =  rrac_device;
	thiz->sync_device_handle = sync_device_handle;

	thiz->device_connection      = rapi_device_connection_device_create(thiz->rapi_device, thiz->host, RAPI_PORT);

	rapi_device_connection_device_hook_connection_change(thiz->device_connection, asm_device_on_sessions_changed, thiz);
	asm_connection_hook_destroy(thiz->device_connection, (AsmHookFunc)asm_device_on_device_broken, thiz);

	return thiz;
}

static void asm_device_destroy(AsmDevice* thiz)
{
	if(thiz != NULL)
	{
		if(thiz->sync_device_handle != NULL)
		{
			dlclose(thiz->sync_device_handle);	
			thiz->sync_device_handle = NULL;
		}

		ASM_FREE(thiz->host);
		rapi_device_destroy(thiz->rapi_device, NULL);
		rrac_device_destroy(thiz->rrac_device, NULL);

		ASM_FREE(thiz);
	}

	return;
}

typedef void* (*SyncDeviceCreateFunc)(void);

static void* load_device(void* handle, const char* type, const char* name)
{
	char func_name[64] = {0};
	asm_return_val_if_fail(handle != NULL && type != NULL && name != NULL, NULL);

	snprintf(func_name, sizeof(func_name), "%s_device_%s_create", type, name);
	SyncDeviceCreateFunc create = (SyncDeviceCreateFunc)dlsym(handle, func_name);

	if(create != NULL)
	{
		printf("%s: load %s ok.\n", __func__, func_name);

		return create();
	}
	else
	{
		printf("%s: load %s failed(%s)\n", __func__, func_name, dlerror());
	}

	return NULL;
}

static void* load_devices(const char* device_name, RapiDevice** rapi_device, RracDevice** rrac_device)
{
	asm_return_val_if_fail(device_name != NULL && rapi_device != NULL && rrac_device != NULL, NULL);

	char module[260] = {0};
	snprintf(module, sizeof(module), SYNCD_DEVICE_SO, device_name);
	void* sync_device_handle = dlopen(module, RTLD_LAZY);
	if(sync_device_handle != NULL)
	{
		*rapi_device = load_device(sync_device_handle, "rapi", device_name);
		*rrac_device = load_device(sync_device_handle, "rrac", device_name);

		assert(*rapi_device != NULL && *rrac_device  != NULL);
		
		printf("%s: load %s ok.\n", __func__, module);

		return sync_device_handle;
	}
	else
	{
		printf("%s: load %s failed(%s)\n", __func__, module, dlerror());
	}

	return NULL;
}

int main(int argc, char* argv[])
{
	RapiDevice* rapi_device = NULL;
	RracDevice* rrac_device = NULL;

	if(argc != 3)
	{
		printf("usage: %s [host(localhost)] [device(demo)]\n", argv[0]);
		exit(0);
	}

	const char* host = argv[1];
	const char* device_name = argv[2];

	void* handle = load_devices(device_name, &rapi_device, &rrac_device);
	asm_return_val_if_fail(rapi_device != NULL && rrac_device != NULL, 1);

	AsmDevice* thiz = asm_device_create(rapi_device, rrac_device, handle, host);

	while(asm_device_process_events(thiz) == ASM_RET_OK)
	{
	}

	asm_device_destroy(thiz);

	return 0;
}

