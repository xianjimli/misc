/*
 * File:    asm-handle-thread.c
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

#include <sys/types.h>
#include <signal.h>

#include <asm-handle-thread.h>

typedef struct _PrivInfo
{
	int thread;
	char* thread_name;
}PrivInfo;

static AsmRet asm_handle_thread_get_handle(AsmHandle* thiz,  void** handle)
{
	asm_return_val_if_fail(thiz != NULL && handle != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	
	*handle = priv->thread;

	return ASM_RET_OK;
}

void asm_handle_thread_destroy(AsmHandle* thiz)
{
	if(thiz != NULL)
	{
		PrivInfo* priv = (PrivInfo*)thiz->priv;
		printf("%s:%d close(%p) :%s\n", __func__, __LINE__, priv->thread, priv->thread_name);
		
		ASM_FREE(priv->thread_name);
		ASM_FREE(thiz);
	}

	return;
}

AsmHandle* asm_handle_thread_create(int thread, const char* thread_name)
{
	asm_return_val_if_fail(thread_name != NULL, NULL);

	AsmHandle* thiz = (AsmHandle*)ASM_ALLOC(AsmHandle, sizeof(PrivInfo));
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	
	priv->thread = thread;
	priv->thread_name = strdup(thread_name);

	thiz->get_handle = asm_handle_thread_get_handle;
	thiz->destroy = asm_handle_thread_destroy;
	
	return thiz;
}

