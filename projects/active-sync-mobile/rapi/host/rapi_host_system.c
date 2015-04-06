/*
 * File:    rapi_host_system.c
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

#include <rapi_host_system.h>
struct _RapiHostSystem
{
	AsmStream* stream;
	AsmInputBuffer* input;
	AsmOutputBuffer* output;
};

RapiHostSystem* rapi_host_system_create(AsmStream* stream)
{
	RapiHostSystem* thiz = (RapiHostSystem*)ASM_ALLOC(RapiHostSystem, 0);
	thiz->stream = stream;
	thiz->input = asm_input_buffer_create(NULL, 0, ASM_ENDIAN_LITTLE, NULL);
	thiz->output = asm_output_buffer_create(1024, ASM_ENDIAN_LITTLE);

	return thiz;
}

AsmRet rapi_host_system_get_store_info(RapiHostSystem* thiz, unsigned int* last_error, unsigned int* return_value,
	 RapiStoreInfo** store_info)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ret);

	asm_output_buffer_reset(thiz->output);

	do
	{
		ret = rapi_host_write_system_get_store_info(thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_write(thiz->stream, thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_read(thiz->stream, thiz->input);
		if(ret != ASM_RET_OK) break;
		ret = rapi_host_read_system_get_store_info(thiz->input, last_error, return_value, store_info);
	}while(0);

	return ret;
}

AsmRet rapi_host_system_get_system_info(RapiHostSystem* thiz, unsigned int* last_error, unsigned int* return_value,
	RapiSystemInfo* system_info, RapiSystemInfo** system_info_ret)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ret);

	asm_output_buffer_reset(thiz->output);

	do
	{
		ret = rapi_host_write_system_get_system_info(thiz->output, system_info);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_write(thiz->stream, thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_read(thiz->stream, thiz->input);
		if(ret != ASM_RET_OK) break;
		ret = rapi_host_read_system_get_system_info(thiz->input, last_error, return_value, system_info_ret);
	}while(0);

	return ret;
}

AsmRet rapi_host_system_get_power_status(RapiHostSystem* thiz, unsigned int* last_error, unsigned int* return_value,
	unsigned int refresh, RapiSystemPowerStatus** power_status)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ret);

	asm_output_buffer_reset(thiz->output);

	do
	{
		ret = rapi_host_write_system_get_power_status(thiz->output, refresh);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_write(thiz->stream, thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_read(thiz->stream, thiz->input);
		if(ret != ASM_RET_OK) break;
		ret = rapi_host_read_system_get_power_status(thiz->input, last_error, return_value, power_status);
	}while(0);

	return ret;
}

AsmRet rapi_host_system_get_version_info(RapiHostSystem* thiz, unsigned int* last_error, unsigned int* return_value,
	 RapiVersionInfo** version_info)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ret);

	asm_output_buffer_reset(thiz->output);

	do
	{
		ret = rapi_host_write_system_get_version_info(thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_write(thiz->stream, thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_read(thiz->stream, thiz->input);
		if(ret != ASM_RET_OK) break;
		ret = rapi_host_read_system_get_version_info(thiz->input, last_error, return_value, version_info);
	}while(0);

	return ret;
}

AsmRet rapi_host_system_start_replication(RapiHostSystem* thiz, unsigned int* last_error, unsigned int* return_value )
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ret);

	asm_output_buffer_reset(thiz->output);

	do
	{
		ret = rapi_host_write_system_start_replication(thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_write(thiz->stream, thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_read(thiz->stream, thiz->input);
		if(ret != ASM_RET_OK) break;
		ret = rapi_host_read_system_start_replication(thiz->input, last_error, return_value);
	}while(0);

	return ret;
}

AsmRet rapi_host_system_start_sync(RapiHostSystem* thiz, unsigned int* last_error, unsigned int* return_value,
	WStr* params )
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ret);

	asm_output_buffer_reset(thiz->output);

	do
	{
		ret = rapi_host_write_system_start_sync(thiz->output, params);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_write(thiz->stream, thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_read(thiz->stream, thiz->input);
		if(ret != ASM_RET_OK) break;
		ret = rapi_host_read_system_start_sync(thiz->input, last_error, return_value);
	}while(0);

	return ret;
}

AsmRet rapi_host_system_resume_sync(RapiHostSystem* thiz, unsigned int* last_error, unsigned int* return_value )
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ret);

	asm_output_buffer_reset(thiz->output);

	do
	{
		ret = rapi_host_write_system_resume_sync(thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_write(thiz->stream, thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_read(thiz->stream, thiz->input);
		if(ret != ASM_RET_OK) break;
		ret = rapi_host_read_system_resume_sync(thiz->input, last_error, return_value);
	}while(0);

	return ret;
}

AsmRet rapi_host_system_pause_sync(RapiHostSystem* thiz, unsigned int* last_error, unsigned int* return_value )
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ret);

	asm_output_buffer_reset(thiz->output);

	do
	{
		ret = rapi_host_write_system_pause_sync(thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_write(thiz->stream, thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_read(thiz->stream, thiz->input);
		if(ret != ASM_RET_OK) break;
		ret = rapi_host_read_system_pause_sync(thiz->input, last_error, return_value);
	}while(0);

	return ret;
}

void rapi_host_system_destroy(RapiHostSystem* thiz)
{
	asm_input_buffer_destroy(thiz->input);
	asm_output_buffer_destroy(thiz->output);
	ASM_FREE(thiz);

	return;
}

