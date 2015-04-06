/*
 * File:    rapi_host_registry.c
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

#include <rapi_host_registry.h>
struct _RapiHostRegistry
{
	AsmStream* stream;
	AsmInputBuffer* input;
	AsmOutputBuffer* output;
};

RapiHostRegistry* rapi_host_registry_create(AsmStream* stream)
{
	RapiHostRegistry* thiz = (RapiHostRegistry*)ASM_ALLOC(RapiHostRegistry, 0);
	thiz->stream = stream;
	thiz->input = asm_input_buffer_create(NULL, 0, ASM_ENDIAN_LITTLE, NULL);
	thiz->output = asm_output_buffer_create(1024, ASM_ENDIAN_LITTLE);

	return thiz;
}

AsmRet rapi_host_registry_create_key(RapiHostRegistry* thiz, unsigned int* last_error, unsigned int* return_value,
	RKEY key, WStr* sub_key, WStr* class_name, RKEY* result, unsigned int* disposition)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ret);

	asm_output_buffer_reset(thiz->output);

	do
	{
		ret = rapi_host_write_registry_create_key(thiz->output, key, sub_key, class_name);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_write(thiz->stream, thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_read(thiz->stream, thiz->input);
		if(ret != ASM_RET_OK) break;
		ret = rapi_host_read_registry_create_key(thiz->input, last_error, return_value, result, disposition);
	}while(0);

	return ret;
}

AsmRet rapi_host_registry_open_key(RapiHostRegistry* thiz, unsigned int* last_error, unsigned int* return_value,
	RKEY key, WStr* sub_key, RKEY* result)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ret);

	asm_output_buffer_reset(thiz->output);

	do
	{
		ret = rapi_host_write_registry_open_key(thiz->output, key, sub_key);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_write(thiz->stream, thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_read(thiz->stream, thiz->input);
		if(ret != ASM_RET_OK) break;
		ret = rapi_host_read_registry_open_key(thiz->input, last_error, return_value, result);
	}while(0);

	return ret;
}

AsmRet rapi_host_registry_query_value(RapiHostRegistry* thiz, unsigned int* last_error, unsigned int* return_value,
	RKEY key, WStr* value_name, unsigned int data_length, unsigned int* type, unsigned int* ret_data_length, void** ret_data)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ret);

	asm_output_buffer_reset(thiz->output);

	do
	{
		ret = rapi_host_write_registry_query_value(thiz->output, key, value_name, data_length);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_write(thiz->stream, thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_read(thiz->stream, thiz->input);
		if(ret != ASM_RET_OK) break;
		ret = rapi_host_read_registry_query_value(thiz->input, last_error, return_value, type, ret_data_length, ret_data);
	}while(0);

	return ret;
}

AsmRet rapi_host_registry_close_key(RapiHostRegistry* thiz, unsigned int* last_error, unsigned int* return_value,
	RKEY key )
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ret);

	asm_output_buffer_reset(thiz->output);

	do
	{
		ret = rapi_host_write_registry_close_key(thiz->output, key);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_write(thiz->stream, thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_read(thiz->stream, thiz->input);
		if(ret != ASM_RET_OK) break;
		ret = rapi_host_read_registry_close_key(thiz->input, last_error, return_value);
	}while(0);

	return ret;
}

AsmRet rapi_host_registry_delete_key(RapiHostRegistry* thiz, unsigned int* last_error, unsigned int* return_value,
	RKEY key, WStr* sub_key )
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ret);

	asm_output_buffer_reset(thiz->output);

	do
	{
		ret = rapi_host_write_registry_delete_key(thiz->output, key, sub_key);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_write(thiz->stream, thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_read(thiz->stream, thiz->input);
		if(ret != ASM_RET_OK) break;
		ret = rapi_host_read_registry_delete_key(thiz->input, last_error, return_value);
	}while(0);

	return ret;
}

AsmRet rapi_host_registry_delete_value(RapiHostRegistry* thiz, unsigned int* last_error, unsigned int* return_value,
	RKEY key, WStr* value_name )
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ret);

	asm_output_buffer_reset(thiz->output);

	do
	{
		ret = rapi_host_write_registry_delete_value(thiz->output, key, value_name);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_write(thiz->stream, thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_read(thiz->stream, thiz->input);
		if(ret != ASM_RET_OK) break;
		ret = rapi_host_read_registry_delete_value(thiz->input, last_error, return_value);
	}while(0);

	return ret;
}

AsmRet rapi_host_registry_enum_key(RapiHostRegistry* thiz, unsigned int* last_error, unsigned int* return_value,
	RKEY key, unsigned int index, unsigned int name_length, unsigned int zero1, unsigned int zero2, WStr** name)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ret);

	asm_output_buffer_reset(thiz->output);

	do
	{
		ret = rapi_host_write_registry_enum_key(thiz->output, key, index, name_length, zero1, zero2);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_write(thiz->stream, thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_read(thiz->stream, thiz->input);
		if(ret != ASM_RET_OK) break;
		ret = rapi_host_read_registry_enum_key(thiz->input, last_error, return_value, name);
	}while(0);

	return ret;
}

AsmRet rapi_host_registry_set_value(RapiHostRegistry* thiz, unsigned int* last_error, unsigned int* return_value,
	RKEY key, WStr* value_name, unsigned int type, unsigned int data_length, void* data)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ret);

	asm_output_buffer_reset(thiz->output);

	do
	{
		ret = rapi_host_write_registry_set_value(thiz->output, key, value_name, type, data_length, data);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_write(thiz->stream, thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_read(thiz->stream, thiz->input);
		if(ret != ASM_RET_OK) break;
		ret = rapi_host_read_registry_set_value(thiz->input, last_error, return_value);
	}while(0);

	return ret;
}

void rapi_host_registry_destroy(RapiHostRegistry* thiz)
{
	asm_input_buffer_destroy(thiz->input);
	asm_output_buffer_destroy(thiz->output);
	ASM_FREE(thiz);

	return;
}

