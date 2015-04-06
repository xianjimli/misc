/*
 * File:    rapi_host_fileman_read.c
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

#include <rapi_host_fileman_read.h>

AsmRet rapi_host_read_fileman_create_file(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, last_error);
	ret = asm_input_buffer_read_uint32(input, return_value);

	return ret;
}

AsmRet rapi_host_read_fileman_read_file(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	, unsigned int* ret_data_length, void** ret_data)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, last_error);
	ret = asm_input_buffer_read_uint32(input, return_value);
	ret = asm_input_buffer_read_uint32(input, ret_data_length);
	*ret_data = malloc(*ret_data_length);
	ret = asm_input_buffer_read_data(input, *ret_data, *ret_data_length);

	return ret;
}

AsmRet rapi_host_read_fileman_write_file(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	,  unsigned int* bytes_written)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, last_error);
	ret = asm_input_buffer_read_uint32(input, return_value);
	ret = asm_input_buffer_read_uint32(input, bytes_written);

	return ret;
}

AsmRet rapi_host_read_fileman_seek(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	, unsigned int* ret_high)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, last_error);
	ret = asm_input_buffer_read_uint32(input, return_value);
	ret = asm_input_buffer_read_uint32(input, ret_high);

	return ret;
}

AsmRet rapi_host_read_fileman_seek_to_end(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, last_error);
	ret = asm_input_buffer_read_uint32(input, return_value);

	return ret;
}

AsmRet rapi_host_read_fileman_get_file_time(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	, RapiFileTime** create_time, RapiFileTime** last_access_time, RapiFileTime** last_write_time)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, last_error);
	ret = asm_input_buffer_read_uint32(input, return_value);
	*create_time=ASM_ALLOC(RapiFileTime, 0);
	ret = asm_input_buffer_read_data(input, *create_time, sizeof(*(*create_time)));
	*last_access_time=ASM_ALLOC(RapiFileTime, 0);
	ret = asm_input_buffer_read_data(input, *last_access_time, sizeof(*(*last_access_time)));
	*last_write_time=ASM_ALLOC(RapiFileTime, 0);
	ret = asm_input_buffer_read_data(input, *last_write_time, sizeof(*(*last_write_time)));

	return ret;
}

AsmRet rapi_host_read_fileman_set_file_time(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, last_error);
	ret = asm_input_buffer_read_uint32(input, return_value);

	return ret;
}

AsmRet rapi_host_read_fileman_copy_file(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, last_error);
	ret = asm_input_buffer_read_uint32(input, return_value);

	return ret;
}

AsmRet rapi_host_read_fileman_create_directory(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, last_error);
	ret = asm_input_buffer_read_uint32(input, return_value);

	return ret;
}

AsmRet rapi_host_read_fileman_delete_file(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, last_error);
	ret = asm_input_buffer_read_uint32(input, return_value);

	return ret;
}

AsmRet rapi_host_read_fileman_remove_directory(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, last_error);
	ret = asm_input_buffer_read_uint32(input, return_value);

	return ret;
}

AsmRet rapi_host_read_fileman_move_file(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, last_error);
	ret = asm_input_buffer_read_uint32(input, return_value);

	return ret;
}

AsmRet rapi_host_read_fileman_get_special_folder(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	, WStr** ret_folder)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, last_error);
	//ret = asm_input_buffer_read_uint32(input, return_value);/*XXX: skip*/
	ret = asm_input_buffer_host_read_wstr_dup(input, ret_folder);

	return ret;
}

AsmRet rapi_host_read_fileman_close_handle(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, last_error);
	ret = asm_input_buffer_read_uint32(input, return_value);

	return ret;
}

AsmRet rapi_host_read_fileman_get_size(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, last_error);
	ret = asm_input_buffer_read_uint32(input, return_value);

	return ret;
}

AsmRet rapi_host_read_fileman_find_all_files(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	, unsigned int* count, RapiFindData** find_data)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, last_error);
	ret = asm_input_buffer_read_uint32(input, return_value);
	ret = asm_input_buffer_read_uint32(input, count);
	*find_data=ASM_ALLOC(RapiFindData, 0);
	ret = asm_input_buffer_read_data(input, *find_data, sizeof(*(*find_data)));

	return ret;
}

AsmRet rapi_host_read_fileman_find_first_file(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	, RapiFindData** find_data, unsigned int* handle)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, last_error);
	ret = asm_input_buffer_read_uint32(input, return_value);
	*find_data=ASM_ALLOC(RapiFindData, 0);
	ret = asm_input_buffer_read_data(input, *find_data, sizeof(*(*find_data)));
	ret = asm_input_buffer_read_uint32(input, handle);

	return ret;
}

AsmRet rapi_host_read_fileman_find_next_file(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	, RapiFindData** find_data)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, last_error);
	ret = asm_input_buffer_read_uint32(input, return_value);
	*find_data=ASM_ALLOC(RapiFindData, 0);
	ret = asm_input_buffer_read_data(input, *find_data, sizeof(*(*find_data)));

	return ret;
}

AsmRet rapi_host_read_fileman_find_close(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, last_error);
	ret = asm_input_buffer_read_uint32(input, return_value);

	return ret;
}


