/*
 * File:    rapi_device_procman_read.c
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

#include <rapi_device_procman_read.h>

AsmRet rapi_device_read_procman_create_process(AsmInputBuffer* input
	, WStr** app_name, WStr** cmd_line, unsigned int* zero1, unsigned int* zero2, unsigned int* zero3, unsigned int* flags,unsigned int* zero4, unsigned int* zero5, unsigned int* zero6)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_device_read_wstr_dup(input, app_name);
	ret = asm_input_buffer_device_read_wstr_dup(input, cmd_line);
	ret = asm_input_buffer_read_uint32(input, zero1);
	ret = asm_input_buffer_read_uint32(input, zero2);
	ret = asm_input_buffer_read_uint32(input, zero3);
	ret = asm_input_buffer_read_uint32(input, flags);
	ret = asm_input_buffer_read_uint32(input, zero4);
	ret = asm_input_buffer_read_uint32(input, zero5);
	ret = asm_input_buffer_read_uint32(input, zero6);

	return ret;
}

AsmRet rapi_device_read_procman_config_process(AsmInputBuffer* input
	, WStr** config, unsigned int* flags)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_device_read_wstr_dup(input, config);
	ret = asm_input_buffer_read_uint32(input, flags);

	return ret;
}


