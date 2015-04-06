/*
 * File:    rapi_host_procman_read.c
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

#include <rapi_host_procman_read.h>

AsmRet rapi_host_read_procman_create_process(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	, RapiProcessInfo** process_info)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, last_error);
	ret = asm_input_buffer_read_uint32(input, return_value);
	*process_info=ASM_ALLOC(RapiProcessInfo, 0);
	ret = asm_input_buffer_read_optional(input, *process_info, sizeof(*(*process_info)));

	return ret;
}

AsmRet rapi_host_read_procman_config_process(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
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


