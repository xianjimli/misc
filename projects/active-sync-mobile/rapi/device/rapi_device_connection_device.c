/*
 * File:    rapi_device_connection_device.c
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
#include <asm-types.h>
#include <asm-input-buffer.h>
#include <asm-output-buffer.h>
#include <rapi_device_connection_device.h>
#include <rapi_device_connection_session.h>

typedef struct _PrivInfo
{
	RapiDevice*      device;
	AsmInputBuffer*  input;
	AsmOutputBuffer* output;
	char* host;
	int   port;

	AsmHookFunc on_destroy;
	void*       on_destroy_ctx;

	AsmHookFunc on_connection_change;
	void*       on_connection_change_ctx;
	AsmConnection* connections[RAPI_MAX_SESSION_NR];

	AsmStream* stream;
}PrivInfo;

static int     rapi_device_connection_device_get_fd(AsmConnection* thiz)
{
	asm_return_val_if_fail(thiz != NULL, -1);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	return asm_stream_get_fd(priv->stream);
}

static size_t   rapi_device_connection_device_get_free_slot(AsmConnection* thiz)
{
	asm_return_val_if_fail(thiz != NULL, RAPI_MAX_SESSION_NR);
	
	size_t i = 0;
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	
	for(i = 0; i < RAPI_MAX_SESSION_NR; i++)
	{
		if(priv->connections[i] == NULL)
		{
			break;
		}
	}

	return i;
}

static AsmRet rapi_device_connection_device_on_connection_broken(AsmConnection* thiz, AsmConnection* connection)
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	
	size_t i = 0;
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	
	for(i = 0; i < RAPI_MAX_SESSION_NR; i++)
	{
		if(priv->connections[i] == connection)
		{
			priv->connections[i] = NULL;
			if(priv->on_connection_change != NULL)
			{
				priv->on_connection_change(priv->on_connection_change_ctx, thiz);
			}
			
			printf("%s: remove %p\n", __func__, connection);
			break;
		}
	}

	return ASM_RET_OK;
}

static AsmRet rapi_device_connection_device_process_event(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);

	PrivInfo* priv = (PrivInfo*)thiz->priv;
	unsigned int req[3] = {0};
	size_t       length = 0;
	ret = asm_stream_read(priv->stream, req, sizeof(req), &length);
	assert(length == sizeof(req) || length == 0);

	if(length == 0)
	{
		printf("%s:%d: connection=%p is broken.\n", __func__, __LINE__, thiz);
		asm_connection_destroy(thiz);
		return ASM_RET_FAIL;
	}

	size_t slot = rapi_device_connection_device_get_free_slot(thiz);

	if(slot < RAPI_MAX_SESSION_NR)
	{
		AsmStream* new_stream = asm_stream_client_socket_create(priv->host, priv->port);
		asm_stream_write(new_stream, req+2, sizeof(req[2]), &length);
		assert(length == sizeof(req[2]));

		priv->connections[slot] = rapi_device_connection_session_create(priv->device, new_stream, req[2]); 
		if(priv->on_connection_change != NULL)
		{
			priv->on_connection_change(priv->on_connection_change_ctx, thiz);
		}
		rapi_device_connection_session_hook_destroy(priv->connections[slot],
			(AsmHookFunc)rapi_device_connection_device_on_connection_broken, thiz);
	}
	
	return ASM_RET_OK;
}

static AsmRet rapi_device_connection_device_hand_shake(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ret);

	PrivInfo* priv = (PrivInfo*)thiz->priv;
	RapiDeviceInfo info = {0};
	size_t length = 0;
	unsigned int cmd = 0;
	unsigned int resp = 0;

	asm_output_buffer_reset(priv->output);
	cmd = uint32_to_endian(RAPI_COMMAND_HAND_SHAKE, ASM_ENDIAN_LITTLE);

	ret = asm_stream_write(priv->stream, &cmd, sizeof(cmd), &length);
	assert(length == sizeof(cmd));

	ret = asm_stream_read(priv->stream, &resp, sizeof(resp), &length);
	assert(length == sizeof(resp));
	assert(resp == RAPI_RESP_HAND_SHAKE);

	cmd = uint32_to_endian(RAPI_RESP_GET_INFO, ASM_ENDIAN_LITTLE);
	ret = asm_stream_write(priv->stream, &cmd, sizeof(cmd), &length);
	assert(length == sizeof(cmd));

	if(rapi_device_get_info(priv->device, &info) == ASM_RET_OK)
	{
		if(rapi_buffer_write_info(priv->output, &info) == ASM_RET_OK)
		{
			ret = rapi_stream_write(priv->stream, priv->output);
		}
	}

	return ret;
}

static AsmRet rapi_device_connection_device_destroy(AsmConnection* thiz)
{
	size_t i = 0;
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	if(priv->on_destroy != NULL)
	{
		priv->on_destroy(priv->on_destroy_ctx, thiz);
	}

	for(i = 0; i < RAPI_MAX_SESSION_NR; i++)
	{
		if(priv->connections[i] != NULL)
		{
			asm_connection_destroy(priv->connections[i]);
			priv->connections[i] = NULL;
		}
	}
	asm_stream_destroy(priv->stream);
	priv->stream = NULL;
	
	asm_input_buffer_destroy(priv->input);
	priv->input = NULL;

	asm_output_buffer_destroy(priv->output);
	priv->output = NULL;

	ASM_FREE(priv->host);
	priv->host = NULL;

	memset(thiz, 0x00, sizeof(AsmConnection) + sizeof(PrivInfo));
	ASM_FREE(thiz);

	return ASM_RET_OK;
}

AsmRet rapi_device_connection_device_hook_connection_change(AsmConnection* thiz, 
	AsmHookFunc on_connection_change, void* on_connection_change_ctx)
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);

	PrivInfo* priv = (PrivInfo*)thiz->priv;
	priv->on_connection_change = on_connection_change;
	priv->on_connection_change_ctx = on_connection_change_ctx;

	return ASM_RET_OK;
}

AsmRet rapi_device_connection_device_get_connections(AsmConnection* thiz, AsmConnection** connections, size_t connections_nr)
{
	size_t i = 0;
	size_t j = 0;
	asm_return_val_if_fail(thiz != NULL && connections != NULL && connections_nr > 0, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	for(i = 0, j = 0; i < connections_nr && j < RAPI_MAX_SESSION_NR; j++)
	{
		if(priv->connections[j] != NULL)
		{
			connections[i] = priv->connections[j];
			i++;
		}
	}
	
	for(; i < connections_nr; i++)
	{
		connections[i] = NULL;
	}

	return ASM_RET_OK;
}

static AsmRet 
rapi_device_connection_device_hook_destroy(AsmConnection* thiz, AsmHookFunc on_destroy, void* on_destroy_ctx)
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	
	priv->on_destroy = on_destroy;
	priv->on_destroy_ctx = on_destroy_ctx;

	return ASM_RET_OK;
}

AsmConnection* rapi_device_connection_device_create(RapiDevice* device, const char* host, int port)
{
	AsmConnection* thiz = NULL;
	asm_return_val_if_fail(device != NULL && host != NULL && port > 0, NULL);
	AsmStream* stream = asm_stream_client_socket_create(host, port);
	asm_return_val_if_fail(stream, NULL);

	thiz = ASM_ALLOC(AsmConnection, sizeof(PrivInfo));
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	priv->device = device;
	priv->input = asm_input_buffer_create(NULL, 0, ASM_ENDIAN_LITTLE, NULL);
	priv->output = asm_output_buffer_create(1024, ASM_ENDIAN_LITTLE);
	priv->stream = stream;
	priv->host = strdup(host);
	priv->port = port;

	thiz->get_fd = rapi_device_connection_device_get_fd;
	thiz->process_event = rapi_device_connection_device_process_event;
	thiz->hook_destroy = rapi_device_connection_device_hook_destroy;
	thiz->destroy = rapi_device_connection_device_destroy;

	rapi_device_connection_device_hand_shake(thiz);

	return thiz;
}
