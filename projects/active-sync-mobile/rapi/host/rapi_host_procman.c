/*
 * File:    rapi_host_procman.c
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

#include <rapi_host_procman.h>
struct _RapiHostProcman
{
	AsmStream* stream;
	AsmInputBuffer* input;
	AsmOutputBuffer* output;
};

RapiHostProcman* rapi_host_procman_create(AsmStream* stream)
{
	RapiHostProcman* thiz = (RapiHostProcman*)ASM_ALLOC(RapiHostProcman, 0);
	thiz->stream = stream;
	thiz->input = asm_input_buffer_create(NULL, 0, ASM_ENDIAN_LITTLE, NULL);
	thiz->output = asm_output_buffer_create(1024, ASM_ENDIAN_LITTLE);

	return thiz;
}

AsmRet rapi_host_procman_create_process(RapiHostProcman* thiz, unsigned int* last_error, unsigned int* return_value,
	WStr* app_name, WStr* cmd_line, unsigned int zero1, unsigned int zero2, unsigned int zero3, unsigned int flags,unsigned int zero4, unsigned int zero5, unsigned int zero6, RapiProcessInfo** process_info)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ret);

	asm_output_buffer_reset(thiz->output);

	do
	{
		ret = rapi_host_write_procman_create_process(thiz->output, app_name, cmd_line, zero1, zero2, zero3, flags, zero4, zero5, zero6);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_write(thiz->stream, thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_read(thiz->stream, thiz->input);
		if(ret != ASM_RET_OK) break;
		ret = rapi_host_read_procman_create_process(thiz->input, last_error, return_value, process_info);
	}while(0);

	return ret;
}

AsmRet rapi_host_procman_config_process(RapiHostProcman* thiz, unsigned int* last_error, unsigned int* return_value,
	WStr* config, unsigned int flags, unsigned int* ret_data_length, void** ret_data)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ret);

	asm_output_buffer_reset(thiz->output);

	do
	{
		ret = rapi_host_write_procman_config_process(thiz->output, config, flags);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_write(thiz->stream, thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_read(thiz->stream, thiz->input);
		if(ret != ASM_RET_OK) break;
		ret = rapi_host_read_procman_config_process(thiz->input, last_error, return_value, ret_data_length, ret_data);
	}while(0);

	return ret;
}

void rapi_host_procman_destroy(RapiHostProcman* thiz)
{
	asm_input_buffer_destroy(thiz->input);
	asm_output_buffer_destroy(thiz->output);
	ASM_FREE(thiz);

	return;
}

