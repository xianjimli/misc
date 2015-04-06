/*
 * File:    rapi_device_procman.h
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
#ifndef RAPI_DEVICE_PROCMAN_H
#define RAPI_DEVICE_PROCMAN_H

struct _RapiDeviceProcman;
typedef struct _RapiDeviceProcman RapiDeviceProcman;

typedef AsmRet (*RapiDeviceProcmanCreateProcessFunc)
	(RapiDeviceProcman* thiz, unsigned int* return_value, WStr* app_name, WStr* cmd_line, unsigned int zero1, unsigned int zero2, unsigned int zero3, unsigned int flags,unsigned int zero4, unsigned int zero5, unsigned int zero6, RapiProcessInfo** process_info);
typedef AsmRet (*RapiDeviceProcmanConfigProcessFunc)
	(RapiDeviceProcman* thiz, unsigned int* return_value, WStr* config, unsigned int flags, unsigned int* ret_data_length, void** ret_data);

typedef void (*RapiDeviceProcmanDestroyFunc)(RapiDeviceProcman* thiz);

struct _RapiDeviceProcman
{
	RapiDeviceProcmanCreateProcessFunc create_process;
	RapiDeviceProcmanConfigProcessFunc config_process;
	RapiDeviceProcmanDestroyFunc destroy;
	char priv[0];
};

static inline AsmRet rapi_device_procman_create_process
	(RapiDeviceProcman* thiz, unsigned int* return_value, WStr* app_name, WStr* cmd_line, unsigned int zero1, unsigned int zero2, unsigned int zero3, unsigned int flags,unsigned int zero4, unsigned int zero5, unsigned int zero6, RapiProcessInfo** process_info)
{
	asm_return_val_if_fail(thiz != NULL && thiz->create_process != NULL, ASM_RET_FAIL);

	return thiz->create_process(thiz, return_value,  app_name,  cmd_line,  zero1,  zero2,  zero3,  flags, zero4,  zero5,  zero6, process_info);
}

static inline AsmRet rapi_device_procman_config_process
	(RapiDeviceProcman* thiz, unsigned int* return_value, WStr* config, unsigned int flags, unsigned int* ret_data_length, void** ret_data)
{
	asm_return_val_if_fail(thiz != NULL && thiz->config_process != NULL, ASM_RET_FAIL);

	return thiz->config_process(thiz, return_value,  config,  flags, ret_data_length,  ret_data);
}

static inline void rapi_device_procman_destroy(RapiDeviceProcman* thiz)
{
	asm_return_if_fail(thiz != NULL && thiz->destroy != NULL);
	thiz->destroy(thiz);

	return;
}
#endif/*RAPI_DEVICE_PROCMAN_H*/

