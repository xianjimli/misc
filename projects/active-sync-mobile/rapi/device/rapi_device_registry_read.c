/*
 * File:    rapi_device_registry_read.c
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

#include <rapi_device_registry_read.h>

AsmRet rapi_device_read_registry_create_key(AsmInputBuffer* input
	, RKEY* key, WStr** sub_key, WStr** class_name)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, key);
	ret = asm_input_buffer_device_read_wstr_dup(input, sub_key);
	ret = asm_input_buffer_device_read_wstr_dup(input, class_name);

	return ret;
}

AsmRet rapi_device_read_registry_open_key(AsmInputBuffer* input
	, RKEY* key, WStr** sub_key)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, key);
	ret = asm_input_buffer_device_read_wstr_dup(input, sub_key);

	return ret;
}

AsmRet rapi_device_read_registry_query_value(AsmInputBuffer* input
	, RKEY* key, WStr** value_name, unsigned int* data_length)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, key);
	ret = asm_input_buffer_device_read_wstr_dup(input, value_name);
	ret = asm_input_buffer_read_uint32(input, data_length);

	return ret;
}

AsmRet rapi_device_read_registry_close_key(AsmInputBuffer* input
	, RKEY* key)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, key);

	return ret;
}

AsmRet rapi_device_read_registry_delete_key(AsmInputBuffer* input
	, RKEY* key, WStr** sub_key)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, key);
	ret = asm_input_buffer_device_read_wstr_dup(input, sub_key);

	return ret;
}

AsmRet rapi_device_read_registry_delete_value(AsmInputBuffer* input
	, RKEY* key, WStr** value_name)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, key);
	ret = asm_input_buffer_device_read_wstr_dup(input, value_name);

	return ret;
}

AsmRet rapi_device_read_registry_enum_key(AsmInputBuffer* input
	, RKEY* key, unsigned int* index, unsigned int* name_length, unsigned int* zero1, unsigned int* zero2)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, key);
	ret = asm_input_buffer_read_uint32(input, index);
	ret = asm_input_buffer_read_uint32(input, name_length);
	ret = asm_input_buffer_read_uint32(input, zero1);
	ret = asm_input_buffer_read_uint32(input, zero2);

	return ret;
}

AsmRet rapi_device_read_registry_set_value(AsmInputBuffer* input
	, RKEY* key, WStr** value_name, unsigned int* type, unsigned int* data_length, void** data)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, key);
	ret = asm_input_buffer_device_read_wstr_dup(input, value_name);
	ret = asm_input_buffer_read_uint32(input, type);
	ret = asm_input_buffer_read_uint32(input, data_length);
	*data = malloc(*data_length);
	ret = asm_input_buffer_read_data(input, *data, *data_length);

	return ret;
}


