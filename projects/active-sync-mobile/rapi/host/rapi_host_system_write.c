/*
 * File:    rapi_host_system_write.c
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

#include <rapi_host_system_write.h>


AsmRet rapi_host_write_system_get_store_info(AsmOutputBuffer* output)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, RAPI_COMMAND_SYSTEM_GET_STORE_INFO);

	return ret;
}

AsmRet rapi_host_write_system_get_system_info(AsmOutputBuffer* output,
	RapiSystemInfo* system_info)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, RAPI_COMMAND_SYSTEM_GET_SYSTEM_INFO);
		ret = asm_output_buffer_write_data(output, system_info, sizeof(*system_info));

	return ret;
}

AsmRet rapi_host_write_system_get_power_status(AsmOutputBuffer* output,
	unsigned int refresh)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, RAPI_COMMAND_SYSTEM_GET_POWER_STATUS);
		ret = asm_output_buffer_write_uint32(output, refresh);

	return ret;
}

AsmRet rapi_host_write_system_get_version_info(AsmOutputBuffer* output)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, RAPI_COMMAND_SYSTEM_GET_VERSION_INFO);

	return ret;
}

AsmRet rapi_host_write_system_start_replication(AsmOutputBuffer* output)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, RAPI_COMMAND_SYSTEM_START_REPLICATION);

	return ret;
}

AsmRet rapi_host_write_system_start_sync(AsmOutputBuffer* output,
	WStr* params)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, RAPI_COMMAND_SYSTEM_START_SYNC);
		ret = asm_output_buffer_host_write_wstr(output, params);

	return ret;
}

AsmRet rapi_host_write_system_resume_sync(AsmOutputBuffer* output)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, RAPI_COMMAND_SYSTEM_RESUME_SYNC);

	return ret;
}

AsmRet rapi_host_write_system_pause_sync(AsmOutputBuffer* output)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, RAPI_COMMAND_SYSTEM_PAUSE_SYNC);

	return ret;
}


