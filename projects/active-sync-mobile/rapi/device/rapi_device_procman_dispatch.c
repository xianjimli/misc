/*
 * File:    rapi_device_procman_dispatch.c
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

#include <rapi_device_procman_dispatch.h>

static AsmRet rapi_device_connection_session_handle_create_process(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	WStr* app_name = NULL;
	WStr* cmd_line = NULL;
	unsigned int zero1 = 0;
	unsigned int zero2 = 0;
	unsigned int zero3 = 0;
	unsigned int flags = 0;
	unsigned int zero4 = 0;
	unsigned int zero5 = 0;
	unsigned int zero6 = 0;
	RapiProcessInfo* process_info = 0;

	unsigned int return_value = RAPI_SUCCESS;

	do
	{
		ret = rapi_device_read_procman_create_process(priv->input, &app_name, &cmd_line, &zero1, &zero2, &zero3, &flags, &zero4, &zero5, &zero6);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_procman_create_process(priv->procman, &return_value, app_name, cmd_line, zero1, zero2, zero3, flags, zero4, zero5, zero6, &process_info);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_write_procman_create_process(priv->output, RAPI_SUCCESS, return_value, process_info);
	}while(0);

	ASM_FREE(app_name);
	ASM_FREE(cmd_line);
	ASM_FREE(process_info);
	return ret;
}
static AsmRet rapi_device_connection_session_handle_config_process(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	WStr* config = NULL;
	unsigned int flags = 0;
	unsigned int ret_data_length = 0;
	void* ret_data = NULL;

	unsigned int return_value = RAPI_SUCCESS;

	do
	{
		ret = rapi_device_read_procman_config_process(priv->input, &config, &flags);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_procman_config_process(priv->procman, &return_value, config, flags, &ret_data_length, &ret_data);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_write_procman_config_process(priv->output, RAPI_SUCCESS, return_value, ret_data_length, ret_data);
	}while(0);

	ASM_FREE(config);
	ASM_FREE(ret_data);
	return ret;
}
AsmRet rapi_device_connection_session_procman_command_dispatch(AsmConnection* thiz, unsigned int cmd)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);

	switch(cmd)
	{
		case RAPI_COMMAND_PROCMAN_CREATE_PROCESS:
		{
			ret = rapi_device_connection_session_handle_create_process(thiz);
			break;
		}
		case RAPI_COMMAND_PROCMAN_CONFIG_PROCESS:
		{
			ret = rapi_device_connection_session_handle_config_process(thiz);
			break;
		}
		default: ret = ASM_RET_UNHANDLED;break;
	}
	return ret;
}
