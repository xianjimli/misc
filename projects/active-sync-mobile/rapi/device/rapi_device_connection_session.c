/*
 * File:    rapi_device_connection_session.c
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

#include <string.h>
#include <asm-input-buffer.h>
#include <asm-output-buffer.h>
#include <rapi_device_connection_session.h>

typedef struct _PrivInfo
{
	unsigned int     req_id;
	RapiDevice*      device;
	AsmStream*       stream;
	AsmInputBuffer*  input;
	AsmOutputBuffer* output;

	AsmHookFunc on_destroy;
	void* on_destroy_ctx;
	RapiDeviceCommandHookFunc on_command;
	void* on_command_ctx;

	RapiDeviceRegistry* registry;	
	RapiDeviceProcman* procman;
	RapiDeviceFileman* fileman;
	RapiDeviceSystem*  system;
}PrivInfo;

#include <rapi_device_registry_dispatch.c>
#include <rapi_device_procman_dispatch.c>
#include <rapi_device_fileman_dispatch.c>
#include <rapi_device_system_dispatch.c>

static int     rapi_device_connection_session_get_fd(AsmConnection* thiz)
{
	asm_return_val_if_fail(thiz != NULL, -1);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	return asm_stream_get_fd(priv->stream);
}

static AsmRet rapi_device_connection_session_dispatch(AsmConnection* thiz, unsigned int cmd)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	if(priv->on_command != NULL)
	{
		priv->on_command(priv->on_command_ctx, thiz, cmd, 1, 0);
	}

	switch(cmd)
	{
		case RAPI_COMMAND_START_REPLICATION: 
		{
			ret = rapi_device_connection_session_handle_start_replication(thiz);
			break;
		}
		default:
		{
			do
			{
				ret = rapi_device_connection_session_system_command_dispatch(thiz, cmd);
				if(ret != ASM_RET_UNHANDLED) break;
				ret = rapi_device_connection_session_registry_command_dispatch(thiz, cmd);
				if(ret != ASM_RET_UNHANDLED) break;
				ret = rapi_device_connection_session_procman_command_dispatch(thiz, cmd);
				if(ret != ASM_RET_UNHANDLED) break;
				ret = rapi_device_connection_session_fileman_command_dispatch(thiz, cmd);
				if(ret != ASM_RET_UNHANDLED) break;

				/*XXX: add other command at here.*/
			}
			while(0);
		}
	}

	if(ret != ASM_RET_UNHANDLED)
	{
		ret = rapi_stream_write(priv->stream, priv->output);
	}
	
	if(priv->on_command != NULL)
	{
		priv->on_command(priv->on_command_ctx, thiz, cmd, 0, ret);
	}

	return ret;
}

static AsmRet rapi_device_connection_session_process_event(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);

	PrivInfo* priv = (PrivInfo*)thiz->priv;
	
	unsigned int cmd = 0;
	ret = rapi_stream_read(priv->stream, priv->input);
	assert(ret == ASM_RET_OK || ret == ASM_RET_INVALID_FD);
	asm_output_buffer_reset(priv->output);

	if(ret == ASM_RET_OK)
	{
		ret = asm_input_buffer_read_uint32(priv->input, &cmd);
		assert(ret == ASM_RET_OK);

		if(ret == ASM_RET_OK)
		{
			rapi_device_connection_session_dispatch(thiz, cmd);
		}
	}
	else if(ret == ASM_RET_INVALID_FD)
	{
		thiz->destroy(thiz);
	}

	printf("%s:%d cmd=0x%02x ret=%d\n", __func__, __LINE__, cmd, ret);

	return ret;
}

static AsmRet rapi_device_connection_session_destroy(AsmConnection* thiz)
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	if(priv->on_destroy != NULL)
	{
		priv->on_destroy(priv->on_destroy_ctx, thiz);
	}

	asm_stream_destroy(priv->stream);
	priv->stream = NULL;
	
	asm_input_buffer_destroy(priv->input);
	priv->input = NULL;

	asm_output_buffer_destroy(priv->output);
	priv->output = NULL;

	memset(thiz, 0x00, sizeof(AsmConnection) + sizeof(PrivInfo));
	ASM_FREE(thiz);

	return ASM_RET_OK;
}

AsmRet rapi_device_connection_session_hook_destroy(AsmConnection* thiz, AsmHookFunc on_destroy, void* on_destroy_ctx)
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	
	priv->on_destroy = on_destroy;
	priv->on_destroy_ctx = on_destroy_ctx;

	return ASM_RET_OK;
}

AsmRet         rapi_device_connection_hook_command(AsmConnection* thiz, RapiDeviceCommandHookFunc on_command, void* ctx)
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	
	priv->on_command = on_command;
	priv->on_command_ctx = ctx;

	return ASM_RET_OK;
}

AsmConnection* rapi_device_connection_session_create(RapiDevice* device, AsmStream* stream, unsigned int req_id)
{
	AsmConnection* thiz = NULL;
	asm_return_val_if_fail(device != NULL && stream != NULL && req_id > 0, NULL);

	thiz = ASM_ALLOC(AsmConnection, sizeof(PrivInfo));
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	priv->device = device;
	priv->stream = stream;
	priv->req_id = priv->req_id;
	priv->input = asm_input_buffer_create(NULL, 0, ASM_ENDIAN_LITTLE, NULL);
	priv->output = asm_output_buffer_create(1024, ASM_ENDIAN_LITTLE);
	priv->registry = NULL;

	rapi_device_get_registry(device, &(priv->registry));
	rapi_device_get_procman(device, &(priv->procman));
	rapi_device_get_fileman(device, &(priv->fileman));
	rapi_device_get_system(device, &(priv->system));

	thiz->get_fd = rapi_device_connection_session_get_fd;
	thiz->process_event = rapi_device_connection_session_process_event;
	thiz->hook_destroy = rapi_device_connection_session_hook_destroy;
	thiz->destroy = rapi_device_connection_session_destroy;

	return thiz;
}
