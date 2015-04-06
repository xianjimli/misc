/*
 * File:    rapi_device_fileman_read.h
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

#include <asm-input-buffer.h>
#include <rapi_device_lib.h>

#ifndef RAPI_DEVICE_FILEMAN_READ_H
#define RAPI_DEVICE_FILEMAN_READ_H

AsmRet rapi_device_read_fileman_create_file(AsmInputBuffer* input
	, WStr** file_name, unsigned int* access_flags, unsigned int* share_mode, unsigned int* creation_disposition, unsigned int* flags_and_attributes, unsigned int* template_file);
AsmRet rapi_device_read_fileman_read_file(AsmInputBuffer* input
	, unsigned int* handle, unsigned int* length);
AsmRet rapi_device_read_fileman_write_file(AsmInputBuffer* input
	, unsigned int* handle, unsigned int* data_length, void** data);
AsmRet rapi_device_read_fileman_seek(AsmInputBuffer* input
	, unsigned int* handle, unsigned int* low, unsigned int* has_high, unsigned int* high, unsigned int* mode);
AsmRet rapi_device_read_fileman_seek_to_end(AsmInputBuffer* input
	, unsigned int* handle);
AsmRet rapi_device_read_fileman_get_file_time(AsmInputBuffer* input
	, unsigned int* handle);
AsmRet rapi_device_read_fileman_set_file_time(AsmInputBuffer* input
	, unsigned int* handle, RapiFileTime** create_time, RapiFileTime** last_access_time, RapiFileTime** last_write_time);
AsmRet rapi_device_read_fileman_copy_file(AsmInputBuffer* input
	, WStr** from, WStr** to, unsigned int* overwrite);
AsmRet rapi_device_read_fileman_create_directory(AsmInputBuffer* input
	, WStr** path);
AsmRet rapi_device_read_fileman_delete_file(AsmInputBuffer* input
	, WStr** file);
AsmRet rapi_device_read_fileman_remove_directory(AsmInputBuffer* input
	, WStr** path);
AsmRet rapi_device_read_fileman_move_file(AsmInputBuffer* input
	, WStr** from, WStr** to);
AsmRet rapi_device_read_fileman_get_special_folder(AsmInputBuffer* input
	, unsigned int* folder, unsigned int* buffer_length);
AsmRet rapi_device_read_fileman_close_handle(AsmInputBuffer* input
	, unsigned int* handle);
AsmRet rapi_device_read_fileman_get_size(AsmInputBuffer* input
	, unsigned int* handle);
AsmRet rapi_device_read_fileman_find_all_files(AsmInputBuffer* input
	, WStr** path, unsigned int* flags);
AsmRet rapi_device_read_fileman_find_first_file(AsmInputBuffer* input
	, WStr** path);
AsmRet rapi_device_read_fileman_find_next_file(AsmInputBuffer* input
	, unsigned int* handle);
AsmRet rapi_device_read_fileman_find_close(AsmInputBuffer* input
	, unsigned int* handle);

#endif/*RAPI_DEVICE_FILEMAN_READ_H*/

