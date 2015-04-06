/*
 * File:    rapi_device_lib.c
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

#include <rapi_device_lib.h>

AsmRet rapi_buffer_write_version(AsmOutputBuffer* output, unsigned int error, unsigned int result, const RapiVersionInfo* version)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL && version != NULL, ret);

	asm_output_buffer_write_uint32(output, error);
	asm_output_buffer_write_uint32(output, result);
	asm_output_buffer_write_uint32(output, sizeof(*version));

	ret = asm_output_buffer_write_data(output, (void*)version, sizeof(*version));

	return ret;
}

static AsmRet asm_output_buffer_write_device_name(AsmOutputBuffer* output, const WStr* value)
{
	if(value != NULL)
	{
		size_t length = wstr_length(value);

		asm_output_buffer_write_uint32(output, length);
		return asm_output_buffer_write_data(output, (void*)value, (length + 1) * sizeof(WStr));
	}
	else
	{
		return asm_output_buffer_write_uint32(output, 0);
	}
}

AsmRet rapi_buffer_write_info(AsmOutputBuffer* output, const RapiDeviceInfo* info)
{
	size_t i = 0;
	AsmRet ret = ASM_RET_FAIL;

	asm_return_val_if_fail(output != NULL && info != NULL, ret);
	asm_output_buffer_write_data(output, &(info->guid), sizeof(info->guid));
	asm_output_buffer_write_uint32(output, info->os_version_major);
	asm_output_buffer_write_uint32(output, info->os_version_minor);
	asm_output_buffer_write_device_name(output, info->name);
	asm_output_buffer_write_uint32(output, info->dev_version);
	asm_output_buffer_write_uint32(output, info->cpu_type);
	asm_output_buffer_write_uint32(output, info->dev_magic);
	asm_output_buffer_write_uint32(output, info->current_partner);
	asm_output_buffer_write_uint32(output, info->dev_id);
	asm_output_buffer_write_uint32(output, strlen(info->platform) + 1);
	asm_output_buffer_write_data(output, info->platform, strlen(info->platform) + 1);
	asm_output_buffer_write_uint32(output, strlen(info->model));
	asm_output_buffer_write_data(output, info->model, strlen(info->model) + 1);
	asm_output_buffer_write_uint32(output, info->components_nr);

	for(i = 0; i < info->components_nr; i++)
	{
		asm_output_buffer_write_uint32(output, info->components[i].l);
		asm_output_buffer_write_uint32(output, info->components[i].h);
	}
	asm_output_buffer_write_uint32(output, info->pw_key);

	return ASM_RET_OK;
}

AsmRet rapi_buffer_write_start_replication(AsmOutputBuffer* output, unsigned int error, unsigned int result)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	asm_output_buffer_write_uint32(output, error);
	asm_output_buffer_write_uint32(output, result);

	return ret;
}
