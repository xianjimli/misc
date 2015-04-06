/*
 * File:    rapi_host_fileman.h
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

#include <asm-common.h>
#include <rapi_lib.h>
#ifndef RAPI_HOST_FILEMAN_H
#define RAPI_HOST_FILEMAN_H

struct _RapiHostFileman;
typedef struct _RapiHostFileman RapiHostFileman;

RapiHostFileman* rapi_host_fileman_create(AsmStream* stream);
AsmRet rapi_host_fileman_create_file(RapiHostFileman* thiz, unsigned int* last_error, unsigned int* return_value,
	WStr* file_name, unsigned int access_flags, unsigned int share_mode, unsigned int creation_disposition, unsigned int flags_and_attributes, unsigned int template_file );
AsmRet rapi_host_fileman_read_file(RapiHostFileman* thiz, unsigned int* last_error, unsigned int* return_value,
	unsigned int handle, unsigned int length, unsigned int* ret_data_length, void** ret_data);
AsmRet rapi_host_fileman_write_file(RapiHostFileman* thiz, unsigned int* last_error, unsigned int* return_value,
	unsigned int handle, unsigned int data_length, void* data,  unsigned int* bytes_written);
AsmRet rapi_host_fileman_seek(RapiHostFileman* thiz, unsigned int* last_error, unsigned int* return_value,
	unsigned int handle, unsigned int low, unsigned int has_high, unsigned int high, unsigned int mode, unsigned int* ret_high);
AsmRet rapi_host_fileman_seek_to_end(RapiHostFileman* thiz, unsigned int* last_error, unsigned int* return_value,
	unsigned int handle );
AsmRet rapi_host_fileman_get_file_time(RapiHostFileman* thiz, unsigned int* last_error, unsigned int* return_value,
	unsigned int handle, RapiFileTime** create_time, RapiFileTime** last_access_time, RapiFileTime** last_write_time);
AsmRet rapi_host_fileman_set_file_time(RapiHostFileman* thiz, unsigned int* last_error, unsigned int* return_value,
	unsigned int handle, RapiFileTime* create_time, RapiFileTime* last_access_time, RapiFileTime* last_write_time );
AsmRet rapi_host_fileman_copy_file(RapiHostFileman* thiz, unsigned int* last_error, unsigned int* return_value,
	WStr* from, WStr* to, unsigned int overwrite );
AsmRet rapi_host_fileman_create_directory(RapiHostFileman* thiz, unsigned int* last_error, unsigned int* return_value,
	WStr* path );
AsmRet rapi_host_fileman_delete_file(RapiHostFileman* thiz, unsigned int* last_error, unsigned int* return_value,
	WStr* file );
AsmRet rapi_host_fileman_remove_directory(RapiHostFileman* thiz, unsigned int* last_error, unsigned int* return_value,
	WStr* path );
AsmRet rapi_host_fileman_move_file(RapiHostFileman* thiz, unsigned int* last_error, unsigned int* return_value,
	WStr* from, WStr* to );
AsmRet rapi_host_fileman_get_special_folder(RapiHostFileman* thiz, unsigned int* last_error, unsigned int* return_value,
	unsigned int folder, unsigned int buffer_length, WStr** ret_folder);
AsmRet rapi_host_fileman_close_handle(RapiHostFileman* thiz, unsigned int* last_error, unsigned int* return_value,
	unsigned int handle );
AsmRet rapi_host_fileman_get_size(RapiHostFileman* thiz, unsigned int* last_error, unsigned int* return_value,
	unsigned int handle );
AsmRet rapi_host_fileman_find_all_files(RapiHostFileman* thiz, unsigned int* last_error, unsigned int* return_value,
	WStr* path, unsigned int flags, unsigned int* count, RapiFindData** find_data);
AsmRet rapi_host_fileman_find_first_file(RapiHostFileman* thiz, unsigned int* last_error, unsigned int* return_value,
	WStr* path, RapiFindData** find_data, unsigned int* handle);
AsmRet rapi_host_fileman_find_next_file(RapiHostFileman* thiz, unsigned int* last_error, unsigned int* return_value,
	unsigned int handle, RapiFindData** find_data);
AsmRet rapi_host_fileman_find_close(RapiHostFileman* thiz, unsigned int* last_error, unsigned int* return_value,
	unsigned int* handle );
void rapi_host_fileman_destroy(RapiHostFileman* thiz);

#endif/*RAPI_HOST_FILEMAN_H*/

