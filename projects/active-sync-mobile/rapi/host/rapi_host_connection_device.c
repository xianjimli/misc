/*
 * File:    rapi_host_connection_device.c
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
#include <rapi_host_connection_device.h>
#include <rapi_host_connection_session.h>

static AsmRet rapi_host_connection_device_handle_hand_shake(AsmConnection* thiz);

typedef struct _PrivInfo
{
	AsmStream*       stream;
	AsmInputBuffer*  input;
	AsmOutputBuffer* output;

	AsmHookFunc on_destroy;
	void*       on_destroy_ctx;

	AsmHookFunc pending_request_hook[RAPI_MAX_SESSION_NR];
	void*       pending_request_hook_ctx[RAPI_MAX_SESSION_NR];
	
	int request_count;

	RapiDeviceInfo device_info;
}PrivInfo;

static int     rapi_host_connection_device_get_fd(AsmConnection* thiz)
{
	asm_return_val_if_fail(thiz != NULL, -1);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	return asm_stream_get_fd(priv->stream);
}

static int rapi_host_connection_device_get_free_slot(AsmConnection* thiz)
{
	asm_return_val_if_fail(thiz != NULL, -1);
	
	size_t i = 0;
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	
	for(i = 0; i < RAPI_MAX_SESSION_NR; i++)
	{
		if(priv->pending_request_hook[i] == NULL)
		{
			return i;
		}
	}

	return -1;
}

static AsmRet rapi_host_connection_device_process_event(AsmConnection* thiz)
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	return ASM_RET_OK;
}

static AsmRet rapi_host_connection_device_destroy(AsmConnection* thiz)
{
	size_t i = 0;
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	asm_stream_destroy(priv->stream);
	priv->stream = NULL;

	ASM_FREE(priv->device_info.name);
	ASM_FREE(priv->device_info.platform);
	ASM_FREE(priv->device_info.model);
	ASM_FREE(priv->device_info.components);

	ASM_FREE(thiz);

	return ASM_RET_OK;
}

static AsmRet 
rapi_host_connection_device_hook_destroy(AsmConnection* thiz, AsmHookFunc on_destroy, void* on_destroy_ctx)
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	
	priv->on_destroy = on_destroy;
	priv->on_destroy_ctx = on_destroy_ctx;

	return ASM_RET_OK;
}

AsmConnection* rapi_host_connection_device_create(AsmStream* stream)
{
	asm_return_val_if_fail(stream != NULL, NULL);

	AsmConnection* thiz = ASM_ALLOC(AsmConnection, sizeof(PrivInfo));

	PrivInfo* priv = (PrivInfo*)thiz->priv;

	priv->stream = stream;
	priv->request_count = 1;

	thiz->get_fd        = rapi_host_connection_device_get_fd;
	thiz->process_event = rapi_host_connection_device_process_event;
	thiz->hook_destroy  = rapi_host_connection_device_hook_destroy;
	thiz->destroy       = rapi_host_connection_device_destroy;

	if(rapi_host_connection_device_handle_hand_shake(thiz) != ASM_RET_OK)
	{
		asm_connection_destroy(thiz);
		thiz = NULL;
	}

	return thiz;
}

typedef enum {
    RAPI_HOST_STATE_HANDSHAKE,
    RAPI_HOST_STATE_GETTING_INFO,
    RAPI_HOST_STATE_GOT_INFO,
    RAPI_HOST_STATE_AUTH,
    RAPI_HOST_STATE_CONNECTED,
} RapiHostState;

static AsmRet rapi_host_connection_device_parse_device_info(AsmConnection* thiz, AsmInputBuffer* input)
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	return rapi_buffer_read_info(input, &(priv->device_info));
}

static AsmRet rapi_host_connection_device_handle_hand_shake(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	asm_return_val_if_fail(priv->stream != NULL, ASM_RET_OK);

	int length = 0;
	unsigned int cmd = 0;
	unsigned int resp = 0;
	AsmInputBuffer* input = NULL;
	do
	{
		ret = asm_stream_read(priv->stream, &cmd, sizeof(cmd), &length);
		if(ret != ASM_RET_OK || cmd != RAPI_COMMAND_HAND_SHAKE) break;	

		resp = RAPI_RESP_HAND_SHAKE;
		ret = asm_stream_write(priv->stream, &resp, sizeof(resp), &length);
		if(ret != ASM_RET_OK) break;
	
		ret = asm_stream_read(priv->stream, &cmd, sizeof(cmd), &length);
		if(ret != ASM_RET_OK || cmd != RAPI_RESP_GET_INFO) break;
		
		input = asm_input_buffer_create(NULL, 0, ASM_ENDIAN_LITTLE, NULL);
		ret = rapi_stream_read(priv->stream, input);
		if(ret != ASM_RET_OK) break;
		ret = rapi_host_connection_device_parse_device_info(thiz, input);
	}while(0);
	
	if(ret != ASM_RET_OK)
	{
		asm_stream_destroy(priv->stream);
		priv->stream = NULL;
		printf("%s:%d hand shake failed.\n", __func__, __LINE__);
	}
	asm_input_buffer_destroy(input);

	return ASM_RET_OK;
}

AsmRet rapi_host_connection_device_get_device_info(AsmConnection* thiz, RapiDeviceInfo* device_info)
{
	asm_return_val_if_fail(thiz != NULL && device_info != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	*device_info = priv->device_info;

	return ASM_RET_OK;
}

AsmRet rapi_host_connection_device_on_new_session(AsmConnection* thiz, AsmStream* stream)
{
	size_t i = 0;
	asm_return_val_if_fail(thiz != NULL && stream != NULL, ASM_RET_FAIL);

	PrivInfo* priv = (PrivInfo*)thiz->priv;

	for(i = 0; i < RAPI_MAX_SESSION_NR; i++)
	{
		if(priv->pending_request_hook[i] != NULL)
		{
			AsmConnection* session = rapi_host_connection_session_create(stream, 0);

			priv->pending_request_hook[i](priv->pending_request_hook_ctx[i], session);
			priv->pending_request_hook[i] = NULL;
			priv->pending_request_hook_ctx[i] = NULL;

			break;
		}
	}

	return ASM_RET_OK;
}

AsmRet rapi_host_connection_device_request_new_session(AsmConnection* thiz, AsmHookFunc hook, void* hook_ctx)
{
	int index = rapi_host_connection_device_get_free_slot(thiz);
	asm_return_val_if_fail(thiz != NULL && hook != NULL && index >= 0, ASM_RET_FAIL);

	PrivInfo* priv = (PrivInfo*)thiz->priv;

	int length = 0;
	unsigned int request[3] = {0};

	request[0] = ASM_TO_LE32(5);
	request[1] = ASM_TO_LE32(4);
	request[2] = ASM_TO_LE32(priv->request_count);

	asm_stream_write(priv->stream, request, sizeof(request), &length); 
	asm_return_val_if_fail(length == sizeof(request), ASM_RET_FAIL);

	priv->pending_request_hook[index]     = hook;
	priv->pending_request_hook_ctx[index] = hook_ctx;

	priv->request_count++;
	return ASM_RET_OK;
}

