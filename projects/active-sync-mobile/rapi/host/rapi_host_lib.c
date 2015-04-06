/*
 * File:    rapi_host_lib.c
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

#include <asm-common.h>
#include <rapi_host_lib.h>

AsmRet rapi_buffer_read_info(AsmInputBuffer* input, RapiDeviceInfo* info)
{
	size_t i = 0;
	unsigned int length = 0;
	AsmRet ret = ASM_RET_FAIL;

	asm_return_val_if_fail(input != NULL && info != NULL, ret);
	
	ASM_FREE(info->name);
	ASM_FREE(info->platform);
	ASM_FREE(info->model);

	do
	{
		ret = asm_input_buffer_read_data(input, &(info->guid), sizeof(info->guid));
		asm_break_if_fail(ret == ASM_RET_OK);
		ret = asm_input_buffer_read_uint32(input, &(info->os_version_major));
		asm_break_if_fail(ret == ASM_RET_OK);
		ret = asm_input_buffer_read_uint32(input, &(info->os_version_minor));
		asm_break_if_fail(ret == ASM_RET_OK);
		ret = asm_input_buffer_read_uint32(input, &(length));
		asm_break_if_fail(ret == ASM_RET_OK);

		if(length > 0)
		{
			length = (length + 1) * sizeof(WStr);
			info->name = (WStr*)malloc(length);
			ret = asm_input_buffer_read_data(input, info->name, length);
			asm_break_if_fail(ret == ASM_RET_OK);
		}
		ret = asm_input_buffer_read_uint32(input, &(info->dev_version));
		asm_break_if_fail(ret == ASM_RET_OK);
		ret = asm_input_buffer_read_uint32(input, &(info->cpu_type));
		asm_break_if_fail(ret == ASM_RET_OK);
		ret = asm_input_buffer_read_uint32(input, &(info->dev_magic));
		asm_break_if_fail(ret == ASM_RET_OK);
		ret = asm_input_buffer_read_uint32(input, &(info->current_partner));
		asm_break_if_fail(ret == ASM_RET_OK);
		ret = asm_input_buffer_read_uint32(input, &(info->dev_id));
		asm_break_if_fail(ret == ASM_RET_OK);

		length = 0;
		ret = asm_input_buffer_read_uint32(input, &length);
		asm_break_if_fail(ret == ASM_RET_OK);
		if(length > 0)
		{
			info->platform = (char*)malloc(length);
			ret = asm_input_buffer_read_data(input, info->platform, length);
			asm_break_if_fail(ret == ASM_RET_OK);
		}

		length = 0;
		ret = asm_input_buffer_read_uint32(input, &length);
		asm_break_if_fail(ret == ASM_RET_OK);
		if(length > 0)
		{
			length += 1;
			info->model = (char*)malloc(length);
			ret = asm_input_buffer_read_data(input, info->model, length);
		}

		ret = asm_input_buffer_read_uint32(input, &(info->components_nr));
		asm_break_if_fail(ret == ASM_RET_OK);
		if(info->components_nr > 0)
		{
			info->components = malloc(sizeof(RapiComponent) * info->components_nr);
			for(i = 0; i < info->components_nr; i++)
			{
				ret = asm_input_buffer_read_uint32(input, &(info->components[i].l));
				ret = asm_input_buffer_read_uint32(input, &(info->components[i].h));
			}
		}
		
		ret = asm_input_buffer_read_uint32(input, &(info->pw_key));
		asm_break_if_fail(ret == ASM_RET_OK);
	}while(0);

    return ret;
}

