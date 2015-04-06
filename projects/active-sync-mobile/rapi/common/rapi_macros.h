/*
 * File:    rapi_macros.h
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

#ifndef _RAPI_MACORS_H
#define _RAPI_MACORS_H

#define RAPI_PORT                 990
#define RAPI_MAX_SESSION_NR       12
#define RAPI_MAX_PATH             260
#define RAPI_DEVICE_OS_MAJOR      0x01
#define RAPI_DEVICE_OS_MINOR      0x02
#define RAPI_DEVICE_SYNC_VERSION  0x03
#define RAPI_CPU_TYPE             0x04
#define RAPI_DEVICE_MAGIC         0xaabbccdd
#define RAPI_DEVICE_ID            0xabcdabcd

typedef unsigned int RKEY;

#define RKEY_CLASSES_ROOT           ((RKEY)0x80000000)
#define RKEY_CURRENT_USER           ((RKEY)0x80000001)
#define RKEY_LOCAL_MACHINE          ((RKEY)0x80000002)
#define RKEY_USERS                  ((RKEY)0x80000003)

#endif/*_RAPI_MACORS_H*/

