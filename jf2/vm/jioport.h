/*
 * File:    jioport.h
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   io port interface.
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
 * 2009-1-25 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#ifndef JF2_IOPORT_H
#define JF2_IOPORT_H
#include <jtype.h>

struct _JIoPort;
typedef struct _JIoPort JIoPort;

typedef void*  (*JIoPortGetBaseFunc)(JIoPort* thiz);
typedef size_t (*JIoPortGetSizeFunc)(JIoPort* thiz);
typedef JRet   (*JIoPortWriteFunc)(JIoPort* thiz, jword_t addr, jword_t data);
typedef JRet   (*JIoPortReadFunc)(JIoPort* thiz,  jword_t addr, jword_t* data);
typedef void   (*JIoPortDestroyFunc)(JIoPort* thiz);

struct _JIoPort
{
	JIoPortGetBaseFunc get_base;
	JIoPortGetSizeFunc get_size;
	JIoPortWriteFunc   write;
	JIoPortReadFunc    read;
	JIoPortDestroyFunc destroy;

	char priv[0];
};

static inline void* jioport_get_base(JIoPort* thiz)
{
	j_ret_val_if_fail(thiz != NULL && thiz->get_base != NULL, NULL);

	return thiz->get_base(thiz);
}

static inline size_t     jioport_get_size(JIoPort* thiz)
{
	j_ret_val_if_fail(thiz != NULL && thiz->get_size != NULL, 0);

	return thiz->get_size(thiz);
}

static inline JRet jioport_check_addr(JIoPort* thiz, jword_t addr)
{
	size_t low = (size_t)jioport_get_base(thiz);
	size_t high = low + jioport_get_size(thiz);

	return ((size_t)addr >= low && (size_t)addr < high) ? JRET_OK : JRET_FAIL;
}

static inline JRet jioport_write(JIoPort* thiz, jword_t addr, jword_t data)
{
	j_ret_val_if_fail(thiz != NULL && thiz->write != NULL, JRET_INVALID_PARAM);

	return thiz->write(thiz, addr, data);
}

static inline JRet jioport_read(JIoPort* thiz,  jword_t addr, jword_t* data)
{
	j_ret_val_if_fail(thiz != NULL && thiz->read != NULL, JRET_INVALID_PARAM);

	return thiz->read(thiz, addr, data);
}

static inline void jioport_destroy(JIoPort* thiz)
{
	j_ret_if_fail(thiz != NULL && thiz->destroy != NULL);

	thiz->destroy(thiz);

	return;
}

#endif/*JF2_IOPORT_H*/


