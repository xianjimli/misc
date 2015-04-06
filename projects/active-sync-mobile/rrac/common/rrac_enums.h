/*
 * File:    rrac_enums.h
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

#ifndef _RRAC_ENUMS_H
#define _RRAC_ENUMS_H
typedef enum _RracCommand
{
	RRAC_COMMAND_6F=0x6f,
	RRAC_COMMAND_70=0x70,
	RRAC_COMMAND_70_RESP=0x6c,
	RRAC_COMMAND_6F_RESP=0x6c,
	RRAC_COMMAND_ERROR=0x6e,
	RRAC_COMMAND_NOTIFY=0x69,
	RRAC_COMMAND_NEGOTIATION=0x65,
	RRAC_COMMAND_GET_OBJECTS = 0x67,
	RRAC_COMMAND_DEL_OBJECT = 0x66,
	RRAC_COMMAND_PUT_OBJECT_RESP=0x65,
	RRAC_COMMAND_DEL_OBJECT_RESP=0x65
}RracCommand;

typedef enum _Rrac6FSubCommand
{
	RRAC_SUB_CMD_RETRIEVE_TYPES=0x7c1,
	RRAC_SUB_CMD_START_EVENT=3
}Rrac6FSubCommand;

typedef enum _RracNotifyCode
{
	RRAC_NOTIFY_UPDATE   = 0x00000000,
	RRAC_NOTIFY_PARTNERS = 0x02000000,
	RRAC_NOTIFY_IDS_4    = 0x04000000,
	RRAC_NOTIFY_IDS_6    = 0x06000000,
	RRAC_NOTIFY_INVALID  = 0xffffffff

}RracNotifyCode;

typedef enum _RracMisc
{
	RRAC_END_OF_OBJECT = 0xffff
}RracMisc;

#endif/*_RRAC_ENUMS_H*/

