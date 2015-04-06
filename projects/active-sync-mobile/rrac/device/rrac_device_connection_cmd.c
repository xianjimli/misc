/*
 * File:    rrac_device_connection_cmd.c
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
#include <rrac_lib.h>
#include <asm-stream-socket.h>
#include <rrac_device_connection_data.h>
#include <rrac_device_connection_cmd.h>

typedef struct _PrivInfo
{
	char* host;
	int   port;
	AsmStream* stream;

	RracDevice* device;
	AsmHookFunc on_destroy;
	void* on_destroy_ctx;

	AsmConnection* data_connection;
}PrivInfo;

static int     rrac_device_connection_cmd_get_fd(AsmConnection* thiz)
{
	asm_return_val_if_fail(thiz != NULL, -1);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	return asm_stream_get_fd(priv->stream);
}

AsmRet rrac_device_connection_cmd_send_command(AsmConnection* thiz, RracCommandHeader* command)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL && command != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	return rrac_write_command(priv->stream, command);
}

static AsmRet rrac_device_connection_cmd_handle_6f(AsmConnection* thiz, RracCommandHeader* command)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL && command != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	RracCommand6F* command_6f = (RracCommand6F*)command;

	switch(command_6f->subcommand)
	{
		case RRAC_SUB_CMD_RETRIEVE_TYPES:
		{
			RracRawObjectTypes* types = NULL;
			if(rrac_device_get_types(priv->device, &types) == ASM_RET_OK)
			{
				size_t length = sizeof(RracRawObjectTypes) + sizeof(RracRawObjectType) * types->nr;

				RracRetrieveTypesResp* resp = ASM_ALLOC(RracRetrieveTypesResp, sizeof(RracRawObjectTypes)
				                    + sizeof(RracRawObjectType) * types->nr);
				resp->command = RRAC_COMMAND_6F_RESP;
				resp->length = sizeof(RracRetrieveTypesResp) + length - sizeof(RracCommandHeader);
				resp->reply_to = RRAC_COMMAND_6F;

				memcpy(&(resp->types), types, length);

				ret = rrac_write_command(priv->stream, (RracCommandHeader*)resp);

				ASM_FREE(resp);
				ASM_FREE(types);
			}

			break;
		}
		default:
		{
			RracCommandGeneralResp resp = {0};
			resp.command = RRAC_COMMAND_6F_RESP;
			resp.length = sizeof(resp) - sizeof(RracCommandHeader);
			resp.reply_to = RRAC_COMMAND_6F;

			ret = rrac_write_command(priv->stream, (RracCommandHeader*)&resp);

			break;
		}
	}

	return ASM_RET_OK;
}

static AsmRet rrac_device_connection_cmd_send_event(AsmConnection* thiz, RracCommandHeader* command)
{
	asm_return_val_if_fail(thiz != NULL && command != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	return rrac_write_command(priv->stream, (RracCommandHeader*)command);
}

static AsmRet rrac_device_connection_cmd_handle_70(AsmConnection* thiz, RracCommandHeader* command)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL && command != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	RracCommandStartEvent* command_70 = (RracCommandStartEvent*)command;

	switch(command_70->subcommand)
	{
		case RRAC_SUB_CMD_START_EVENT:
		{
			RracCommandStartEventResp resp = {0};

			resp.command = RRAC_COMMAND_70_RESP;
			resp.length = sizeof(resp) - sizeof(RracCommandHeader);
			resp.reply_to = RRAC_COMMAND_70;
			ret = rrac_write_command(priv->stream, (RracCommandHeader*)&resp);
			
			rrac_device_start_event(priv->device, command_70->data, command_70->count,
				(RracDeviceSendEventFunc)rrac_device_connection_cmd_send_event, thiz);

			break;
		}
		default:break;
	}

	return ASM_RET_OK;
}

static AsmRet rrac_device_connection_cmd_handle_get_objects(AsmConnection* thiz, RracCommandHeader* command)
{
	RracCommandGetObjects* cmd = (RracCommandGetObjects*)command;
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	
	rrac_device_get_objects(priv->device, cmd->type, cmd->data, cmd->count, 
		(RracDeviceSendObjectFunc)rrac_device_connection_data_send_object, priv->data_connection);

	return ASM_RET_OK;
}

static AsmRet rrac_device_connection_cmd_handle_del_object(AsmConnection* thiz, RracCommandHeader* command)
{
	AsmRet ret = ASM_RET_FAIL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	RracCommandDelObject* cmd = (RracCommandDelObject*)command;

	ret = rrac_device_del_object(priv->device, cmd->type, cmd->id, cmd->flags);
	RracCommandDelObjectResp resp = {0};
	
	resp.command = RRAC_COMMAND_DEL_OBJECT_RESP;
	resp.length = sizeof(resp) - sizeof(RracCommandHeader);
	resp.type = cmd->type;
	resp.req_id = cmd->id;
	resp.resp_id =(ret == ASM_RET_OK ? cmd->id : -1);
	resp.flags  = 0x80000000 | cmd->flags;

	ret = rrac_device_connection_cmd_send_command(thiz, (RracCommandHeader*)&resp);

	printf("%s:%d: %d %d %d\n", __func__, __LINE__, cmd->id, resp.req_id, resp.resp_id);

	return ret;
}
static AsmRet rrac_device_connection_cmd_process_event(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	RracCommandHeader* command = NULL;

	if((ret = rrac_read_command(priv->stream, &command)) == ASM_RET_OK)
	{
		switch(command->command)
		{
			case RRAC_COMMAND_6F: ret = rrac_device_connection_cmd_handle_6f(thiz, command); break;
			case RRAC_COMMAND_70: ret = rrac_device_connection_cmd_handle_70(thiz, command); break;
			case RRAC_COMMAND_GET_OBJECTS: ret = rrac_device_connection_cmd_handle_get_objects(thiz, command); break;
			case RRAC_COMMAND_DEL_OBJECT: ret = rrac_device_connection_cmd_handle_del_object(thiz, command); break;
			default:break;
		}

		printf("%s:%d command=%x length=%x ret=%d\n", __func__, __LINE__, command->command, command->length, ret);

		ASM_FREE(command);
	}
	else
	{
		printf("%s: rrac_read_command failed.\n", __func__);
		asm_connection_destroy(thiz);
	}
	return ret;
}

static AsmRet 
rrac_device_connection_cmd_hook_destroy(AsmConnection* thiz, AsmHookFunc on_destroy, void* on_destroy_ctx)
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	priv->on_destroy = on_destroy;
	priv->on_destroy_ctx = on_destroy_ctx;

	return ASM_RET_OK;
}

static AsmRet rrac_device_connection_cmd_destroy(AsmConnection* thiz)
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	if(priv->on_destroy != NULL)
	{
		priv->on_destroy(priv->on_destroy_ctx, thiz);
	}

	ASM_FREE(priv->host);
	if(priv->stream != NULL)
	{
		asm_stream_destroy(priv->stream);
		priv->stream = NULL;
	}

	ASM_FREE(thiz);

	return ASM_RET_FAIL; 
}

AsmConnection* rrac_device_connection_cmd_create(const char* host, int port, RracDevice* device)
{
	AsmStream* stream = asm_stream_client_socket_create(host, port);

	asm_return_val_if_fail(stream >= 0, NULL);

	AsmConnection* thiz = (AsmConnection*)malloc(sizeof(AsmConnection) + sizeof(PrivInfo));
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	
	priv->host    = strdup(host);
	priv->port    = port;
	priv->stream = stream;
	priv->device  = device;
	priv->data_connection = NULL;

	thiz->get_fd    = rrac_device_connection_cmd_get_fd;
	thiz->process_event = rrac_device_connection_cmd_process_event;
	thiz->hook_destroy  = rrac_device_connection_cmd_hook_destroy;
	thiz->destroy       = rrac_device_connection_cmd_destroy;

	return thiz;
}

AsmRet rrac_device_connection_cmd_set_data_connection(AsmConnection* thiz, AsmConnection* data)
{
	asm_return_val_if_fail(thiz != NULL && data != NULL, ASM_RET_FAIL);

	PrivInfo* priv = (PrivInfo*)thiz->priv;

	priv->data_connection = data;

	return ASM_RET_OK;
}
