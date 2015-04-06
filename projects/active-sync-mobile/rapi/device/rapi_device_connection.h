/*
 * File:    rapi_device_connection.h
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
#include <rapi_device.h>

#ifndef RAPI_DEVICE_CONNECTION_H
#define RAPI_DEVICE_CONNECTION_H

struct _RapiDeviceConnection;
typedef struct _RapiDeviceConnection RapiDeviceConnection;

typedef int     (*RapiDeviceConnectionGetSocketFunc)(RapiDeviceConnection* thiz);
typedef AsmRet (*RapiDeviceConnectionProcessEventFunc)(RapiDeviceConnection* thiz);
typedef AsmRet (*RapiDeviceConnectionDestroyFunc)(RapiDeviceConnection* thiz);

struct _RapiDeviceConnection
{
	RapiDeviceConnectionGetSocketFunc     get_socket;
	RapiDeviceConnectionProcessEventFunc  process_event;

	RapiDeviceConnectionDestroyFunc       destroy;

	char priv[0];
};

static inline int rapi_device_connection_get_socket(RapiDeviceConnection* thiz)
{
	assert(thiz != NULL && thiz->get_socket != NULL);

	if(thiz != NULL && thiz->get_socket != NULL)
	{
		return thiz->get_socket(thiz);
	}
	else
	{
		return -1;
	}
}

static inline AsmRet rapi_device_connection_process_event(RapiDeviceConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;

	assert(thiz != NULL && thiz->process_event != NULL);
	if(thiz != NULL && thiz->process_event != NULL)
	{
		ret = thiz->process_event(thiz);
	}

	return ret;
}

static inline AsmRet rapi_device_connection_destroy(RapiDeviceConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;

	assert(thiz != NULL && thiz->destroy != NULL);
	if(thiz != NULL && thiz->destroy != NULL)
	{
		ret = thiz->destroy(thiz);
	}

	return ret;
}

#endif/*RAPI_DEVICE_CONNECTION_H*/

