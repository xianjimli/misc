/*
 * File:    rapi_device_default.c
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

#include <string.h>
#include <rapi_device_registry_default.h>
#include <rapi_device_default.h>
#include <rapi_test_data.h>

typedef struct _PrivInfo
{
	unsigned int major;
	unsigned int minor;
	unsigned int build_number;
	unsigned int platform_id;

	WStr*  name;
	RapiDeviceGuid guid;
	unsigned int components_nr;
	RapiComponent components[4];
	RapiDeviceRegistry* registry;
	RapiDeviceFileman*  fileman;
	RapiDeviceProcman*  procman;
	RapiDeviceSystem*   system;
}PrivInfo;

static inline AsmRet rapi_device_default_get_registry(RapiDevice* thiz, RapiDeviceRegistry** registry)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL && registry != NULL, ret);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	*registry = priv->registry;
	ret = ASM_RET_OK;

	return ret;
}

static inline AsmRet rapi_device_default_get_fileman(RapiDevice* thiz, RapiDeviceFileman** fileman)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL && fileman != NULL, ret);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	*fileman = priv->fileman;
	ret = ASM_RET_OK;

	return ret;
}

static inline AsmRet rapi_device_default_get_procman(RapiDevice* thiz, RapiDeviceProcman** procman)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL && procman != NULL, ret);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	*procman = priv->procman;
	ret = ASM_RET_OK;

	return ret;
}
static inline AsmRet rapi_device_default_get_system(RapiDevice* thiz, RapiDeviceSystem** system)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL && system != NULL, ret);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	*system = priv->system;
	ret = ASM_RET_OK;

	return ret;
}

static AsmRet rapi_device_default_get_version(RapiDevice* thiz, RapiVersionInfo* version)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL && version != NULL, ret);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	memset(version, 0x00, sizeof(version));

	return rapi_test_data_get_version_info(version);
}

static AsmRet rapi_device_default_get_info(RapiDevice* thiz, RapiDeviceInfo* info)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL && info != NULL, ret);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	return rapi_test_data_get_device_info(info);
}

static AsmRet rapi_device_default_start_replication(RapiDevice* thiz, void* unused)
{
	AsmRet ret = ASM_RET_FAIL;

	assert(thiz != NULL);
	if(thiz != NULL)
	{
		PrivInfo* priv = (PrivInfo*)thiz->priv;
		ret = ASM_RET_OK;
	}
	
	return ret;
}

static AsmRet rapi_device_default_destroy(RapiDevice* thiz, void* unused)
{
	AsmRet ret = ASM_RET_FAIL;

	if(thiz != NULL)
	{
		PrivInfo* priv = (PrivInfo*)thiz->priv;
		rapi_device_registry_destroy(priv->registry);
		rapi_device_procman_destroy(priv->procman);
		rapi_device_fileman_destroy(priv->fileman);
		rapi_device_system_destroy(priv->system);

		ASM_FREE(thiz);
	}
	
	return ret;
}

RapiDevice* rapi_device_default_create(void)
{
	size_t i = 0;
	RapiDevice* thiz = (RapiDevice*)malloc(sizeof(RapiDevice) + sizeof(PrivInfo));
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	
	priv->major = 1;
	priv->minor = 2;
	priv->build_number = 3;
	priv->platform_id = 4;
	priv->guid.data1 = 0x11223344;
	priv->guid.data2 = 0x5566;
	priv->guid.data3 = 0x7788;
	strncpy(priv->guid.data4, "bronchom", 8);
	priv->components_nr = sizeof(priv->components)/sizeof(priv->components[0]);

	for(i = 0; i < priv->components_nr; i++)
	{
		priv->components[i].l = i;
		priv->components[i].h = i;
	}

	priv->registry = rapi_device_registry_default_create();
	priv->procman  = rapi_device_procman_default_create();
	priv->fileman  = rapi_device_fileman_default_create();
	priv->system   = rapi_device_system_default_create();

	thiz->get_registry = rapi_device_default_get_registry;
	thiz->get_procman  = rapi_device_default_get_procman;
	thiz->get_fileman  = rapi_device_default_get_fileman;
	thiz->get_system   = rapi_device_default_get_system;

	thiz->get_info = rapi_device_default_get_info;
	thiz->destroy  = rapi_device_default_destroy;

	return thiz;
}

