/*
 * File:    asm-types.h
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

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#ifndef ASM_TYPES_H
#define ASM_TYPES_H

typedef enum _AsmEndian
{
	ASM_ENDIAN_NONE,
	ASM_ENDIAN_BIG,
	ASM_ENDIAN_LITTLE,
	ASM_ENDIAN_NR
}AsmEndian;

typedef enum _AsmRet
{
	ASM_RET_OK,
	ASM_RET_FAIL,
	ASM_RET_INVALID_FD,
	ASM_RET_EOF,
	ASM_RET_EOO, /*END OF OBJECT*/
	ASM_RET_OOM,
	ASM_RET_UNHANDLED,
	ASM_RET_TIME_OUT,
	ASM_RET_NR
}AsmRet;

typedef struct _FileTime
{
	unsigned int low;
	unsigned int high;
}FileTime;

typedef unsigned short WStr;

typedef void (*AsmBufferFreeFunc)(void* p);
typedef AsmRet (*AsmHookFunc)(void* ctx, void* obj);
typedef void (*AsmHookProgressFunc)(void* ctx, int progress, int total);

static inline asm_call_on_progress(AsmHookProgressFunc hook, void* hook_ctx, int progress, int total)
{
	if(hook != NULL)
	{
		hook(hook_ctx, progress, total);
	}

	return;
}

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#define asm_return_val_if_fail(p, v) if(!(p)) { printf("%s:%d:("#p") failed.\n", __func__, __LINE__); return (v);};
#define asm_return_if_fail(p) if(!(p)) { printf("%s:%d:("#p") failed.\n", __func__, __LINE__); return;};
#define asm_break_if_fail(p) if(!(p)) {printf("%s:%d:("#p") failed.\n", __func__, __LINE__); break;}

#endif/*ASM_TYPES_H*/
