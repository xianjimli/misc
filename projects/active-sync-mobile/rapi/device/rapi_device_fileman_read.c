/*
 * File:    rapi_device_fileman_read.c
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

#include <rapi_device_fileman_read.h>

AsmRet rapi_device_read_fileman_create_file(AsmInputBuffer* input
	, WStr** file_name, unsigned int* access_flags, unsigned int* share_mode, unsigned int* creation_disposition, unsigned int* flags_and_attributes, unsigned int* template_file)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_device_read_wstr_dup(input, file_name);
	ret = asm_input_buffer_read_uint32(input, access_flags);
	ret = asm_input_buffer_read_uint32(input, share_mode);
	ret = asm_input_buffer_read_uint32(input, creation_disposition);
	ret = asm_input_buffer_read_uint32(input, flags_and_attributes);
	ret = asm_input_buffer_read_uint32(input, template_file);

	return ret;
}

AsmRet rapi_device_read_fileman_read_file(AsmInputBuffer* input
	, unsigned int* handle, unsigned int* length)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, handle);
	ret = asm_input_buffer_read_uint32(input, length);

	return ret;
}

AsmRet rapi_device_read_fileman_write_file(AsmInputBuffer* input
	, unsigned int* handle, unsigned int* data_length, void** data)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, handle);
	ret = asm_input_buffer_read_uint32(input, data_length);
	*data = malloc(*data_length);
	ret = asm_input_buffer_read_data(input, *data, *data_length);

	return ret;
}

AsmRet rapi_device_read_fileman_seek(AsmInputBuffer* input
	, unsigned int* handle, unsigned int* low, unsigned int* has_high, unsigned int* high, unsigned int* mode)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, handle);
	ret = asm_input_buffer_read_uint32(input, low);
	ret = asm_input_buffer_read_uint32(input, has_high);
	ret = asm_input_buffer_read_uint32(input, high);
	ret = asm_input_buffer_read_uint32(input, mode);

	return ret;
}

AsmRet rapi_device_read_fileman_seek_to_end(AsmInputBuffer* input
	, unsigned int* handle)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, handle);

	return ret;
}

AsmRet rapi_device_read_fileman_get_file_time(AsmInputBuffer* input
	, unsigned int* handle)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, handle);

	return ret;
}

AsmRet rapi_device_read_fileman_set_file_time(AsmInputBuffer* input
	, unsigned int* handle, RapiFileTime** create_time, RapiFileTime** last_access_time, RapiFileTime** last_write_time)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, handle);
	*create_time=ASM_ALLOC(RapiFileTime, 0);
	ret = asm_input_buffer_read_data(input, *create_time, sizeof(*(*create_time)));
	*last_access_time=ASM_ALLOC(RapiFileTime, 0);
	ret = asm_input_buffer_read_data(input, *last_access_time, sizeof(*(*last_access_time)));
	*last_write_time=ASM_ALLOC(RapiFileTime, 0);
	ret = asm_input_buffer_read_data(input, *last_write_time, sizeof(*(*last_write_time)));

	return ret;
}

AsmRet rapi_device_read_fileman_copy_file(AsmInputBuffer* input
	, WStr** from, WStr** to, unsigned int* overwrite)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_device_read_wstr_dup(input, from);
	ret = asm_input_buffer_device_read_wstr_dup(input, to);
	ret = asm_input_buffer_read_uint32(input, overwrite);

	return ret;
}

AsmRet rapi_device_read_fileman_create_directory(AsmInputBuffer* input
	, WStr** path)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_device_read_wstr_dup(input, path);

	return ret;
}

AsmRet rapi_device_read_fileman_delete_file(AsmInputBuffer* input
	, WStr** file)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_device_read_wstr_dup(input, file);

	return ret;
}

AsmRet rapi_device_read_fileman_remove_directory(AsmInputBuffer* input
	, WStr** path)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_device_read_wstr_dup(input, path);

	return ret;
}

AsmRet rapi_device_read_fileman_move_file(AsmInputBuffer* input
	, WStr** from, WStr** to)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_device_read_wstr_dup(input, from);
	ret = asm_input_buffer_device_read_wstr_dup(input, to);

	return ret;
}

AsmRet rapi_device_read_fileman_get_special_folder(AsmInputBuffer* input
	, unsigned int* folder, unsigned int* buffer_length)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, folder);
	ret = asm_input_buffer_read_uint32(input, buffer_length);

	return ret;
}

AsmRet rapi_device_read_fileman_close_handle(AsmInputBuffer* input
	, unsigned int* handle)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, handle);

	return ret;
}

AsmRet rapi_device_read_fileman_get_size(AsmInputBuffer* input
	, unsigned int* handle)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, handle);

	return ret;
}

AsmRet rapi_device_read_fileman_find_all_files(AsmInputBuffer* input
	, WStr** path, unsigned int* flags)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_device_read_wstr_dup(input, path);
	ret = asm_input_buffer_read_uint32(input, flags);

	return ret;
}

AsmRet rapi_device_read_fileman_find_first_file(AsmInputBuffer* input
	, WStr** path)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_device_read_wstr_dup(input, path);

	return ret;
}

AsmRet rapi_device_read_fileman_find_next_file(AsmInputBuffer* input
	, unsigned int* handle)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, handle);

	return ret;
}

AsmRet rapi_device_read_fileman_find_close(AsmInputBuffer* input
	, unsigned int* handle)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, handle);

	return ret;
}


