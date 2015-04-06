/*
 * File:    rapi_enums.h
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

#ifndef _RAPI_ENUMS_H
#define _RAPI_ENUMS_H

typedef enum _RapiCommand
{
	RAPI_COMMAND_HAND_SHAKE = 0x00,
	RAPI_COMMAND_START_REPLICATION=0x02,
	RAPI_COMMAND_GET_VERSION = 0x43
}RapiCommand;

typedef enum _RapiResponse
{
	RAPI_RESP_HAND_SHAKE = 0x03,
	RAPI_RESP_GET_INFO = 0x04
}RapiResponse;

typedef enum _RapiReturnValue
{
	RAPI_SUCCESS = 0,
	RAPI_FILE_NOT_FOUND=2,
	RAPI_NOT_ENOUGH_MEMORY=8,
	RAPI_SEEK=25,
	RAPI_INVALID_PARAMETER=87,
	RAPI_INSUFFICIENT_BUFFER=122,
	RAPI_NO_DATA=232,
	RAPI_NO_MORE_ITEMS=259,
	RAPI_KEY_DELETED=1018
}RapiReturnValue;

typedef enum _RapiCsidl
{
	RAPI_CSIDL_PROGRAMS           = 0x0002,
	RAPI_CSIDL_PERSONAL           = 0x0005,
	RAPI_CSIDL_FAVORITES_GRYPHON  = 0x0006,
	RAPI_CSIDL_STARTUP            = 0x0007,
	RAPI_CSIDL_RECENT             = 0x0008,
	RAPI_CSIDL_STARTMENU          = 0x000b,
	RAPI_CSIDL_DESKTOPDIRECTORY   = 0x0010,
	RAPI_CSIDL_FONTS              = 0x0014,
	RAPI_CSIDL_FAVORITES          = 0x0016
}RapiCsidl;

typedef enum _RapiShareMode
{
	RAPI_SHARE_MODE_GENERIC_WRITE = 0x40000000,
	RAPI_SHARE_MODE_GENERIC_READ = 0x80000000,
	RAPI_SHARE_MODE_FILE_SHARE_READ = 0x00000001,
}RapiShareMode;

typedef enum _RapiCreationDisposition
{
	RAPI_CREATION_DISPOSITION_CREATE_NEW = 1,
	RAPI_CREATION_DISPOSITION_CREATE_ALWAYS = 2,
	RAPI_CREATION_DISPOSITION_OPEN_EXISTING = 3,
	RAPI_CREATION_DISPOSITION_OPEN_ALWAYS = 4,
	RAPI_CREATION_DISPOSITION_TRUNCATE_EXISTING = 5,
	RAPI_CREATION_DISPOSITION_OPEN_FOR_LOADER = 6,
}RapiCreationDisposition;

typedef enum _RapiDesiredAccess
{
	RAPI_ACCESS_EXECUTE = 0x00000001,
	RAPI_ACCESS_READ = 0x00000002,
	RAPI_ACCESS_WRITE = 0x00000004,

}RapiDesiredAccess;

typedef enum _RapiFileAttribute
{
	RAPI_FILE_ATTRIBUTE_READONLY = 0x00000001,
	RAPI_FILE_ATTRIBUTE_HIDDEN = 0x00000002,
	RAPI_FILE_ATTRIBUTE_SYSTEM = 0x00000004,
	RAPI_FILE_ATTRIBUTE_1 = 0x00000008,
	RAPI_FILE_ATTRIBUTE_DIRECTORY = 0x00000010,
	RAPI_FILE_ATTRIBUTE_ARCHIVE = 0x00000020,
	RAPI_FILE_ATTRIBUTE_INROM = 0x00000040,
	RAPI_FILE_ATTRIBUTE_NORMAL = 0x00000080,
	RAPI_FILE_ATTRIBUTE_TEMPORARY = 0x00000100,
	RAPI_FILE_ATTRIBUTE_2 = 0x00000200,
	RAPI_FILE_ATTRIBUTE_3 = 0x00000400,
	RAPI_FILE_ATTRIBUTE_COMPRESSED = 0x00000800,
	RAPI_FILE_ATTRIBUTE_ROMSTATICREF = 0x00001000,
	RAPI_FILE_ATTRIBUTE_ROMMODULE = 0x00002000,
	RAPI_FILE_ATTRIBUTE_4 = 0x00004000,
	RAPI_FILE_ATTRIBUTE_5 = 0x00008000,
	RAPI_FILE_ATTRIBUTE_HAS_CHILDREN = 0x00010000,
	RAPI_FILE_ATTRIBUTE_SHORTCUT = 0x00020000,
	RAPI_FILE_ATTRIBUTE_6 = 0x00040000,
	RAPI_FILE_ATTRIBUTE_7 = 0x00080000,
}RapiFileAttribute;

typedef enum _RapiFileSeekType
{
	RAPI_FILE_SEEK_TYPE_BEGIN = 0,
	RAPI_FILE_SEEK_TYPE_CURRENT = 1,
	RAPI_FILE_SEEK_TYPE_END = 2,
}RapiFileSeekType;

typedef enum _RapiRegKey
{
	RAPI_KEY_CLASSES_ROOT          = (0x80000000),
	RAPI_KEY_CURRENT_USER          = (0x80000001),
	RAPI_KEY_LOCAL_MACHINE         = (0x80000002),
	RAPI_KEY_USERS                 = (0x80000003)
}RapiRegKey;

typedef enum _RapiRegType
{
	RAPI_REG_NONE                   = 0,
	RAPI_REG_SZ                     = 1,
	RAPI_REG_EXPAND_SZ              = 2,
	RAPI_REG_BINARY                 = 3,
	RAPI_REG_DWORD                  = 4,
	RAPI_REG_DWORD_LITTLE_ENDIAN    = 4,
	RAPI_REG_DWORD_BIG_ENDIAN       = 5,
	RAPI_REG_LINK                   = 6,
	RAPI_REG_MULTI_SZ               = 7
}RapiRegType;

typedef enum _RapiRegCreateFlags
{
	RAPI_REG_CREATED_NEW_KEY        = 1,
	RAPI_REG_OPENED_EXISTING_KEY    = 2
}RapiRegCreateFlags;

#include <rapi_registry.h>
#include <rapi_procman.h>
#include <rapi_system.h>
#include <rapi_fileman.h>

#endif/*_RAPI_ENUMS_H*/

