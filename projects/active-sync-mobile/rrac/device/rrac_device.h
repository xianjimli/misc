/*
 * File:    rrac_device.h
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

#include <rrac_lib.h>

#ifndef _RRAC_DEVICE_H
#define _RRAC_DEVICE_H

struct _RracDevice;
typedef struct _RracDevice RracDevice;

typedef AsmRet    (*RracDeviceSendEventFunc)(void* ctx, RracCommandHeader* command);
typedef AsmRet    (*RracDeviceSendObjectFunc)(void* ctx, RracObject* object);

typedef AsmRet    (*RracDeviceStartEventFunc)(RracDevice* thiz, 
					unsigned int* ignored_ids, 
					unsigned int ignored_ids_nr,
					RracDeviceSendEventFunc send_event, void* ctx);

typedef AsmRet    (*RracDeviceGetObjectsFunc)(RracDevice* thiz,
					unsigned int type,
					unsigned int* ids,
					unsigned int  ids_nr,
					RracDeviceSendObjectFunc send_object, void* ctx);

typedef AsmRet    (*RracDevicePutObjectFunc)(RracDevice* thiz, RracObject* object);
typedef AsmRet    (*RracDeviceGetTypesFunc)(RracDevice* thiz, RracRawObjectTypes** types);
typedef AsmRet    (*RracDeviceDelObjectFunc)(RracDevice* thiz, 
					unsigned int type, unsigned int id, unsigned int flags);

typedef AsmRet    (*RracDeviceDestroyFunc)(RracDevice* thiz, void* unused);

struct _RracDevice
{
	RracDeviceGetTypesFunc     get_types;
	RracDeviceStartEventFunc   start_event;
	RracDeviceGetObjectsFunc   get_objects;
	RracDevicePutObjectFunc    put_object;
	RracDeviceDelObjectFunc    del_object;
	RracDeviceDestroyFunc      destroy;

	char priv[0];
};

static inline AsmRet rrac_device_get_types(RracDevice* thiz, RracRawObjectTypes** types)
{
	asm_return_val_if_fail(thiz != NULL && thiz->get_types != NULL, ASM_RET_FAIL);

	return thiz->get_types(thiz, types);
}

static inline AsmRet rrac_device_put_object(RracDevice* thiz, RracObject* object)
{
	asm_return_val_if_fail(thiz != NULL && thiz->put_object != NULL, ASM_RET_FAIL);

	return thiz->put_object(thiz, object);
}

static inline AsmRet rrac_device_del_object(RracDevice* thiz, 
					unsigned int type, unsigned int id, unsigned int flags)
{
	asm_return_val_if_fail(thiz != NULL && thiz->del_object != NULL, ASM_RET_FAIL);

	return thiz->del_object(thiz, type, id, flags);
}
static inline AsmRet rrac_device_start_event(RracDevice* thiz, 
					unsigned int* ignored_ids, 
					unsigned int ignored_ids_nr,
					RracDeviceSendEventFunc send_event, void* ctx)
{
	asm_return_val_if_fail(thiz != NULL && thiz->start_event != NULL, ASM_RET_FAIL);

	return thiz->start_event(thiz, ignored_ids, ignored_ids_nr, send_event, ctx);
}

static inline AsmRet rrac_device_get_objects(RracDevice* thiz,
					unsigned int type,
					unsigned int* ids,
					unsigned int  ids_nr,
					RracDeviceSendObjectFunc send_object, void* ctx)
{
	asm_return_val_if_fail(thiz != NULL && thiz->get_objects != NULL, ASM_RET_FAIL);

	return thiz->get_objects(thiz, type, ids, ids_nr, send_object, ctx);
}
					
static inline AsmRet rrac_device_destroy(RracDevice* thiz, void* unused)
{
	asm_return_val_if_fail(thiz!= NULL && thiz->destroy != NULL, ASM_RET_FAIL);

	return thiz->destroy(thiz, unused);
}

#endif/*RRAC_DEVICE_H*/


