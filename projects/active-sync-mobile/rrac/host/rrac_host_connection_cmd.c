/*
 * File:    rrac_host_connection_cmd.c
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

#include <rrac_host_connection_cmd.h>

typedef struct _PrivInfo
{
	AsmStream* stream;
	AsmHookFunc on_destroy;
	void* on_destroy_ctx;
}PrivInfo;

static int     rrac_host_connection_cmd_get_fd(AsmConnection* thiz)
{
	asm_return_val_if_fail(thiz != NULL, -1);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	return asm_stream_get_fd(priv->stream);
}

static AsmRet rrac_host_connection_cmd_process_event(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	
	printf("%s: don't call this function.\n", __func__);

	return ret;
}

static AsmRet
rrac_host_connection_cmd_hook_destroy(AsmConnection* thiz, AsmHookFunc on_destroy, void* on_destroy_ctx)
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	
	priv->on_destroy = on_destroy;
	priv->on_destroy_ctx = on_destroy_ctx;

	return ASM_RET_OK;
}

static AsmRet rrac_host_connection_cmd_destroy(AsmConnection* thiz)
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	
	if(priv->on_destroy != NULL)
	{
		priv->on_destroy(priv->on_destroy_ctx, thiz);
		priv->on_destroy = NULL;
	}

	if(priv->stream != NULL)
	{
		asm_stream_destroy(priv->stream);
		priv->stream = NULL;
	}

	ASM_FREE(thiz);

	return ASM_RET_OK;
}

AsmRet rrac_host_connection_cmd_send_command(AsmConnection* thiz, RracCommandHeader* command)
{
	asm_return_val_if_fail(thiz != NULL && command != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	return rrac_write_command(priv->stream, command);
}

AsmRet rrac_host_connection_cmd_read_resp(AsmConnection* thiz, unsigned int timeout_seconds, RracCommandHeader** resp)
{
	asm_return_val_if_fail(thiz != NULL && resp != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	
	asm_stream_set_time_out(priv->stream, timeout_seconds, 0);

	return rrac_read_command(priv->stream, resp);
}

AsmConnection* rrac_host_connection_cmd_create(AsmStream* stream)
{
	asm_return_val_if_fail(stream != NULL, NULL);
	AsmConnection* thiz = (AsmConnection*)malloc(sizeof(AsmConnection) + sizeof(PrivInfo));
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	priv->stream = stream;
	priv->on_destroy = NULL;
	priv->on_destroy_ctx = NULL;

	thiz->get_fd    = rrac_host_connection_cmd_get_fd;
	thiz->process_event = rrac_host_connection_cmd_process_event;
	thiz->hook_destroy  = rrac_host_connection_cmd_hook_destroy;
	thiz->destroy       = rrac_host_connection_cmd_destroy;

	return thiz;
}

