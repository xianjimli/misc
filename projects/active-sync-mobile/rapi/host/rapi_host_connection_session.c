/*
 * File:    rapi_host_connection_session.c
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

#include <asm-input-buffer.h>
#include <asm-output-buffer.h>
#include <rapi_host_connection_session.h>

typedef struct _PrivInfo
{
	unsigned int     req_id;

	AsmStream* stream;

	AsmHookFunc on_destroy;
	void*       on_destroy_ctx;

}PrivInfo;

static int     rapi_host_connection_session_get_fd(AsmConnection* thiz)
{
	asm_return_val_if_fail(thiz != NULL, -1);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	return asm_stream_get_fd(priv->stream);
}

AsmStream*     rapi_host_connection_session_get_stream(AsmConnection* thiz)
{
	asm_return_val_if_fail(thiz != NULL, -1);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	return priv->stream;
}

static AsmRet rapi_host_connection_session_process_event(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);

	return ret;
}

static AsmRet rapi_host_connection_session_destroy(AsmConnection* thiz)
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	if(priv->on_destroy != NULL)
	{
		priv->on_destroy(priv->on_destroy_ctx, thiz);
	}

	asm_stream_destroy(priv->stream);
	priv->stream = NULL;

	ASM_FREE(thiz);

	return ASM_RET_OK;
}

AsmRet rapi_host_connection_session_hook_destroy(AsmConnection* thiz, AsmHookFunc on_destroy, void* on_destroy_ctx)
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	
	priv->on_destroy = on_destroy;
	priv->on_destroy_ctx = on_destroy_ctx;

	return ASM_RET_OK;
}

AsmConnection* rapi_host_connection_session_create(AsmStream* stream, unsigned int req_id)
{
	AsmConnection* thiz = NULL;
	unsigned int req_id_from_device = 0;
	int length = 0;
	asm_return_val_if_fail(stream != NULL, NULL);

	asm_stream_read(stream, &req_id_from_device, sizeof(req_id_from_device), &length);	
	asm_return_val_if_fail(length == sizeof(req_id_from_device), NULL);

	thiz = ASM_ALLOC(AsmConnection, sizeof(PrivInfo));
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	priv->stream   = stream;
	priv->req_id   = priv->req_id;

	thiz->get_fd        = rapi_host_connection_session_get_fd;
	thiz->process_event = rapi_host_connection_session_process_event;
	thiz->hook_destroy  = rapi_host_connection_session_hook_destroy;
	thiz->destroy       = rapi_host_connection_session_destroy;

	printf("%s:%d req_id=%d\n", __func__, __LINE__, req_id);
	return thiz;
}

