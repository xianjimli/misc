/*
 * File:    rapi_device_registry_write.h
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

#include <asm-output-buffer.h>
#include <rapi_device_lib.h>

#ifndef RAPI_DEVICE_REGISTRY_WRITE_H
#define RAPI_DEVICE_REGISTRY_WRITE_H

AsmRet rapi_device_write_registry_create_key(
	AsmOutputBuffer* output, unsigned int last_error, unsigned int return_value,
	RKEY result, unsigned int disposition);
AsmRet rapi_device_write_registry_open_key(
	AsmOutputBuffer* output, unsigned int last_error, unsigned int return_value,
	RKEY result);
AsmRet rapi_device_write_registry_query_value(
	AsmOutputBuffer* output, unsigned int last_error, unsigned int return_value,
	unsigned int type, unsigned int ret_data_length, void* ret_data);
AsmRet rapi_device_write_registry_close_key(
	AsmOutputBuffer* output, unsigned int last_error, unsigned int return_value);
AsmRet rapi_device_write_registry_delete_key(
	AsmOutputBuffer* output, unsigned int last_error, unsigned int return_value);
AsmRet rapi_device_write_registry_delete_value(
	AsmOutputBuffer* output, unsigned int last_error, unsigned int return_value);
AsmRet rapi_device_write_registry_enum_key(
	AsmOutputBuffer* output, unsigned int last_error, unsigned int return_value,
	WStr* name);
AsmRet rapi_device_write_registry_set_value(
	AsmOutputBuffer* output, unsigned int last_error, unsigned int return_value);

#endif/*RAPI_DEVICE_REGISTRY_WRITE_H*/

