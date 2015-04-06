/*
 * File:    rapi_device_system_default.c
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

#include <rapi_test_data.h>
#include <rapi_device_system_default.h>

typedef struct _PrivInfo
{
	int dummy;
}PrivInfo;

static AsmRet rapi_device_system_default_get_store_info
	(RapiDeviceSystem* thiz, unsigned int* return_value,  RapiStoreInfo** store_info)
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	*store_info = ASM_ALLOC(RapiStoreInfo, 0);
	(*store_info)->used_size = TEST_DATA_STORAGE_USED_SIZE;
	(*store_info)->free_size = TEST_DATA_STORAGE_FREE_SIZE;

	*return_value = 1;
	printf("%s:%d %d\n", __func__, __LINE__, *return_value);
	return ASM_RET_OK;
}

static AsmRet rapi_device_system_default_get_system_info
	(RapiDeviceSystem* thiz, unsigned int* return_value, RapiSystemInfo* system_info, RapiSystemInfo** system_info_ret)
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	rapi_dump_system_info(system_info);

	*return_value = 1;
	printf("%s:%d %d\n", __func__, __LINE__, *return_value);

	return rapi_test_data_get_system_info(system_info_ret);
}

static AsmRet rapi_device_system_default_get_power_status
	(RapiDeviceSystem* thiz, unsigned int* return_value, unsigned int refresh, RapiSystemPowerStatus** power_status)
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	
	*return_value = 1;
	printf("%s:%d %d\n", __func__, __LINE__, *return_value);
	return rapi_test_data_get_power_status(power_status);
}

static AsmRet rapi_device_system_default_get_version_info
	(RapiDeviceSystem* thiz, unsigned int* return_value,  RapiVersionInfo** version_info)
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	
	*version_info = ASM_ALLOC(RapiVersionInfo, 0);
	rapi_test_data_get_version_info(*version_info);

	*return_value = 1;

	printf("%s:%d %d\n", __func__, __LINE__, *return_value);
	return ASM_RET_OK;
}

static AsmRet rapi_device_system_default_start_replication
	(RapiDeviceSystem* thiz, unsigned int* return_value )
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	*return_value = 1;
	printf("%s:%d %d\n", __func__, __LINE__, *return_value);

	return ASM_RET_OK;
}

static AsmRet rapi_device_system_default_start_sync
	(RapiDeviceSystem* thiz, unsigned int* return_value, WStr* params )
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	*return_value = 1;
	printf("%s:%d %d\n", __func__, __LINE__, *return_value);
	return ASM_RET_OK;
}

static AsmRet rapi_device_system_default_resume_sync
	(RapiDeviceSystem* thiz, unsigned int* return_value )
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	*return_value = 1;
	printf("%s:%d %d\n", __func__, __LINE__, *return_value);
	return ASM_RET_OK;
}

static AsmRet rapi_device_system_default_pause_sync
	(RapiDeviceSystem* thiz, unsigned int* return_value )
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	*return_value = 1;
	printf("%s:%d %d\n", __func__, __LINE__, *return_value);
	return ASM_RET_OK;
}

void rapi_device_system_default_destroy(RapiDeviceSystem* thiz)
{
	ASM_FREE(thiz);

	return;
}

RapiDeviceSystem* rapi_device_system_default_create(void)
{
	RapiDeviceSystem* thiz = (RapiDeviceSystem*)ASM_ALLOC(RapiDeviceSystem, sizeof(PrivInfo));
	thiz->get_store_info = rapi_device_system_default_get_store_info;
	thiz->get_system_info = rapi_device_system_default_get_system_info;
	thiz->get_power_status = rapi_device_system_default_get_power_status;
	thiz->get_version_info = rapi_device_system_default_get_version_info;
	thiz->start_replication = rapi_device_system_default_start_replication;
	thiz->start_sync = rapi_device_system_default_start_sync;
	thiz->resume_sync = rapi_device_system_default_resume_sync;
	thiz->pause_sync = rapi_device_system_default_pause_sync;
	thiz->destroy = rapi_device_system_default_destroy;

	return thiz;
}

