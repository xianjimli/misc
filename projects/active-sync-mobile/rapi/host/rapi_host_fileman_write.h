/*
 * File:    rapi_host_fileman_write.h
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

#include <asm-output-buffer.h>
#include <rapi_host_lib.h>

#ifndef RAPI_HOST_FILEMAN_WRITE_H
#define RAPI_HOST_FILEMAN_WRITE_H

AsmRet rapi_host_write_fileman_create_file(AsmOutputBuffer* output,
	WStr* file_name, unsigned int access_flags, unsigned int share_mode, unsigned int creation_disposition, unsigned int flags_and_attributes, unsigned int template_file);
AsmRet rapi_host_write_fileman_read_file(AsmOutputBuffer* output,
	unsigned int handle, unsigned int length);
AsmRet rapi_host_write_fileman_write_file(AsmOutputBuffer* output,
	unsigned int handle, unsigned int data_length, void* data);
AsmRet rapi_host_write_fileman_seek(AsmOutputBuffer* output,
	unsigned int handle, unsigned int low, unsigned int has_high, unsigned int high, unsigned int mode);
AsmRet rapi_host_write_fileman_seek_to_end(AsmOutputBuffer* output,
	unsigned int handle);
AsmRet rapi_host_write_fileman_get_file_time(AsmOutputBuffer* output,
	unsigned int handle);
AsmRet rapi_host_write_fileman_set_file_time(AsmOutputBuffer* output,
	unsigned int handle, RapiFileTime* create_time, RapiFileTime* last_access_time, RapiFileTime* last_write_time);
AsmRet rapi_host_write_fileman_copy_file(AsmOutputBuffer* output,
	WStr* from, WStr* to, unsigned int overwrite);
AsmRet rapi_host_write_fileman_create_directory(AsmOutputBuffer* output,
	WStr* path);
AsmRet rapi_host_write_fileman_delete_file(AsmOutputBuffer* output,
	WStr* file);
AsmRet rapi_host_write_fileman_remove_directory(AsmOutputBuffer* output,
	WStr* path);
AsmRet rapi_host_write_fileman_move_file(AsmOutputBuffer* output,
	WStr* from, WStr* to);
AsmRet rapi_host_write_fileman_get_special_folder(AsmOutputBuffer* output,
	unsigned int folder, unsigned int buffer_length);
AsmRet rapi_host_write_fileman_close_handle(AsmOutputBuffer* output,
	unsigned int handle);
AsmRet rapi_host_write_fileman_get_size(AsmOutputBuffer* output,
	unsigned int handle);
AsmRet rapi_host_write_fileman_find_all_files(AsmOutputBuffer* output,
	WStr* path, unsigned int flags);
AsmRet rapi_host_write_fileman_find_first_file(AsmOutputBuffer* output,
	WStr* path);
AsmRet rapi_host_write_fileman_find_next_file(AsmOutputBuffer* output,
	unsigned int handle);
AsmRet rapi_host_write_fileman_find_close(AsmOutputBuffer* output,
	unsigned int handle);

#endif/*RAPI_HOST_FILEMAN_WRITE_H*/

