/*
 * File:    rapi_host_connection_session.h
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
#include <asm-stream.h>
#include <asm-connection.h>

#ifndef _RAPI_HOST_CONNECTION_SESSION_H
#define _RAPI_HOST_CONNECTION_SESSION_H

AsmConnection* rapi_host_connection_session_create(AsmStream* stream, unsigned int req_id);
AsmStream*     rapi_host_connection_session_get_stream(AsmConnection* thiz);

#endif/*_RAPI_HOST_CONNECTION_SESSION_H*/
