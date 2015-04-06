/*
 * lrc_type.h
 * Copyright (C) 2006-2009 Li XianJing <xianjimli@hotmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330, 
 * Boston, MA 02111-1307, USA.
 */


#ifndef LRC_TYPE_H
#define LRC_TYPE_H

#include <stddef.h>
#include <assert.h>
#include <stdio.h>

enum _LRC_RESULT
{
	LRC_RESULT_OK,
	LRC_RESULT_FAIL,
	LRC_RESULT_NR
};

typedef enum _LRC_RESULT LRC_RESULT;


typedef int  (*LrcItemCompareFunc)(void* data, void* user_data);
typedef void (*LrcItemDestroyFunc)(void* data);
typedef void (*LrcDestroyFunc)(void* data);

#define LRC_ASSERT(p) assert(p)
#define LRC_ALLOC(type, n) (type*)calloc(sizeof(type), n)
#define LRC_CALLOC(size, n) calloc(size, n)
#define LRC_MALLOC(size) malloc(size)
#define LRC_FREE(p) if(p != NULL) { free(p); p = NULL;}

#define return_if_fail(p) if(!(p)){\
	fprintf(stderr, "%s:%d return;", __func__, __LINE__); return;}
#define return_val_if_fail(p, val) if(!(p)){\
	fprintf(stderr, "%s:%d return;", __func__, __LINE__); return val;}

struct _Lrc;
typedef struct _Lrc Lrc;
#endif/*LRC_TYPE_H*/


