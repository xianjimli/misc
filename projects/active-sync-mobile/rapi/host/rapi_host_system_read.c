/*
 * File:    rapi_host_system_read.c
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

#include <rapi_host_system_read.h>

AsmRet rapi_host_read_system_get_store_info(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	, RapiStoreInfo** store_info)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, last_error);
	ret = asm_input_buffer_read_uint32(input, return_value);
	*store_info=ASM_ALLOC(RapiStoreInfo, 0);
	ret = asm_input_buffer_read_data(input, *store_info, sizeof(*(*store_info)));

	return ret;
}

AsmRet rapi_host_read_system_get_system_info(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	, RapiSystemInfo** system_info_ret)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

//	ret = asm_input_buffer_read_uint32(input, last_error); /*XXX:skip*/
	ret = asm_input_buffer_read_uint32(input, return_value);
	*system_info_ret=ASM_ALLOC(RapiSystemInfo, 0);
	ret = asm_input_buffer_read_data(input, *system_info_ret, sizeof(*(*system_info_ret)));

	return ret;
}

AsmRet rapi_host_read_system_get_power_status(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	, RapiSystemPowerStatus** power_status)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

//	ret = asm_input_buffer_read_uint32(input, last_error); /*XXX: skip*/
	ret = asm_input_buffer_read_uint32(input, return_value);
	*power_status=ASM_ALLOC(RapiSystemPowerStatus, 0);
	ret = asm_input_buffer_read_data(input, *power_status, sizeof(*(*power_status)));

	return ret;
}

AsmRet rapi_host_read_system_get_version_info(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	, RapiVersionInfo** version_info)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, last_error);
	ret = asm_input_buffer_read_uint32(input, return_value);
	*version_info=ASM_ALLOC(RapiVersionInfo, 0);
	ret = asm_input_buffer_read_data(input, *version_info, sizeof(*(*version_info)));

	return ret;
}

AsmRet rapi_host_read_system_start_replication(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, last_error);
	ret = asm_input_buffer_read_uint32(input, return_value);

	return ret;
}

AsmRet rapi_host_read_system_start_sync(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, last_error);
	ret = asm_input_buffer_read_uint32(input, return_value);

	return ret;
}

AsmRet rapi_host_read_system_resume_sync(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, last_error);
	ret = asm_input_buffer_read_uint32(input, return_value);

	return ret;
}

AsmRet rapi_host_read_system_pause_sync(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value
	)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(input != NULL, ret);

	ret = asm_input_buffer_read_uint32(input, last_error);
	ret = asm_input_buffer_read_uint32(input, return_value);

	return ret;
}


