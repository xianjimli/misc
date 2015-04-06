/*
 * File:    rapi_device_system_dispatch.c
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

#include <rapi_device_system_dispatch.h>

static AsmRet rapi_device_connection_session_handle_get_store_info(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	RapiStoreInfo* store_info = 0;

	unsigned int return_value = RAPI_SUCCESS;

	do
	{
		ret = rapi_device_system_get_store_info(priv->system, &return_value, &store_info);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_write_system_get_store_info(priv->output, RAPI_SUCCESS, return_value, store_info);
	}while(0);

	ASM_FREE(store_info);
	return ret;
}
static AsmRet rapi_device_connection_session_handle_get_system_info(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	RapiSystemInfo* system_info = 0;
	RapiSystemInfo* system_info_ret = 0;

	unsigned int return_value = RAPI_SUCCESS;

	do
	{
		ret = rapi_device_read_system_get_system_info(priv->input, &system_info);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_system_get_system_info(priv->system, &return_value, system_info, &system_info_ret);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_write_system_get_system_info(priv->output, RAPI_SUCCESS, return_value, system_info_ret);
	}while(0);

	ASM_FREE(system_info);
	ASM_FREE(system_info_ret);
	return ret;
}
static AsmRet rapi_device_connection_session_handle_get_power_status(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	unsigned int refresh = 0;
	RapiSystemPowerStatus* power_status = 0;

	unsigned int return_value = RAPI_SUCCESS;

	do
	{
		ret = rapi_device_read_system_get_power_status(priv->input, &refresh);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_system_get_power_status(priv->system, &return_value, refresh, &power_status);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_write_system_get_power_status(priv->output, RAPI_SUCCESS, return_value, power_status);
	}while(0);

	ASM_FREE(power_status);
	return ret;
}
static AsmRet rapi_device_connection_session_handle_get_version_info(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	RapiVersionInfo* version_info = 0;

	unsigned int return_value = RAPI_SUCCESS;

	do
	{
		ret = rapi_device_system_get_version_info(priv->system, &return_value, &version_info);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_write_system_get_version_info(priv->output, RAPI_SUCCESS, return_value, version_info);
	}while(0);

	ASM_FREE(version_info);
	return ret;
}
static AsmRet rapi_device_connection_session_handle_start_replication(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;


	unsigned int return_value = RAPI_SUCCESS;

	do
	{
		ret = rapi_device_system_start_replication(priv->system, &return_value);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_write_system_start_replication(priv->output, RAPI_SUCCESS, return_value);
	}while(0);

	return ret;
}
static AsmRet rapi_device_connection_session_handle_start_sync(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	WStr* params = NULL;

	unsigned int return_value = RAPI_SUCCESS;

	do
	{
		ret = rapi_device_read_system_start_sync(priv->input, &params);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_system_start_sync(priv->system, &return_value, params);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_write_system_start_sync(priv->output, RAPI_SUCCESS, return_value);
	}while(0);

	ASM_FREE(params);
	return ret;
}
static AsmRet rapi_device_connection_session_handle_resume_sync(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;


	unsigned int return_value = RAPI_SUCCESS;

	do
	{
		ret = rapi_device_system_resume_sync(priv->system, &return_value);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_write_system_resume_sync(priv->output, RAPI_SUCCESS, return_value);
	}while(0);

	return ret;
}
static AsmRet rapi_device_connection_session_handle_pause_sync(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;


	unsigned int return_value = RAPI_SUCCESS;

	do
	{
		ret = rapi_device_system_pause_sync(priv->system, &return_value);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_write_system_pause_sync(priv->output, RAPI_SUCCESS, return_value);
	}while(0);

	return ret;
}
AsmRet rapi_device_connection_session_system_command_dispatch(AsmConnection* thiz, unsigned int cmd)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);

	switch(cmd)
	{
		case RAPI_COMMAND_SYSTEM_GET_STORE_INFO:
		{
			ret = rapi_device_connection_session_handle_get_store_info(thiz);
			break;
		}
		case RAPI_COMMAND_SYSTEM_GET_SYSTEM_INFO:
		{
			ret = rapi_device_connection_session_handle_get_system_info(thiz);
			break;
		}
		case RAPI_COMMAND_SYSTEM_GET_POWER_STATUS:
		{
			ret = rapi_device_connection_session_handle_get_power_status(thiz);
			break;
		}
		case RAPI_COMMAND_SYSTEM_GET_VERSION_INFO:
		{
			ret = rapi_device_connection_session_handle_get_version_info(thiz);
			break;
		}
		case RAPI_COMMAND_SYSTEM_START_REPLICATION:
		{
			ret = rapi_device_connection_session_handle_start_replication(thiz);
			break;
		}
		case RAPI_COMMAND_SYSTEM_START_SYNC:
		{
			ret = rapi_device_connection_session_handle_start_sync(thiz);
			break;
		}
		case RAPI_COMMAND_SYSTEM_RESUME_SYNC:
		{
			ret = rapi_device_connection_session_handle_resume_sync(thiz);
			break;
		}
		case RAPI_COMMAND_SYSTEM_PAUSE_SYNC:
		{
			ret = rapi_device_connection_session_handle_pause_sync(thiz);
			break;
		}
		default: ret = ASM_RET_UNHANDLED;break;
	}
	return ret;
}
