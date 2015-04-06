/*
 * File:    rapi_host_procman.h
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
#ifndef RAPI_HOST_PROCMAN_H
#define RAPI_HOST_PROCMAN_H

struct _RapiHostProcman;
typedef struct _RapiHostProcman RapiHostProcman;

RapiHostProcman* rapi_host_procman_create(AsmStream* stream);
AsmRet rapi_host_procman_create_process(RapiHostProcman* thiz, unsigned int* last_error, unsigned int* return_value,
	WStr* app_name, WStr* cmd_line, unsigned int zero1, unsigned int zero2, unsigned int zero3, unsigned int flags,unsigned int zero4, unsigned int zero5, unsigned int zero6, RapiProcessInfo** process_info);
AsmRet rapi_host_procman_config_process(RapiHostProcman* thiz, unsigned int* last_error, unsigned int* return_value,
	WStr* config, unsigned int flags, unsigned int* ret_data_length, void** ret_data);
void rapi_host_procman_destroy(RapiHostProcman* thiz);

#endif/*RAPI_HOST_PROCMAN_H*/

