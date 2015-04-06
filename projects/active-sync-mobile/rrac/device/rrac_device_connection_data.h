/*
 * File:    rrac_device_connection_data.h
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

#include <rrac_device.h>
#include <asm-connection.h>

#ifndef RRAC_DEVICE_CONNECTION_DATA_H
#define RRAC_DEVICE_CONNECTION_DATA_H

AsmConnection* rrac_device_connection_data_create(const char* host, int port, RracDevice* device);
AsmRet rrac_device_connection_data_set_cmd_connection(AsmConnection* thiz, AsmConnection* cmd_connection);
AsmRet rrac_device_connection_data_send_object(AsmConnection* thiz, const RracObject* object);

#endif/*RRAC_DEVICE_CONNECTION_DATA_H*/
