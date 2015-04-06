/*
 * File:    rapi_device_connection_session.h
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
#include <rapi_device.h>
#include <asm-connection.h>

#ifndef _RAPI_DEVICE_CONNECTION_SESSION_H
#define _RAPI_DEVICE_CONNECTION_SESSION_H

typedef AsmRet (*RapiDeviceCommandHookFunc)(void* ctx, AsmConnection* session, unsigned int cmd, int before, AsmRet result);

AsmConnection* rapi_device_connection_session_create(RapiDevice* device, AsmStream* stream, unsigned int req_id);
AsmRet         rapi_device_connection_hook_command(AsmConnection* thiz, RapiDeviceCommandHookFunc on_command, void* ctx);

#endif/*_RAPI_DEVICE_CONNECTION_SESSION_H*/
