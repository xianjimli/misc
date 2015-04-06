/*
 * File:    rapi_host_registry_write.c
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

#include <rapi_host_registry_write.h>


AsmRet rapi_host_write_registry_create_key(AsmOutputBuffer* output,
	RKEY key, WStr* sub_key, WStr* class_name)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, RAPI_COMMAND_REGISTRY_CREATE_KEY);
		ret = asm_output_buffer_write_uint32(output, key);
		ret = asm_output_buffer_host_write_wstr(output, sub_key);
		ret = asm_output_buffer_host_write_wstr(output, class_name);

	return ret;
}

AsmRet rapi_host_write_registry_open_key(AsmOutputBuffer* output,
	RKEY key, WStr* sub_key)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, RAPI_COMMAND_REGISTRY_OPEN_KEY);
		ret = asm_output_buffer_write_uint32(output, key);
		ret = asm_output_buffer_host_write_wstr(output, sub_key);

	return ret;
}

AsmRet rapi_host_write_registry_query_value(AsmOutputBuffer* output,
	RKEY key, WStr* value_name, unsigned int data_length)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, RAPI_COMMAND_REGISTRY_QUERY_VALUE);
		ret = asm_output_buffer_write_uint32(output, key);
		ret = asm_output_buffer_host_write_wstr(output, value_name);
		ret = asm_output_buffer_write_uint32(output, data_length);

	return ret;
}

AsmRet rapi_host_write_registry_close_key(AsmOutputBuffer* output,
	RKEY key)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, RAPI_COMMAND_REGISTRY_CLOSE_KEY);
		ret = asm_output_buffer_write_uint32(output, key);

	return ret;
}

AsmRet rapi_host_write_registry_delete_key(AsmOutputBuffer* output,
	RKEY key, WStr* sub_key)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, RAPI_COMMAND_REGISTRY_DELETE_KEY);
		ret = asm_output_buffer_write_uint32(output, key);
		ret = asm_output_buffer_host_write_wstr(output, sub_key);

	return ret;
}

AsmRet rapi_host_write_registry_delete_value(AsmOutputBuffer* output,
	RKEY key, WStr* value_name)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, RAPI_COMMAND_REGISTRY_DELETE_VALUE);
		ret = asm_output_buffer_write_uint32(output, key);
		ret = asm_output_buffer_host_write_wstr(output, value_name);

	return ret;
}

AsmRet rapi_host_write_registry_enum_key(AsmOutputBuffer* output,
	RKEY key, unsigned int index, unsigned int name_length, unsigned int zero1, unsigned int zero2)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, RAPI_COMMAND_REGISTRY_ENUM_KEY);
		ret = asm_output_buffer_write_uint32(output, key);
		ret = asm_output_buffer_write_uint32(output, index);
		ret = asm_output_buffer_write_uint32(output, name_length);
		ret = asm_output_buffer_write_uint32(output, zero1);
		ret = asm_output_buffer_write_uint32(output, zero2);

	return ret;
}

AsmRet rapi_host_write_registry_set_value(AsmOutputBuffer* output,
	RKEY key, WStr* value_name, unsigned int type, unsigned int data_length, void* data)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, RAPI_COMMAND_REGISTRY_SET_VALUE);
		ret = asm_output_buffer_write_uint32(output, key);
		ret = asm_output_buffer_host_write_wstr(output, value_name);
		ret = asm_output_buffer_write_uint32(output, type);
		ret = asm_output_buffer_write_uint32(output, data_length);
		ret = asm_output_buffer_write_data(output, data, data_length);

	return ret;
}


