/*
 * File:    rapi_device_registry.h
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
#ifndef RAPI_DEVICE_REGISTRY_H
#define RAPI_DEVICE_REGISTRY_H

struct _RapiDeviceRegistry;
typedef struct _RapiDeviceRegistry RapiDeviceRegistry;

typedef AsmRet (*RapiDeviceRegistryCreateKeyFunc)
	(RapiDeviceRegistry* thiz, unsigned int* return_value, RKEY key, WStr* sub_key, WStr* class_name, RKEY* result, unsigned int* disposition);
typedef AsmRet (*RapiDeviceRegistryOpenKeyFunc)
	(RapiDeviceRegistry* thiz, unsigned int* return_value, RKEY key, WStr* sub_key, RKEY* result);
typedef AsmRet (*RapiDeviceRegistryQueryValueFunc)
	(RapiDeviceRegistry* thiz, unsigned int* return_value, RKEY key, WStr* value_name, unsigned int data_length, unsigned int* type, unsigned int* ret_data_length, void** ret_data);
typedef AsmRet (*RapiDeviceRegistryCloseKeyFunc)
	(RapiDeviceRegistry* thiz, unsigned int* return_value, RKEY key );
typedef AsmRet (*RapiDeviceRegistryDeleteKeyFunc)
	(RapiDeviceRegistry* thiz, unsigned int* return_value, RKEY key, WStr* sub_key );
typedef AsmRet (*RapiDeviceRegistryDeleteValueFunc)
	(RapiDeviceRegistry* thiz, unsigned int* return_value, RKEY key, WStr* value_name );
typedef AsmRet (*RapiDeviceRegistryEnumKeyFunc)
	(RapiDeviceRegistry* thiz, unsigned int* return_value, RKEY key, unsigned int index, unsigned int name_length, unsigned int zero1, unsigned int zero2, WStr** name);
typedef AsmRet (*RapiDeviceRegistrySetValueFunc)
	(RapiDeviceRegistry* thiz, unsigned int* return_value, RKEY key, WStr* value_name, unsigned int type, unsigned int data_length, void* data);

typedef void (*RapiDeviceRegistryDestroyFunc)(RapiDeviceRegistry* thiz);

struct _RapiDeviceRegistry
{
	RapiDeviceRegistryCreateKeyFunc create_key;
	RapiDeviceRegistryOpenKeyFunc open_key;
	RapiDeviceRegistryQueryValueFunc query_value;
	RapiDeviceRegistryCloseKeyFunc close_key;
	RapiDeviceRegistryDeleteKeyFunc delete_key;
	RapiDeviceRegistryDeleteValueFunc delete_value;
	RapiDeviceRegistryEnumKeyFunc enum_key;
	RapiDeviceRegistrySetValueFunc set_value;
	RapiDeviceRegistryDestroyFunc destroy;
	char priv[0];
};

static inline AsmRet rapi_device_registry_create_key
	(RapiDeviceRegistry* thiz, unsigned int* return_value, RKEY key, WStr* sub_key, WStr* class_name, RKEY* result, unsigned int* disposition)
{
	asm_return_val_if_fail(thiz != NULL && thiz->create_key != NULL, ASM_RET_FAIL);

	return thiz->create_key(thiz, return_value,  key,  sub_key,  class_name, result,  disposition);
}

static inline AsmRet rapi_device_registry_open_key
	(RapiDeviceRegistry* thiz, unsigned int* return_value, RKEY key, WStr* sub_key, RKEY* result)
{
	asm_return_val_if_fail(thiz != NULL && thiz->open_key != NULL, ASM_RET_FAIL);

	return thiz->open_key(thiz, return_value,  key,  sub_key, result);
}

static inline AsmRet rapi_device_registry_query_value
	(RapiDeviceRegistry* thiz, unsigned int* return_value, RKEY key, WStr* value_name, unsigned int data_length, unsigned int* type, unsigned int* ret_data_length, void** ret_data)
{
	asm_return_val_if_fail(thiz != NULL && thiz->query_value != NULL, ASM_RET_FAIL);

	return thiz->query_value(thiz, return_value,  key,  value_name,  data_length, type,  ret_data_length,  ret_data);
}

static inline AsmRet rapi_device_registry_close_key
	(RapiDeviceRegistry* thiz, unsigned int* return_value, RKEY key )
{
	asm_return_val_if_fail(thiz != NULL && thiz->close_key != NULL, ASM_RET_FAIL);

	return thiz->close_key(thiz, return_value,  key);
}

static inline AsmRet rapi_device_registry_delete_key
	(RapiDeviceRegistry* thiz, unsigned int* return_value, RKEY key, WStr* sub_key )
{
	asm_return_val_if_fail(thiz != NULL && thiz->delete_key != NULL, ASM_RET_FAIL);

	return thiz->delete_key(thiz, return_value,  key,  sub_key);
}

static inline AsmRet rapi_device_registry_delete_value
	(RapiDeviceRegistry* thiz, unsigned int* return_value, RKEY key, WStr* value_name )
{
	asm_return_val_if_fail(thiz != NULL && thiz->delete_value != NULL, ASM_RET_FAIL);

	return thiz->delete_value(thiz, return_value,  key,  value_name);
}

static inline AsmRet rapi_device_registry_enum_key
	(RapiDeviceRegistry* thiz, unsigned int* return_value, RKEY key, unsigned int index, unsigned int name_length, unsigned int zero1, unsigned int zero2, WStr** name)
{
	asm_return_val_if_fail(thiz != NULL && thiz->enum_key != NULL, ASM_RET_FAIL);

	return thiz->enum_key(thiz, return_value,  key,  index,  name_length,  zero1,  zero2, name);
}

static inline AsmRet rapi_device_registry_set_value
	(RapiDeviceRegistry* thiz, unsigned int* return_value, RKEY key, WStr* value_name, unsigned int type, unsigned int data_length, void* data)
{
	asm_return_val_if_fail(thiz != NULL && thiz->set_value != NULL, ASM_RET_FAIL);

	return thiz->set_value(thiz, return_value,  key,  value_name,  type,  data_length,  data);
}

static inline void rapi_device_registry_destroy(RapiDeviceRegistry* thiz)
{
	asm_return_if_fail(thiz != NULL && thiz->destroy != NULL);
	thiz->destroy(thiz);

	return;
}
#endif/*RAPI_DEVICE_REGISTRY_H*/

