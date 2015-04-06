/*
 * File:    rapi_host_test.c
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

#include <string.h>
#include <asm-wstr.h>
#include <rapi_host.h>
#include <rapi_test_data.h>

static void test_create_file(RapiHost* thiz, WStr* file_name, unsigned int create_flags, char* file_data_w, int test_write, int call_delete)
{
	unsigned int last_error = 0;
	unsigned int return_value = 0;
	char* file_data_r = NULL;

	assert(rapi_host_create_file(thiz, &last_error, &return_value, 
		file_name, RAPI_SHARE_MODE_GENERIC_WRITE, 0, 
		create_flags, RAPI_FILE_ATTRIBUTE_NORMAL, 0) == ASM_RET_OK);
	assert(return_value != 0);
	unsigned int handle = return_value;
	unsigned int bytes_written = 0;
	unsigned int ret_high = 0;
	unsigned int ret_length = 0;
	if(test_write)
	{
		assert(rapi_host_write_file(thiz, &last_error, &return_value, 
			handle, strlen(file_data_w), file_data_w, &bytes_written) == ASM_RET_OK);
		assert(bytes_written == strlen(file_data_w));

		assert(rapi_host_seek(thiz, &last_error, &return_value,
			handle, 0, 0, 0, RAPI_FILE_SEEK_TYPE_BEGIN, &ret_high) == ASM_RET_OK);
	}
	assert(rapi_host_read_file(thiz, &last_error, &return_value,
		handle, strlen(file_data_w), &ret_length, (void**)&file_data_r) == ASM_RET_OK);
	assert(ret_length == strlen(file_data_w));
	assert(strncmp(file_data_w, file_data_r, strlen(file_data_w)) == 0);
	ASM_FREE(file_data_r);
	assert(rapi_host_close_handle(thiz, &last_error, &return_value, handle) == ASM_RET_OK);
	if(call_delete)
	{
		assert(rapi_host_delete_file(thiz, &last_error, &return_value, file_name) == ASM_RET_OK);
	}

	return;
}

static void test_fileman_get_special(RapiHost* thiz)
{
	WStr* str = NULL;
	WStr* str1 = NULL;
	size_t i = 0;
	unsigned int last_error = 0;
	unsigned int return_value = 0;
	unsigned int folders_type[]=
		{
			RAPI_CSIDL_PROGRAMS,
			RAPI_CSIDL_PERSONAL,
			RAPI_CSIDL_FAVORITES_GRYPHON,
			RAPI_CSIDL_STARTUP,
			RAPI_CSIDL_RECENT,
			RAPI_CSIDL_STARTMENU,
			RAPI_CSIDL_DESKTOPDIRECTORY,
			RAPI_CSIDL_FONTS,
			RAPI_CSIDL_FAVORITES,
			0
		};
	const char* folders[] =
		{
			TEST_DATA_SPECIAL_FOLDER_PROGRAMS,
			TEST_DATA_SPECIAL_FOLDER_PERSONAL,
			TEST_DATA_SPECIAL_FOLDER_FAVORITES_GRYPHON,
			TEST_DATA_SPECIAL_FOLDER_STARTUP,
			TEST_DATA_SPECIAL_FOLDER_RECENT,
			TEST_DATA_SPECIAL_FOLDER_STARTMENU,
			TEST_DATA_SPECIAL_FOLDER_DESKTOPDIRECTORY,
			TEST_DATA_SPECIAL_FOLDER_FONTS,
			TEST_DATA_SPECIAL_FOLDER_FAVORITES,
			NULL
		};

	for(i = 0; folders[i] != NULL; i++)
	{
		assert(rapi_host_get_special_folder(thiz, &last_error, &return_value, folders_type[i], 260, &str) == ASM_RET_OK);
		str1 = wstr_dup_from_ascii(folders[i]);
		assert(wstr_compare(str1, str) == 0);
		ASM_FREE(str);
		ASM_FREE(str1);
	}

	return;
}

static void test_fileman_directroy(RapiHost* thiz)
{
	unsigned int last_error = 0;
	unsigned int return_value = 0;
	WStr* path = wstr_dup_from_ascii("directory");

	assert(rapi_host_create_directory(thiz, &last_error, &return_value, path) == ASM_RET_OK);
	assert(return_value);
	assert(rapi_host_create_directory(thiz, &last_error, &return_value, path) == ASM_RET_OK);
	assert(!return_value);
	assert(rapi_host_remove_directory(thiz, &last_error, &return_value, path) == ASM_RET_OK);
	assert(return_value);
	assert(rapi_host_remove_directory(thiz, &last_error, &return_value, path) == ASM_RET_OK);
	assert(!return_value);

	ASM_FREE(path);

	return;
}

static void test_fileman(RapiHost* thiz)
{
	char* file_data_w = "1234567890";
	char* file_data_r = NULL;
	WStr* file_src = NULL;
	WStr* file_dst = NULL;
	unsigned int last_error = 0;
	unsigned int return_value = 0;

	test_fileman_get_special(thiz);

	file_src = wstr_dup_from_ascii("test.src");
	file_dst = wstr_dup_from_ascii("test.dst");
	test_create_file(thiz, file_src, RAPI_CREATION_DISPOSITION_CREATE_ALWAYS, file_data_w, 1, 1);
	test_create_file(thiz, file_src, RAPI_CREATION_DISPOSITION_CREATE_ALWAYS, file_data_w, 1, 0);

	assert(rapi_host_copy_file(thiz, &last_error, &return_value, file_src, file_dst, 1) == ASM_RET_OK);
	assert(return_value);
	test_create_file(thiz, file_src, RAPI_CREATION_DISPOSITION_OPEN_EXISTING, file_data_w, 0, 1);
	assert(rapi_host_move_file(thiz, &last_error, &return_value, file_dst, file_src) == ASM_RET_OK);
	assert(return_value);
	
	assert(rapi_host_move_file(thiz, &last_error, &return_value, file_dst, file_src) == ASM_RET_OK);
	assert(!return_value);

	test_fileman_directroy(thiz);

	ASM_FREE(file_src);
	ASM_FREE(file_dst);

	return;
}

static void test_procman(RapiHost* thiz)
{
	unsigned int last_error = 0;
	unsigned int return_value = 0;
	WStr* app_name = wstr_dup_from_ascii("ls");
	WStr* cmd_line = wstr_dup_from_ascii("./");
	RapiProcessInfo* process_info = NULL;

	assert(rapi_host_create_process(thiz, &last_error, &return_value, 
		app_name, cmd_line, 0, 0, 0, 0, 0, 0, 0, &process_info) == ASM_RET_OK);
	assert(process_info != NULL && process_info->pid > 0);

	assert(rapi_host_close_handle(thiz, &last_error, &return_value, process_info->process_handle) == ASM_RET_OK);
	assert(rapi_host_close_handle(thiz, &last_error, &return_value, process_info->thread_handle) == ASM_RET_OK);

	ASM_FREE(app_name);
	ASM_FREE(cmd_line);
	ASM_FREE(process_info);

	return;
}

static void test_system(RapiHost* thiz)
{
	unsigned int last_error = 0;
	unsigned int return_value = 0;

	RapiVersionInfo* version_from_device = NULL;
	RapiVersionInfo version_from_test = {0};
	assert(rapi_test_data_get_version_info(&version_from_test) == ASM_RET_OK);
	assert(rapi_host_get_version_info(thiz, &last_error, &return_value, &version_from_device) == ASM_RET_OK);
	assert(last_error == RAPI_SUCCESS && return_value);
	assert(version_from_device != NULL);
	assert(memcmp(version_from_device, &version_from_test, sizeof(RapiVersionInfo)) == 0);
	ASM_FREE(version_from_device);

	RapiSystemInfo* system_info_from_device = NULL;
	RapiSystemInfo* system_info_from_test = NULL;
	rapi_test_data_get_system_info(&system_info_from_test);
	assert(rapi_host_get_system_info(thiz, &last_error, &return_value, 
		system_info_from_test, &system_info_from_device) == ASM_RET_OK);
	assert(memcmp(system_info_from_device, system_info_from_test, sizeof(RapiSystemInfo)) == 0);
	ASM_FREE(system_info_from_device);
	ASM_FREE(system_info_from_test);

	RapiSystemPowerStatus* power_status_from_device = NULL;
	RapiSystemPowerStatus* power_status_from_test = NULL;
	rapi_test_data_get_power_status(&power_status_from_test);
	assert(rapi_host_get_power_status(thiz, &last_error, &return_value,
		1, &power_status_from_device) == ASM_RET_OK);
	assert(memcmp(power_status_from_device, power_status_from_test, sizeof(RapiSystemPowerStatus)) == 0);
	ASM_FREE(power_status_from_device);
	ASM_FREE(power_status_from_test);

	WStr* sync_param = wstr_dup_from_ascii("rapi_host_start_sync");
	assert(rapi_host_start_replication(thiz, &last_error, &return_value) == ASM_RET_OK);
	assert(rapi_host_start_sync(thiz, &last_error, &return_value, sync_param) == ASM_RET_OK);
	assert(rapi_host_resume_sync(thiz, &last_error, &return_value) == ASM_RET_OK);
	assert(rapi_host_pause_sync(thiz, &last_error, &return_value) == ASM_RET_OK);
	ASM_FREE(sync_param);

	return ;
}

static void test_registry_data_type(RapiHost* thiz, WStr* sub_key, int type, int data_length, void* data)
{
	unsigned int last_error = 0;
	unsigned int return_value = 0;

	RKEY         ret_key = 0;
	unsigned int ret_type = 0;
	unsigned int ret_data_length = 0;
	void*        ret_data = NULL;
	unsigned int disposition = 0;

	WStr* class_name = wstr_dup_from_ascii("class_name");
	WStr* value_name = wstr_dup_from_ascii("value_name");
	WStr* ret_name = NULL;

	assert(rapi_host_create_key(thiz, &last_error, &return_value, 
		RAPI_KEY_CURRENT_USER, sub_key, class_name, &ret_key, &disposition) == ASM_RET_OK);
	assert(ret_key != 0 && disposition == RAPI_REG_CREATED_NEW_KEY);
	assert(return_value == RAPI_SUCCESS);

	assert(rapi_host_set_value(thiz, &last_error, &return_value,
		ret_key, value_name, type, data_length, data) == ASM_RET_OK);
	assert(rapi_host_close_key(thiz, &last_error, &return_value, ret_key) == ASM_RET_OK);

	assert(rapi_host_open_key(thiz, &last_error, &return_value,	RAPI_KEY_CURRENT_USER, sub_key, &ret_key) == ASM_RET_OK);
	assert(rapi_host_query_value(thiz, &last_error, &return_value,
		ret_key, value_name, data_length, &ret_type, &ret_data_length, &ret_data) == ASM_RET_OK);
	assert(data_length == ret_data_length);
	assert(memcmp(ret_data, data, data_length) == 0);
	ASM_FREE(ret_data);

	assert(rapi_host_enum_key(thiz, &last_error, &return_value,ret_key,0, 100, 0, 0, &ret_name) == ASM_RET_OK);
	assert(wstr_compare(ret_name, value_name) == 0);

	assert(rapi_host_close_key(thiz, &last_error, &return_value, ret_key) == ASM_RET_OK);
	assert(rapi_host_delete_key(thiz, &last_error, &return_value, RAPI_KEY_CURRENT_USER, sub_key) == ASM_RET_OK);

	ASM_FREE(class_name);
	ASM_FREE(value_name);
	ASM_FREE(ret_name);

	return;
}

static void test_registry(RapiHost* thiz)
{
	char* str = __func__;
	unsigned int dword_value = 0x11223344;
	WStr* sub_key = wstr_dup_from_ascii("sub_key");
	test_registry_data_type(thiz, sub_key, RAPI_REG_DWORD, sizeof(int), &dword_value);
	test_registry_data_type(thiz, sub_key, RAPI_REG_BINARY, sizeof(int), &dword_value);
	test_registry_data_type(thiz, sub_key, RAPI_REG_SZ, strlen(str), str);
	ASM_FREE(sub_key);

	return;
}


static void test_host(RapiHost* thiz)
{
	int i = 0;
	int n = 1;
	for(i = 0; i < n; i++)
	{
		test_fileman(thiz);
		test_procman(thiz);
		test_system(thiz);
		test_registry(thiz);
	}

	return;
}

static int should_quit = 0;

static void on_new_session(void* ctx, void* new_session)
{
	AsmConnection* session = (AsmConnection*)new_session;
	RapiHost* host = rapi_host_create(session);

	test_host(host);

	rapi_host_destroy(host);

	should_quit = 1;

	return;
}

static void on_device_changed(void* ctx, AsmConnection* device_connection, int action/*1:add 0:remove*/)
{
	if(action)
	{
		RapiDeviceInfo info_from_device = {0};
		RapiDeviceInfo info_from_test = {0};
		rapi_host_connection_device_get_device_info(device_connection, &info_from_device);
		rapi_test_data_get_device_info(&info_from_test);
		assert(rapi_test_data_device_info_cmp(&info_from_device, &info_from_test) == 0);

		rapi_host_connection_device_request_new_session(device_connection, on_new_session, NULL);
	}
	
	printf("%s:%d device=%p action=%d\n", __func__, __LINE__, device_connection, action);

	return;
}

int main(int argc, char* argv[])
{
	AsmConnection* server = rapi_host_connection_listen_create(RAPI_PORT);
	
	rapi_host_connection_listen_hook_device_changed(server, on_device_changed, NULL);
	while(asm_connection_process_event(server) == ASM_RET_OK && !should_quit)
	{
	}
	asm_connection_destroy(server);

	return 0;
}

