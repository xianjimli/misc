/*
 * File:    rrac_host_connection_listen.h
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
#include <asm-connection.h>

#ifndef _RRAC_HOST_CONNECTION_LISTEN_H
#define _RRAC_HOST_CONNECTION_LISTEN_H

typedef AsmRet (*RapiStartReplicationFunc)(void* ctx);

AsmConnection* rrac_host_connection_listen_create(RapiStartReplicationFunc start_replication, void* ctx);
AsmRet         rrac_host_connection_request_sync(AsmConnection* thiz, AsmConnection** cmd, AsmConnection** data);

#endif/*_RRAC_HOST_CONNECTION_LISTEN_H*/

