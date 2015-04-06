/*
 * File:    rapi_host_wrapper.h
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

AsmRet rapi_host_create_file(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value,
	WStr* file_name, unsigned int access_flags, unsigned int share_mode, unsigned int creation_disposition, unsigned int flags_and_attributes, unsigned int template_file );
AsmRet rapi_host_read_file(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value,
	unsigned int handle, unsigned int length, unsigned int* ret_data_length, void** ret_data);
AsmRet rapi_host_write_file(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value,
	unsigned int handle, unsigned int data_length, void* data,  unsigned int* bytes_written);
AsmRet rapi_host_seek(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value,
	unsigned int handle, unsigned int low, unsigned int has_high, unsigned int high, unsigned int mode, unsigned int* ret_high);
AsmRet rapi_host_seek_to_end(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value,
	unsigned int handle );
AsmRet rapi_host_get_file_time(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value,
	unsigned int handle, RapiFileTime** create_time, RapiFileTime** last_access_time, RapiFileTime** last_write_time);
AsmRet rapi_host_set_file_time(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value,
	unsigned int handle, RapiFileTime* create_time, RapiFileTime* last_access_time, RapiFileTime* last_write_time );
AsmRet rapi_host_copy_file(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value,
	WStr* from, WStr* to, unsigned int overwrite );
AsmRet rapi_host_create_directory(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value,
	WStr* path );
AsmRet rapi_host_delete_file(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value,
	WStr* file );
AsmRet rapi_host_remove_directory(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value,
	WStr* path );
AsmRet rapi_host_move_file(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value,
	WStr* from, WStr* to );
AsmRet rapi_host_get_special_folder(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value,
	unsigned int folder, unsigned int buffer_length, WStr** ret_folder);
AsmRet rapi_host_close_handle(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value,
	unsigned int handle );
AsmRet rapi_host_get_size(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value,
	unsigned int handle );
AsmRet rapi_host_find_all_files(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value,
	WStr* path, unsigned int flags, unsigned int* count, RapiFindData** find_data);
AsmRet rapi_host_find_first_file(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value,
	WStr* path, RapiFindData** find_data, unsigned int* handle);
AsmRet rapi_host_find_next_file(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value,
	unsigned int handle, RapiFindData** find_data);
AsmRet rapi_host_find_close(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value,
	unsigned int* handle );
AsmRet rapi_host_create_process(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value,
	WStr* app_name, WStr* cmd_line, unsigned int zero1, unsigned int zero2, unsigned int zero3, unsigned int flags,unsigned int zero4, unsigned int zero5, unsigned int zero6, RapiProcessInfo** process_info);
AsmRet rapi_host_config_process(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value,
	WStr* config, unsigned int flags, unsigned int* ret_data_length, void** ret_data);
AsmRet rapi_host_create_key(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value,
	RKEY key, WStr* sub_key, WStr* class_name, RKEY* result, unsigned int* disposition);
AsmRet rapi_host_open_key(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value,
	RKEY key, WStr* sub_key, RKEY* result);
AsmRet rapi_host_query_value(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value,
	RKEY key, WStr* value_name, unsigned int data_length, unsigned int* type, unsigned int* ret_data_length, void** ret_data);
AsmRet rapi_host_close_key(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value,
	RKEY key );
AsmRet rapi_host_delete_key(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value,
	RKEY key, WStr* sub_key );
AsmRet rapi_host_delete_value(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value,
	RKEY key, WStr* value_name );
AsmRet rapi_host_enum_key(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value,
	RKEY key, unsigned int index, unsigned int name_length, unsigned int zero1, unsigned int zero2, WStr** name);
AsmRet rapi_host_set_value(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value,
	RKEY key, WStr* value_name, unsigned int type, unsigned int data_length, void* data);
AsmRet rapi_host_get_store_info(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value,
	 RapiStoreInfo** store_info);
AsmRet rapi_host_get_system_info(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value,
	RapiSystemInfo* system_info, RapiSystemInfo** system_info_ret);
AsmRet rapi_host_get_power_status(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value,
	unsigned int refresh, RapiSystemPowerStatus** power_status);
AsmRet rapi_host_get_version_info(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value,
	 RapiVersionInfo** version_info);
AsmRet rapi_host_start_replication(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value );
AsmRet rapi_host_start_sync(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value,
	WStr* params );
AsmRet rapi_host_resume_sync(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value );
AsmRet rapi_host_pause_sync(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value );
