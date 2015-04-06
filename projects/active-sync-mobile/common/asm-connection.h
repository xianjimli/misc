/*
 * File:    asm-connection.h
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

#include <asm-common.h>

#ifndef _ASM_CONNECTION_H
#define _ASM_CONNECTION_H

struct _AsmConnection;
typedef struct _AsmConnection AsmConnection;

typedef int     (*AsmConnectionGetSocketFunc)(AsmConnection* thiz);
typedef AsmRet (*AsmConnectionProcessEventFunc)(AsmConnection* thiz);
typedef AsmRet (*AsmConnectionHookDestroyFunc)(AsmConnection* thiz, AsmHookFunc on_destroy, void* ctx);
typedef AsmRet (*AsmConnectionDestroyFunc)(AsmConnection* thiz);

struct _AsmConnection
{
	AsmConnectionGetSocketFunc     get_fd;
	AsmConnectionProcessEventFunc  process_event;
	AsmConnectionHookDestroyFunc   hook_destroy;
	AsmConnectionDestroyFunc       destroy;

	char priv[0];
};

static inline int asm_connection_get_fd(AsmConnection* thiz)
{
	asm_return_val_if_fail(thiz != NULL && thiz->get_fd != NULL, -1);

	return thiz->get_fd(thiz);
}

static inline AsmRet asm_connection_process_event(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;

	asm_return_val_if_fail(thiz != NULL && thiz->process_event != NULL, ret);

	return thiz->process_event(thiz);
}

static inline AsmRet asm_connection_hook_destroy(AsmConnection* thiz, AsmHookFunc on_destroy, void* ctx)
{
	AsmRet ret = ASM_RET_FAIL;

	asm_return_val_if_fail(thiz != NULL && thiz->hook_destroy != NULL, ASM_RET_FAIL);

	return thiz->hook_destroy(thiz, on_destroy, ctx);
}

static inline AsmRet asm_connection_destroy(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;

	asm_return_val_if_fail(thiz != NULL && thiz->destroy != NULL, ASM_RET_FAIL);
	
	return thiz->destroy(thiz);
}

#endif/*_ASM_CONNECTION_H*/

