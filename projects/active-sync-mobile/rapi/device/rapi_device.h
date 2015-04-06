/*
 * File:    rapi_device.h
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

#include <rapi_lib.h>
#include <rapi_device_registry.h>
#include <rapi_device_procman.h>
#include <rapi_device_system.h>
#include <rapi_device_fileman.h>

#ifndef _RAPI_DEVICE_H
#define _RAPI_DEVICE_H

struct _RapiDevice;
typedef struct _RapiDevice RapiDevice;

typedef AsmRet    (*RapiDeviceGetRegistryFunc)(RapiDevice* thiz, RapiDeviceRegistry** registry);
typedef AsmRet    (*RapiDeviceGetFilemanFunc)(RapiDevice* thiz, RapiDeviceFileman** fileman);
typedef AsmRet    (*RapiDeviceGetProcManFunc)(RapiDevice* thiz, RapiDeviceProcman** procman);
typedef AsmRet    (*RapiDeviceGetSystemFunc)(RapiDevice* thiz, RapiDeviceSystem** system);

typedef AsmRet    (*RapiDeviceGetInfoFunc)(RapiDevice* thiz, RapiDeviceInfo* info);
typedef AsmRet    (*RapiDeviceDestroyFunc)(RapiDevice* thiz, void* unused);

struct _RapiDevice
{
	RapiDeviceGetRegistryFunc      get_registry;
	RapiDeviceGetFilemanFunc       get_fileman;
	RapiDeviceGetProcManFunc       get_procman;
	RapiDeviceGetSystemFunc        get_system;

	RapiDeviceGetInfoFunc          get_info;

	RapiDeviceDestroyFunc          destroy;
	char priv[0];
};

static inline AsmRet rapi_device_get_registry(RapiDevice* thiz, RapiDeviceRegistry** registry)
{
	asm_return_val_if_fail(thiz != NULL && thiz->get_registry != NULL, ASM_RET_FAIL);

	return thiz->get_registry(thiz, registry);
}

static inline AsmRet rapi_device_get_fileman(RapiDevice* thiz, RapiDeviceFileman** fileman)
{
	asm_return_val_if_fail(thiz != NULL && thiz->get_fileman != NULL, ASM_RET_FAIL);

	return thiz->get_fileman(thiz, fileman);
}

static inline AsmRet rapi_device_get_procman(RapiDevice* thiz, RapiDeviceProcman** procman)
{
	asm_return_val_if_fail(thiz != NULL && thiz->get_procman != NULL, ASM_RET_FAIL);

	return thiz->get_procman(thiz, procman);
}

static inline AsmRet rapi_device_get_system(RapiDevice* thiz, RapiDeviceSystem** system)
{
	asm_return_val_if_fail(thiz != NULL && thiz->get_system != NULL, ASM_RET_FAIL);

	return thiz->get_system(thiz, system);
}

static inline AsmRet rapi_device_get_info(RapiDevice* thiz, RapiDeviceInfo* info)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL && thiz->get_info != NULL, ASM_RET_FAIL);

	return thiz->get_info(thiz, info);
}

static inline AsmRet rapi_device_destroy(RapiDevice* thiz, void* unused)
{
 	asm_return_val_if_fail(thiz != NULL && thiz->destroy != NULL, ASM_RET_FAIL)

	return thiz->destroy(thiz, unused);
}

#endif/*RAPI_DEVICE_H*/

