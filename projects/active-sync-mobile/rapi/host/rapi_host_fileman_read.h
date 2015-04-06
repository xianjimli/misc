/*
 * File:    rapi_host_fileman_read.h
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
#include <rapi_host_lib.h>

#ifndef RAPI_HOST_FILEMAN_READ_H
#define RAPI_HOST_FILEMAN_READ_H

AsmRet rapi_host_read_fileman_create_file(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	);
AsmRet rapi_host_read_fileman_read_file(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	, unsigned int* ret_data_length, void** ret_data);
AsmRet rapi_host_read_fileman_write_file(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	,  unsigned int* bytes_written);
AsmRet rapi_host_read_fileman_seek(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	, unsigned int* ret_high);
AsmRet rapi_host_read_fileman_seek_to_end(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	);
AsmRet rapi_host_read_fileman_get_file_time(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	, RapiFileTime** create_time, RapiFileTime** last_access_time, RapiFileTime** last_write_time);
AsmRet rapi_host_read_fileman_set_file_time(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	);
AsmRet rapi_host_read_fileman_copy_file(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	);
AsmRet rapi_host_read_fileman_create_directory(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	);
AsmRet rapi_host_read_fileman_delete_file(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	);
AsmRet rapi_host_read_fileman_remove_directory(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	);
AsmRet rapi_host_read_fileman_move_file(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	);
AsmRet rapi_host_read_fileman_get_special_folder(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	, WStr** ret_folder);
AsmRet rapi_host_read_fileman_close_handle(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	);
AsmRet rapi_host_read_fileman_get_size(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	);
AsmRet rapi_host_read_fileman_find_all_files(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	, unsigned int* count, RapiFindData** find_data);
AsmRet rapi_host_read_fileman_find_first_file(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	, RapiFindData** find_data, unsigned int* handle);
AsmRet rapi_host_read_fileman_find_next_file(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	, RapiFindData** find_data);
AsmRet rapi_host_read_fileman_find_close(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	);

#endif/*RAPI_HOST_FILEMAN_READ_H*/

