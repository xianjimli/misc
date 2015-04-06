/*
 * File:    rrac_structs.h
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

#include <asm-types.h>

#ifndef RRAC_STRUCTS_H
#define RRAC_STRUCTS_H

#define COMMAND_HEADER \
	unsigned short command; \
	unsigned short length

typedef struct _RracCommandHeader
{
	COMMAND_HEADER;

	char data[0];
}RracCommandHeader;

typedef struct _RracCommand6F
{
	COMMAND_HEADER;

	unsigned int subcommand;
}RracCommand6F;

typedef struct _RracCommandStartEvent
{
	COMMAND_HEADER;
	unsigned int size2;
	unsigned int unknown1;
	unsigned int subcommand;
	unsigned int unknown2[4];
	unsigned int count;
	unsigned int data[0];
}RracCommandStartEvent;

typedef struct _RracCommandGetObjects
{
	COMMAND_HEADER;
	unsigned int unknown;
	unsigned int type;
	unsigned int count;
	unsigned int data[0];
}RracCommandGetObjects;

typedef struct _RracCommandDelObject
{
	COMMAND_HEADER;
	unsigned int unknown;
	unsigned int type;
	unsigned int id;
	unsigned int flags;
}RracCommandDelObject;
/**********************************************/

typedef struct _RracRawObjectType
{   
    unsigned int offset;
    WStr         name1[100];
    WStr         name2[80];
    unsigned int id;
    unsigned int count;
    unsigned int total_size;
    FileTime     file_time;
} RracRawObjectType;

typedef struct _RracRawObjectTypes
{
	unsigned int nr;
	RracRawObjectType types[0];
}RracRawObjectTypes;

typedef struct _RracCommandGeneralResp
{
	COMMAND_HEADER;
	unsigned int reply_to;
}RracCommandGeneralResp;

typedef struct _RracRetrieveTypesResp
{
	COMMAND_HEADER;

	unsigned int reply_to;
	unsigned int unknown[7];

	RracRawObjectTypes types;
}RracRetrieveTypesResp;

typedef struct _RracCommandStartEventResp
{
	COMMAND_HEADER;
	unsigned int reply_to;
	unsigned int unknown[3];
}RracCommandStartEventResp;

typedef struct _RracNegotiation
{
	COMMAND_HEADER;

	unsigned int type_id;
	unsigned int old_id;
	unsigned int new_id;
	unsigned int flags;
}RracNegotiation;

typedef struct _RracNotify
{
	COMMAND_HEADER;
	unsigned int  notify_code;
	unsigned int  type;
	unsigned int  changed;
	unsigned int  total;
	unsigned int  data[0];
}RracNotify;

typedef struct _RracNotifyPartners
{
	COMMAND_HEADER;
    unsigned int notify_code;
    unsigned int unknown[3];
    unsigned int partner_index;
    unsigned int partner_ids[2];
}RracNotifyPartners;

typedef struct _RracChunkHeader
{
	unsigned short length;
	unsigned short stuff;
	char data[0];
}RracChunkHeader;

typedef struct _RracObjectHeader
{
	unsigned int id;
	unsigned int type;
	unsigned int flags;
	RracChunkHeader data[0];
}RracObjectHeader;

typedef struct _RracObject
{
	unsigned int id;
	unsigned int type;
	unsigned int flags;
	unsigned int length;
	char data[0];
}RracObject;

typedef struct _RracCommandOpsObjectResp
{
	COMMAND_HEADER;

	unsigned int type;
	unsigned int req_id;
	unsigned int resp_id;
	unsigned int flags;
	
}RracCommandOpsObjectResp;

typedef struct _RracCommandOpsObjectResp RracCommandPutObjectResp;
typedef struct _RracCommandOpsObjectResp RracCommandDelObjectResp;

#endif/*RRAC_STRUCTS_H*/

