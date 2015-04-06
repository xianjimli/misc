/*
 * File:    rrac_host.h
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

#include <asm-connection.h>
#include <rrac_host_lib.h>

#ifndef _RRAC_HOST_H
#define _RRAC_HOST_H

struct _RracHost;
typedef struct _RracHost RracHost;

typedef AsmRet (*RracHostOnEventFunc)(void* ctx, RracCommandHeader* event);
typedef AsmRet (*RracHostOnGetObjectFunc)(void* ctx, RracObject* object);
typedef AsmRet (*RracHostOnPutObjectFunc)(void* ctx, RracObject** object);

RracHost* rrac_host_create(AsmConnection* listen_connection);

AsmRet    rrac_host_get_types(RracHost* thiz, RracRawObjectTypes** types);

AsmRet    rrac_host_start_event(RracHost* thiz, unsigned int ignored_ids_nr, 
	unsigned int* ignored_ids, RracHostOnEventFunc on_event, void* ctx);
AsmRet    rrac_host_get_objects(RracHost* thiz, unsigned int type, unsigned int id_nr, 
	unsigned int* ids, RracHostOnGetObjectFunc on_get_object, void* ctx);
AsmRet    rrac_host_put_objects(RracHost* thiz, RracHostOnPutObjectFunc on_put_object, void* ctx);
AsmRet    rrac_host_del_object(RracHost* thiz, unsigned int type, unsigned int id, unsigned int flags);

void      rrac_host_destroy(RracHost* thiz);

#endif/*_RRAC_HOST_H*/

