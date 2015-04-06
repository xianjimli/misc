/*
 * File:    rapi_device_system.h
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
#include <rapi_lib.h>
#ifndef RAPI_DEVICE_SYSTEM_H
#define RAPI_DEVICE_SYSTEM_H

struct _RapiDeviceSystem;
typedef struct _RapiDeviceSystem RapiDeviceSystem;

typedef AsmRet (*RapiDeviceSystemGetStoreinfoFunc)
	(RapiDeviceSystem* thiz, unsigned int* return_value,  RapiStoreInfo** store_info);
typedef AsmRet (*RapiDeviceSystemGetSystemInfoFunc)
	(RapiDeviceSystem* thiz, unsigned int* return_value, RapiSystemInfo* system_info, RapiSystemInfo** system_info_ret);
typedef AsmRet (*RapiDeviceSystemGetPowerStatusFunc)
	(RapiDeviceSystem* thiz, unsigned int* return_value, unsigned int refresh, RapiSystemPowerStatus** power_status);
typedef AsmRet (*RapiDeviceSystemGetVersionInfoFunc)
	(RapiDeviceSystem* thiz, unsigned int* return_value,  RapiVersionInfo** version_info);
typedef AsmRet (*RapiDeviceSystemStartReplicationFunc)
	(RapiDeviceSystem* thiz, unsigned int* return_value );
typedef AsmRet (*RapiDeviceSystemStartSyncFunc)
	(RapiDeviceSystem* thiz, unsigned int* return_value, WStr* params );
typedef AsmRet (*RapiDeviceSystemResumeSyncFunc)
	(RapiDeviceSystem* thiz, unsigned int* return_value );
typedef AsmRet (*RapiDeviceSystemPauseSyncFunc)
	(RapiDeviceSystem* thiz, unsigned int* return_value );

typedef void (*RapiDeviceSystemDestroyFunc)(RapiDeviceSystem* thiz);

struct _RapiDeviceSystem
{
	RapiDeviceSystemGetStoreinfoFunc get_store_info;
	RapiDeviceSystemGetSystemInfoFunc get_system_info;
	RapiDeviceSystemGetPowerStatusFunc get_power_status;
	RapiDeviceSystemGetVersionInfoFunc get_version_info;
	RapiDeviceSystemStartReplicationFunc start_replication;
	RapiDeviceSystemStartSyncFunc start_sync;
	RapiDeviceSystemResumeSyncFunc resume_sync;
	RapiDeviceSystemPauseSyncFunc pause_sync;
	RapiDeviceSystemDestroyFunc destroy;
	char priv[0];
};

static inline AsmRet rapi_device_system_get_store_info
	(RapiDeviceSystem* thiz, unsigned int* return_value,  RapiStoreInfo** store_info)
{
	asm_return_val_if_fail(thiz != NULL && thiz->get_store_info != NULL, ASM_RET_FAIL);

	return thiz->get_store_info(thiz, return_value,  store_info);
}

static inline AsmRet rapi_device_system_get_system_info
	(RapiDeviceSystem* thiz, unsigned int* return_value, RapiSystemInfo* system_info, RapiSystemInfo** system_info_ret)
{
	asm_return_val_if_fail(thiz != NULL && thiz->get_system_info != NULL, ASM_RET_FAIL);

	return thiz->get_system_info(thiz, return_value,  system_info, system_info_ret);
}

static inline AsmRet rapi_device_system_get_power_status
	(RapiDeviceSystem* thiz, unsigned int* return_value, unsigned int refresh, RapiSystemPowerStatus** power_status)
{
	asm_return_val_if_fail(thiz != NULL && thiz->get_power_status != NULL, ASM_RET_FAIL);

	return thiz->get_power_status(thiz, return_value,  refresh, power_status);
}

static inline AsmRet rapi_device_system_get_version_info
	(RapiDeviceSystem* thiz, unsigned int* return_value,  RapiVersionInfo** version_info)
{
	asm_return_val_if_fail(thiz != NULL && thiz->get_version_info != NULL, ASM_RET_FAIL);

	return thiz->get_version_info(thiz, return_value,  version_info);
}

static inline AsmRet rapi_device_system_start_replication
	(RapiDeviceSystem* thiz, unsigned int* return_value )
{
	asm_return_val_if_fail(thiz != NULL && thiz->start_replication != NULL, ASM_RET_FAIL);

	return thiz->start_replication(thiz, return_value);
}

static inline AsmRet rapi_device_system_start_sync
	(RapiDeviceSystem* thiz, unsigned int* return_value, WStr* params )
{
	asm_return_val_if_fail(thiz != NULL && thiz->start_sync != NULL, ASM_RET_FAIL);

	return thiz->start_sync(thiz, return_value,  params);
}

static inline AsmRet rapi_device_system_resume_sync
	(RapiDeviceSystem* thiz, unsigned int* return_value )
{
	asm_return_val_if_fail(thiz != NULL && thiz->resume_sync != NULL, ASM_RET_FAIL);

	return thiz->resume_sync(thiz, return_value);
}

static inline AsmRet rapi_device_system_pause_sync
	(RapiDeviceSystem* thiz, unsigned int* return_value )
{
	asm_return_val_if_fail(thiz != NULL && thiz->pause_sync != NULL, ASM_RET_FAIL);

	return thiz->pause_sync(thiz, return_value);
}

static inline void rapi_device_system_destroy(RapiDeviceSystem* thiz)
{
	asm_return_if_fail(thiz != NULL && thiz->destroy != NULL);
	thiz->destroy(thiz);

	return;
}
#endif/*RAPI_DEVICE_SYSTEM_H*/

