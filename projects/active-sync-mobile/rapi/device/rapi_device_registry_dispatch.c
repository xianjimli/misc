/*
 * File:    rapi_device_registry_dispatch.c
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

#include <rapi_device_registry_dispatch.h>

static AsmRet rapi_device_connection_session_handle_create_key(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	RKEY key = 0;
	WStr* sub_key = NULL;
	WStr* class_name = NULL;
	RKEY result = 0;
	unsigned int disposition = 0;

	unsigned int return_value = RAPI_SUCCESS;

	do
	{
		ret = rapi_device_read_registry_create_key(priv->input, &key, &sub_key, &class_name);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_registry_create_key(priv->registry, &return_value, key, sub_key, class_name, &result, &disposition);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_write_registry_create_key(priv->output, RAPI_SUCCESS, return_value, result, disposition);
	}while(0);

	ASM_FREE(sub_key);
	ASM_FREE(class_name);
	return ret;
}
static AsmRet rapi_device_connection_session_handle_open_key(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	RKEY key = 0;
	WStr* sub_key = NULL;
	RKEY result = 0;

	unsigned int return_value = RAPI_SUCCESS;

	do
	{
		ret = rapi_device_read_registry_open_key(priv->input, &key, &sub_key);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_registry_open_key(priv->registry, &return_value, key, sub_key, &result);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_write_registry_open_key(priv->output, RAPI_SUCCESS, return_value, result);
	}while(0);

	ASM_FREE(sub_key);
	return ret;
}
static AsmRet rapi_device_connection_session_handle_query_value(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	RKEY key = 0;
	WStr* value_name = NULL;
	unsigned int data_length = 0;
	unsigned int type = 0;
	unsigned int ret_data_length = 0;
	void* ret_data = NULL;

	unsigned int return_value = RAPI_SUCCESS;

	do
	{
		ret = rapi_device_read_registry_query_value(priv->input, &key, &value_name, &data_length);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_registry_query_value(priv->registry, &return_value, key, value_name, data_length, &type, &ret_data_length, &ret_data);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_write_registry_query_value(priv->output, RAPI_SUCCESS, return_value, type, ret_data_length, ret_data);
	}while(0);

	ASM_FREE(value_name);
	ASM_FREE(ret_data);
	return ret;
}
static AsmRet rapi_device_connection_session_handle_close_key(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	RKEY key = 0;

	unsigned int return_value = RAPI_SUCCESS;

	do
	{
		ret = rapi_device_read_registry_close_key(priv->input, &key);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_registry_close_key(priv->registry, &return_value, key);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_write_registry_close_key(priv->output, RAPI_SUCCESS, return_value);
	}while(0);

	return ret;
}
static AsmRet rapi_device_connection_session_handle_delete_key(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	RKEY key = 0;
	WStr* sub_key = NULL;

	unsigned int return_value = RAPI_SUCCESS;

	do
	{
		ret = rapi_device_read_registry_delete_key(priv->input, &key, &sub_key);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_registry_delete_key(priv->registry, &return_value, key, sub_key);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_write_registry_delete_key(priv->output, RAPI_SUCCESS, return_value);
	}while(0);

	ASM_FREE(sub_key);
	return ret;
}
static AsmRet rapi_device_connection_session_handle_delete_value(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	RKEY key = 0;
	WStr* value_name = NULL;

	unsigned int return_value = RAPI_SUCCESS;

	do
	{
		ret = rapi_device_read_registry_delete_value(priv->input, &key, &value_name);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_registry_delete_value(priv->registry, &return_value, key, value_name);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_write_registry_delete_value(priv->output, RAPI_SUCCESS, return_value);
	}while(0);

	ASM_FREE(value_name);
	return ret;
}
static AsmRet rapi_device_connection_session_handle_enum_key(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	RKEY key = 0;
	unsigned int index = 0;
	unsigned int name_length = 0;
	unsigned int zero1 = 0;
	unsigned int zero2 = 0;
	WStr* name = NULL;

	unsigned int return_value = RAPI_SUCCESS;

	do
	{
		ret = rapi_device_read_registry_enum_key(priv->input, &key, &index, &name_length, &zero1, &zero2);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_registry_enum_key(priv->registry, &return_value, key, index, name_length, zero1, zero2, &name);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_write_registry_enum_key(priv->output, RAPI_SUCCESS, return_value, name);
	}while(0);

	ASM_FREE(name);
	return ret;
}
static AsmRet rapi_device_connection_session_handle_set_value(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	RKEY key = 0;
	WStr* value_name = NULL;
	unsigned int type = 0;
	unsigned int data_length = 0;
	void* data = NULL;

	unsigned int return_value = RAPI_SUCCESS;

	do
	{
		ret = rapi_device_read_registry_set_value(priv->input, &key, &value_name, &type, &data_length, &data);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_registry_set_value(priv->registry, &return_value, key, value_name, type, data_length, data);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_write_registry_set_value(priv->output, RAPI_SUCCESS, return_value);
	}while(0);

	ASM_FREE(value_name);
	ASM_FREE(data);
	return ret;
}
AsmRet rapi_device_connection_session_registry_command_dispatch(AsmConnection* thiz, unsigned int cmd)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);

	switch(cmd)
	{
		case RAPI_COMMAND_REGISTRY_CREATE_KEY:
		{
			ret = rapi_device_connection_session_handle_create_key(thiz);
			break;
		}
		case RAPI_COMMAND_REGISTRY_OPEN_KEY:
		{
			ret = rapi_device_connection_session_handle_open_key(thiz);
			break;
		}
		case RAPI_COMMAND_REGISTRY_QUERY_VALUE:
		{
			ret = rapi_device_connection_session_handle_query_value(thiz);
			break;
		}
		case RAPI_COMMAND_REGISTRY_CLOSE_KEY:
		{
			ret = rapi_device_connection_session_handle_close_key(thiz);
			break;
		}
		case RAPI_COMMAND_REGISTRY_DELETE_KEY:
		{
			ret = rapi_device_connection_session_handle_delete_key(thiz);
			break;
		}
		case RAPI_COMMAND_REGISTRY_DELETE_VALUE:
		{
			ret = rapi_device_connection_session_handle_delete_value(thiz);
			break;
		}
		case RAPI_COMMAND_REGISTRY_ENUM_KEY:
		{
			ret = rapi_device_connection_session_handle_enum_key(thiz);
			break;
		}
		case RAPI_COMMAND_REGISTRY_SET_VALUE:
		{
			ret = rapi_device_connection_session_handle_set_value(thiz);
			break;
		}
		default: ret = ASM_RET_UNHANDLED;break;
	}
	return ret;
}
