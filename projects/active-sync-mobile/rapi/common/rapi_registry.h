/*
 * File:    rapi_registry.h
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

#ifndef RAPI_REGISTRY_H
#define RAPI_REGISTRY_H

typedef enum _RapiRegistryCommand
{
	RAPI_COMMAND_REGISTRY_CREATE_KEY=0x31,
	RAPI_COMMAND_REGISTRY_OPEN_KEY=0x2f,
	RAPI_COMMAND_REGISTRY_QUERY_VALUE=0x37,
	RAPI_COMMAND_REGISTRY_CLOSE_KEY=0x32,
	RAPI_COMMAND_REGISTRY_DELETE_KEY=0x33,
	RAPI_COMMAND_REGISTRY_DELETE_VALUE=0x35,
	RAPI_COMMAND_REGISTRY_ENUM_KEY=0x30,
	RAPI_COMMAND_REGISTRY_SET_VALUE=0x38,
}RapiRegistryCommand;
#endif/*RAPI_REGISTRY_H*/

