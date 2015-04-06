/*
 * File:    rapi_device_registry_write.c
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

#include <rapi_device_registry_write.h>


AsmRet rapi_device_write_registry_create_key(
	AsmOutputBuffer* output, unsigned int last_error, unsigned int return_value,
	RKEY result, unsigned int disposition)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, last_error);
	ret = asm_output_buffer_write_uint32(output, return_value);
	if(return_value == RAPI_SUCCESS)
	{
		ret = asm_output_buffer_write_uint32(output, result);
		ret = asm_output_buffer_write_uint32(output, disposition);

	}

	return ret;
}

AsmRet rapi_device_write_registry_open_key(
	AsmOutputBuffer* output, unsigned int last_error, unsigned int return_value,
	RKEY result)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, last_error);
	ret = asm_output_buffer_write_uint32(output, return_value);
	if(return_value == RAPI_SUCCESS)
	{
		ret = asm_output_buffer_write_uint32(output, result);

	}

	return ret;
}

AsmRet rapi_device_write_registry_query_value(
	AsmOutputBuffer* output, unsigned int last_error, unsigned int return_value,
	unsigned int type, unsigned int ret_data_length, void* ret_data)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, last_error);
	ret = asm_output_buffer_write_uint32(output, return_value);
	if(return_value == RAPI_SUCCESS)
	{
		ret = asm_output_buffer_write_uint32(output, type);
		ret = asm_output_buffer_write_uint32(output, ret_data_length);
		ret = asm_output_buffer_write_data(output, ret_data, ret_data_length);

	}

	return ret;
}

AsmRet rapi_device_write_registry_close_key(
	AsmOutputBuffer* output, unsigned int last_error, unsigned int return_value)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, last_error);
	ret = asm_output_buffer_write_uint32(output, return_value);
	if(return_value == RAPI_SUCCESS)
	{

	}

	return ret;
}

AsmRet rapi_device_write_registry_delete_key(
	AsmOutputBuffer* output, unsigned int last_error, unsigned int return_value)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, last_error);
	ret = asm_output_buffer_write_uint32(output, return_value);
	if(return_value == RAPI_SUCCESS)
	{

	}

	return ret;
}

AsmRet rapi_device_write_registry_delete_value(
	AsmOutputBuffer* output, unsigned int last_error, unsigned int return_value)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, last_error);
	ret = asm_output_buffer_write_uint32(output, return_value);
	if(return_value == RAPI_SUCCESS)
	{

	}

	return ret;
}

AsmRet rapi_device_write_registry_enum_key(
	AsmOutputBuffer* output, unsigned int last_error, unsigned int return_value,
	WStr* name)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, last_error);
	ret = asm_output_buffer_write_uint32(output, return_value);
	if(return_value == RAPI_SUCCESS)
	{
		ret = asm_output_buffer_device_write_wstr(output, name);

	}

	return ret;
}

AsmRet rapi_device_write_registry_set_value(
	AsmOutputBuffer* output, unsigned int last_error, unsigned int return_value)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, last_error);
	ret = asm_output_buffer_write_uint32(output, return_value);
	if(return_value == RAPI_SUCCESS)
	{

	}

	return ret;
}


