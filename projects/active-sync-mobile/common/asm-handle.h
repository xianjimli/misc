/*
 * File:    asm-handle.h
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

#include <asm-types.h>
#include <asm-macros.h>

#ifndef ASM_HANDLE_H
#define ASM_HANDLE_H

struct _AsmHandle;
typedef struct _AsmHandle AsmHandle;

typedef AsmRet (*AsmHandleGetHandleFunc)(AsmHandle* thiz,  void** handle);

typedef void (*AsmHandleDestroyFunc)(AsmHandle* thiz);

struct _AsmHandle
{
	AsmHandleGetHandleFunc get_handle;
	AsmHandleDestroyFunc destroy;
	char priv[0];
};

static inline AsmRet asm_handle_get_handle(AsmHandle* thiz,  void** handle)
{
	asm_return_val_if_fail(thiz != NULL && thiz->get_handle != NULL, ASM_RET_FAIL);

	return thiz->get_handle(thiz,  handle);
}

static inline void asm_handle_destroy(AsmHandle* thiz)
{
	asm_return_if_fail(thiz != NULL && thiz->destroy != NULL);
	thiz->destroy(thiz);

	return;
}
#endif/*ASM_HANDLE_H*/

