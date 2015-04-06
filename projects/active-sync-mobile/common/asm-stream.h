/*
 * File:    asm-stream.h
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
#ifndef ASM_STREAM_H
#define ASM_STREAM_H

struct _AsmStream;
typedef struct _AsmStream AsmStream;

typedef AsmRet (*AsmStreamReadFunc)(AsmStream* thiz, void* buffer, unsigned int length, unsigned int* real_length);
typedef AsmRet (*AsmStreamWriteFunc)(AsmStream* thiz, void* buffer, unsigned int length, unsigned int* real_length);
typedef AsmRet (*AsmStreamFlushFunc)(AsmStream* thiz );
typedef int    (*AsmStreamGetFdFunc)(AsmStream* thiz );
typedef AsmRet (*AsmStreamSetTimeOutFunc)(AsmStream* thiz, unsigned int rto_seconds, unsigned int wto_seconds );
typedef AsmRet (*AsmStreamHookWriteProgressFunc)(AsmStream* thiz, AsmHookProgressFunc on_progress, void* on_progress_ctx );
typedef AsmRet (*AsmStreamHookReadProgressFunc)(AsmStream* thiz, AsmHookProgressFunc on_progress, void* on_progress_ctx );

typedef void (*AsmStreamDestroyFunc)(AsmStream* thiz);

struct _AsmStream
{
	AsmStreamReadFunc read;
	AsmStreamWriteFunc write;
	AsmStreamFlushFunc flush;
	AsmStreamGetFdFunc get_fd;
	AsmStreamSetTimeOutFunc set_time_out;
	AsmStreamHookWriteProgressFunc hook_write_progress;
	AsmStreamHookReadProgressFunc hook_read_progress;
	AsmStreamDestroyFunc destroy;
	char priv[0];
};

static inline AsmRet asm_stream_read(AsmStream* thiz, void* buffer, unsigned int length, unsigned int* real_length)
{
	asm_return_val_if_fail(thiz != NULL && thiz->read != NULL, ASM_RET_FAIL);

	return thiz->read(thiz,  buffer,  length, real_length);
}

static inline AsmRet asm_stream_write(AsmStream* thiz, void* buffer, unsigned int length, unsigned int* real_length)
{
	asm_return_val_if_fail(thiz != NULL && thiz->write != NULL, ASM_RET_FAIL);

	return thiz->write(thiz,  buffer,  length, real_length);
}

static inline AsmRet asm_stream_flush(AsmStream* thiz )
{
	asm_return_val_if_fail(thiz != NULL && thiz->flush != NULL, ASM_RET_FAIL);

	return thiz->flush(thiz);
}

static inline int asm_stream_get_fd(AsmStream* thiz )
{
	asm_return_val_if_fail(thiz != NULL && thiz->get_fd != NULL, -1);

	return thiz->get_fd(thiz);
}

static inline AsmRet asm_stream_set_time_out(AsmStream* thiz, unsigned int rto_seconds, unsigned int wto_seconds )
{
	asm_return_val_if_fail(thiz != NULL && thiz->set_time_out != NULL, ASM_RET_FAIL);

	return thiz->set_time_out(thiz,  rto_seconds,  wto_seconds);
}

static inline AsmRet asm_stream_hook_write_progress(AsmStream* thiz, AsmHookProgressFunc on_progress, void* on_progress_ctx )
{
	asm_return_val_if_fail(thiz != NULL && thiz->hook_write_progress != NULL, ASM_RET_FAIL);

	return thiz->hook_write_progress(thiz,  on_progress,  on_progress_ctx);
}

static inline AsmRet asm_stream_hook_read_progress(AsmStream* thiz, AsmHookProgressFunc on_progress, void* on_progress_ctx )
{
	asm_return_val_if_fail(thiz != NULL && thiz->hook_read_progress != NULL, ASM_RET_FAIL);

	return thiz->hook_read_progress(thiz,  on_progress,  on_progress_ctx);
}

static inline void asm_stream_destroy(AsmStream* thiz)
{
	asm_return_if_fail(thiz != NULL && thiz->destroy != NULL);
	thiz->destroy(thiz);

	return;
}
#endif/*ASM_STREAM_H*/

