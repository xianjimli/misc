/*
 * File:    rapi_fileman.h
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

#ifndef RAPI_FILEMAN_H
#define RAPI_FILEMAN_H

typedef enum _RapiFilemanCommand
{
	RAPI_COMMAND_FILEMAN_CREATE_FILE=0x16,
	RAPI_COMMAND_FILEMAN_READ_FILE=0x17,
	RAPI_COMMAND_FILEMAN_WRITE_FILE=0x18,
	RAPI_COMMAND_FILEMAN_SEEK=0x26,
	RAPI_COMMAND_FILEMAN_SEEK_TO_END=0x27,
	RAPI_COMMAND_FILEMAN_GET_FILE_TIME=0x41,
	RAPI_COMMAND_FILEMAN_SET_FILE_TIME=0x42,
	RAPI_COMMAND_FILEMAN_COPY_FILE=0x2c,
	RAPI_COMMAND_FILEMAN_CREATE_DIRECTORY=0x28,
	RAPI_COMMAND_FILEMAN_DELETE_FILE=0x2d,
	RAPI_COMMAND_FILEMAN_REMOVE_DIRECTORY=0x29,
	RAPI_COMMAND_FILEMAN_MOVE_FILE=0x2b,
	RAPI_COMMAND_FILEMAN_GET_SPECIAL_FOLDER=0x4b,
	RAPI_COMMAND_FILEMAN_CLOSE_HANDLE=0x19,
	RAPI_COMMAND_FILEMAN_GET_SIZE=0x2e,
	RAPI_COMMAND_FILEMAN_FIND_ALL_FILES=0x1a,
	RAPI_COMMAND_FILEMAN_FIND_FIRST_FILE=0x11,
	RAPI_COMMAND_FILEMAN_FIND_NEXT_FILE=0x00,
	RAPI_COMMAND_FILEMAN_FIND_CLOSE=0x01,
}RapiFilemanCommand;
#endif/*RAPI_FILEMAN_H*/

