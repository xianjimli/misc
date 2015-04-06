/*
 * File:    rapi_host_connection_listen.c
 * Author:  Li XianJing <lixianjing@broncho.org>
 * Brief:   
 *
 * Copyright (c) 2008 topwise, Inc.
 *
 * Licensed under the Academic Free License version 2.1
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * History:
 * ================================================================
 * 2008-01-28 Li XianJing <lixianjing@topwisesz.com> created
 *
 */

#include <asm-server-socket.h>
#include <asm-input-buffer.h>
#include <asm-output-buffer.h>
#include <rapi_host_lib.h>
#include <rapi_host_connection_listen.h>
#include <rapi_host_connection_device.h>

static inline void 
call_device_change_hook(RapiHostHookDeviceChangedFunc hook, void* ctx, AsmConnection* device_connection, int action)
{
	if(hook != NULL)
	{
		hook(ctx, device_connection, action);
	}

	return;
}

typedef struct _PrivInfo
{
	AsmServer* server;

	AsmHookFunc on_destroy;
	void* on_destroy_ctx;
	
	RapiHostHookDeviceChangedFunc on_device_changed;
	void* on_device_changed_ctx;

	AsmConnection* device_connections[RAPI_MAX_DEVICES];
}PrivInfo;

static int     rapi_host_connection_listen_get_fd(AsmConnection* thiz)
{
	asm_return_val_if_fail(thiz != NULL, -1);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	return asm_server_get_fd(priv->server);
}

static int    rapi_host_connection_listen_get_free_slot(AsmConnection* thiz)
{
	int i = 0;
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	
	for(i = 0; i < RAPI_MAX_DEVICES; i++)
	{
		if(priv->device_connections[i] == NULL)
		{
			return i;
		}
	}

	return -1;
}

static int    rapi_host_connection_listen_get_device(AsmConnection* thiz, int sock_no)
{
	int i = 0;
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	
	for(i = 0; i < RAPI_MAX_DEVICES; i++)
	{
		if(priv->device_connections[i] != NULL)
		{
			if(socket_is_from_same_client(asm_connection_get_fd(priv->device_connections[i]), sock_no))
			{
				return i;
			}
		}
	}

	return -1;
}

static AsmRet rapi_host_connection_listen_process_event(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	
	AsmStream* stream = NULL;

	if(asm_server_accept(priv->server, &stream) == ASM_RET_OK)
	{
		int index = rapi_host_connection_listen_get_device(thiz, asm_stream_get_fd(stream));
		if(index >= 0)
		{
			/*if device exist, it must be session connection.*/
			rapi_host_connection_device_on_new_session(priv->device_connections[index], stream);
		}
		else
		{
			index = rapi_host_connection_listen_get_free_slot(thiz);
			if(index >= 0)
			{
				priv->device_connections[index] = rapi_host_connection_device_create(stream);
				call_device_change_hook(priv->on_device_changed, priv->on_device_changed_ctx, priv->device_connections[index], 1);
			}
			else
			{
				printf("%s:%d exceed max devices.\n", __func__, __LINE__);
				asm_stream_destroy(stream);
			}
		}

		ret = ASM_RET_OK;
	}

	return ret;
}

static AsmRet rapi_host_connection_listen_destroy(AsmConnection* thiz)
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	if(priv->on_destroy != NULL)
	{
		priv->on_destroy(priv->on_destroy_ctx, thiz);
	}

	size_t i = 0;
	for(i = 0; i < RAPI_MAX_DEVICES; i++)
	{
		if(priv->device_connections[i] != NULL)
		{
			call_device_change_hook(priv->on_device_changed, priv->on_device_changed_ctx, priv->device_connections[i], 0);
			asm_connection_destroy(priv->device_connections[i]);
			priv->device_connections[i] = NULL;
		}
	}

	asm_server_destroy(priv->server);
	ASM_FREE(thiz);

	return ASM_RET_OK;
}

AsmRet rapi_host_connection_listen_hook_destroy(AsmConnection* thiz, AsmHookFunc on_destroy, void* on_destroy_ctx)
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	
	priv->on_destroy = on_destroy;
	priv->on_destroy_ctx = on_destroy_ctx;

	return ASM_RET_OK;
}

AsmRet         rapi_host_connection_listen_get_devices(AsmConnection* thiz, AsmConnection** device_connections, size_t nr)
{
	asm_return_val_if_fail(thiz != NULL && device_connections != NULL && nr > 0, ASM_RET_FAIL);

	PrivInfo* priv = (PrivInfo*)thiz->priv;

	size_t i = 0;
	size_t j = 0;

	for(i = 0, j= 0; i < RAPI_MAX_DEVICES && j < nr; i++)
	{
		if(priv->device_connections[i] != NULL)
		{
			device_connections[j] = priv->device_connections[i];
			j++;
		}
	}

	for(; j < nr; j++)
	{
		device_connections[j] = NULL;
	}

	return ASM_RET_OK;
}

AsmRet         rapi_host_connection_listen_hook_device_changed(AsmConnection* thiz, RapiHostHookDeviceChangedFunc hook, void* hook_ctx)
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	priv->on_device_changed = hook;
	priv->on_device_changed_ctx = hook_ctx;

	return ASM_RET_OK;
}

AsmConnection* rapi_host_connection_listen_create(int port)
{
	AsmServer* server = asm_server_socket_create(NULL, port);

	asm_return_val_if_fail(server != NULL, NULL);

	AsmConnection* thiz = ASM_ALLOC(AsmConnection, sizeof(PrivInfo));
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	priv->server = server;

	thiz->get_fd    = rapi_host_connection_listen_get_fd;
	thiz->process_event = rapi_host_connection_listen_process_event;
	thiz->hook_destroy  = rapi_host_connection_listen_hook_destroy;
	thiz->destroy       = rapi_host_connection_listen_destroy;

	return thiz;
}

