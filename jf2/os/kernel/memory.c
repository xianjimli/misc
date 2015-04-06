/*
 * File:   memory.h 
 * Author: Li XianJing <xianjimli@hotmail.com>
 * Brief:  memory manager.
 *
 * Copyright (c) 2009  Li XianJing
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
 * 2009-1-28 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include <jtype.h>

typedef struct _MemInfo
{
	char*  start;
	jword_t length;
}MemInfo;

static MemInfo g_mem_info = {0};

JRet kernel_mem_init(char* start, jword_t length)
{
	return JRET_OK;
}

void* kernel_mem_alloc(jword_t length)
{
	return NULL;
}

void kernel_mem_free(void* ptr)
{
	return;
}

void* kernel_mem_realloc(void* ptr, jword_t length)
{
	return NULL;
}

