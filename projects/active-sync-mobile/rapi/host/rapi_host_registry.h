/*
 * File:    rapi_host_registry.h
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
#ifndef RAPI_HOST_REGISTRY_H
#define RAPI_HOST_REGISTRY_H

struct _RapiHostRegistry;
typedef struct _RapiHostRegistry RapiHostRegistry;

RapiHostRegistry* rapi_host_registry_create(AsmStream* stream);
AsmRet rapi_host_registry_create_key(RapiHostRegistry* thiz, unsigned int* last_error, unsigned int* return_value,
	RKEY key, WStr* sub_key, WStr* class_name, RKEY* result, unsigned int* disposition);
AsmRet rapi_host_registry_open_key(RapiHostRegistry* thiz, unsigned int* last_error, unsigned int* return_value,
	RKEY key, WStr* sub_key, RKEY* result);
AsmRet rapi_host_registry_query_value(RapiHostRegistry* thiz, unsigned int* last_error, unsigned int* return_value,
	RKEY key, WStr* value_name, unsigned int data_length, unsigned int* type, unsigned int* ret_data_length, void** ret_data);
AsmRet rapi_host_registry_close_key(RapiHostRegistry* thiz, unsigned int* last_error, unsigned int* return_value,
	RKEY key );
AsmRet rapi_host_registry_delete_key(RapiHostRegistry* thiz, unsigned int* last_error, unsigned int* return_value,
	RKEY key, WStr* sub_key );
AsmRet rapi_host_registry_delete_value(RapiHostRegistry* thiz, unsigned int* last_error, unsigned int* return_value,
	RKEY key, WStr* value_name );
AsmRet rapi_host_registry_enum_key(RapiHostRegistry* thiz, unsigned int* last_error, unsigned int* return_value,
	RKEY key, unsigned int index, unsigned int name_length, unsigned int zero1, unsigned int zero2, WStr** name);
AsmRet rapi_host_registry_set_value(RapiHostRegistry* thiz, unsigned int* last_error, unsigned int* return_value,
	RKEY key, WStr* value_name, unsigned int type, unsigned int data_length, void* data);
void rapi_host_registry_destroy(RapiHostRegistry* thiz);

#endif/*RAPI_HOST_REGISTRY_H*/

