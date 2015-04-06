/*
 * File:    rapi_system.h
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

#ifndef RAPI_SYSTEM_H
#define RAPI_SYSTEM_H

typedef enum _RapiSystemCommand
{
	RAPI_COMMAND_SYSTEM_GET_STORE_INFO=0x39,
	RAPI_COMMAND_SYSTEM_GET_SYSTEM_INFO=0x3d,
	RAPI_COMMAND_SYSTEM_GET_POWER_STATUS=0x49,
	RAPI_COMMAND_SYSTEM_GET_VERSION_INFO=0x43,
	RAPI_COMMAND_SYSTEM_START_REPLICATION=0x02,
	RAPI_COMMAND_SYSTEM_START_SYNC=0x59,
	RAPI_COMMAND_SYSTEM_RESUME_SYNC=0x10,
	RAPI_COMMAND_SYSTEM_PAUSE_SYNC=0x0f,
}RapiSystemCommand;
#endif/*RAPI_SYSTEM_H*/

