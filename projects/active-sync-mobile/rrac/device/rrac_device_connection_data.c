/*
 * File:    rrac_device_connection_data.c
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

typedef struct _PrivInfo
{
	char* host;
	int   port;
	AsmStream* stream;

	RracDevice* device;
	AsmHookFunc on_destroy;
	void* on_destroy_ctx;

	AsmConnection* cmd_connection;
}PrivInfo;

static int     rrac_device_connection_data_get_fd(AsmConnection* thiz)
{
	asm_return_val_if_fail(thiz != NULL, -1);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	return asm_stream_get_fd(priv->stream);
}

AsmRet rrac_device_connection_data_set_cmd_connection(AsmConnection* thiz, AsmConnection* cmd_connection)
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	priv->cmd_connection = cmd_connection;

	return ASM_RET_OK;
}
static AsmRet rrac_device_connection_data_process_event(AsmConnection* thiz)
{
	RracObject* object = NULL;
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	if(rrac_read_object(priv->stream, &object) == ASM_RET_OK)
	{
		ret = rrac_device_put_object(priv->device, object);
	
		RracCommandPutObjectResp resp = {0};
		resp.command = RRAC_COMMAND_PUT_OBJECT_RESP;
		resp.length = sizeof(resp) - sizeof(RracCommandHeader);
		resp.type = object->type;
		resp.req_id = object->id;
		resp.resp_id = (ret == ASM_RET_OK ? object->id : -1);
		resp.flags = object->flags;

		ret = rrac_device_connection_cmd_send_command(priv->cmd_connection, &resp);

		ASM_FREE(object);
	}
	else
	{
		asm_connection_destroy(thiz);
	}
	
	return ret;
}

static AsmRet 
rrac_device_connection_data_hook_destroy(AsmConnection* thiz, AsmHookFunc on_destroy, void* on_destroy_ctx)
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	priv->on_destroy = on_destroy;
	priv->on_destroy_ctx = on_destroy_ctx;

	return ASM_RET_OK;
}

AsmRet rrac_device_connection_data_send_object(AsmConnection* thiz, const RracObject* object)
{
	AsmRet ret = ASM_RET_FAIL;

	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	ret = rrac_write_object(priv->stream, object);

	return ret;
}

static AsmRet rrac_device_connection_data_destroy(AsmConnection* thiz)
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

AsmConnection* rrac_device_connection_data_create(const char* host, int port, RracDevice* device)
{
	AsmStream* stream = asm_stream_client_socket_create(host, port);

	asm_return_val_if_fail(stream >= 0, NULL);

	AsmConnection* thiz = ASM_ALLOC(AsmConnection, sizeof(PrivInfo));
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	
	priv->host    = strdup(host);
	priv->port    = port;
	priv->stream = stream;
	priv->device  = device;
	priv->cmd_connection = NULL;

	thiz->get_fd    = rrac_device_connection_data_get_fd;
	thiz->process_event = rrac_device_connection_data_process_event;
	thiz->hook_destroy  = rrac_device_connection_data_hook_destroy;
	thiz->destroy       = rrac_device_connection_data_destroy;

	return thiz;
}
