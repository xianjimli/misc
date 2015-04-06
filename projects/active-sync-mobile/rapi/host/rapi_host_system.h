/*
 * File:    rapi_host_system.h
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
#ifndef RAPI_HOST_SYSTEM_H
#define RAPI_HOST_SYSTEM_H

struct _RapiHostSystem;
typedef struct _RapiHostSystem RapiHostSystem;

RapiHostSystem* rapi_host_system_create(AsmStream* stream);
AsmRet rapi_host_system_get_store_info(RapiHostSystem* thiz, unsigned int* last_error, unsigned int* return_value,
	 RapiStoreInfo** store_info);
AsmRet rapi_host_system_get_system_info(RapiHostSystem* thiz, unsigned int* last_error, unsigned int* return_value,
	RapiSystemInfo* system_info, RapiSystemInfo** system_info_ret);
AsmRet rapi_host_system_get_power_status(RapiHostSystem* thiz, unsigned int* last_error, unsigned int* return_value,
	unsigned int refresh, RapiSystemPowerStatus** power_status);
AsmRet rapi_host_system_get_version_info(RapiHostSystem* thiz, unsigned int* last_error, unsigned int* return_value,
	 RapiVersionInfo** version_info);
AsmRet rapi_host_system_start_replication(RapiHostSystem* thiz, unsigned int* last_error, unsigned int* return_value );
AsmRet rapi_host_system_start_sync(RapiHostSystem* thiz, unsigned int* last_error, unsigned int* return_value,
	WStr* params );
AsmRet rapi_host_system_resume_sync(RapiHostSystem* thiz, unsigned int* last_error, unsigned int* return_value );
AsmRet rapi_host_system_pause_sync(RapiHostSystem* thiz, unsigned int* last_error, unsigned int* return_value );
void rapi_host_system_destroy(RapiHostSystem* thiz);

#endif/*RAPI_HOST_SYSTEM_H*/

