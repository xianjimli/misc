/*
 * File:    rrac_host_test.c
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

#include <string.h>
#include <rrac_host.h>
#include <rrac_test_data.h>

#include <rrac_host_connection_listen.h>

static AsmRet on_event(void* ctx, RracCommandHeader* event)
{
	printf("%s:%d command=%d length=%d\n", __func__, __LINE__, event->command, event->length);

	return ASM_RET_OK;
}


typedef struct _PutGetObjectCtx
{
	unsigned int id;
	unsigned int id_begin;
	unsigned int id_end;
	unsigned int type;
}PutGetObjectCtx;

static AsmRet on_put_object(void* ctx, RracObject** object)
{
	PutGetObjectCtx* info = (PutGetObjectCtx*)ctx;

	if(info->id < info->id_end)
	{
		*object = rrac_test_data_get_object(info->type, info->id, info->id * 100, (unsigned char)info->id);
		info->id++;
		return ASM_RET_OK;
	}
	else
	{
		return ASM_RET_EOF;
	}
}

static AsmRet on_get_object(void* ctx, RracObject* object)
{
	PutGetObjectCtx* info = (PutGetObjectCtx*)ctx;
	RracObject* object_test = rrac_test_data_get_object(info->type, info->id, info->id * 100, (unsigned char)info->id);

	assert(object->id == object_test->id);
	assert(object->type == object_test->type);
	assert(object->length == object_test->length);
	assert(memcmp(object->data, object_test->data, object->length) == 0);

	ASM_FREE(object_test);
	
	return ASM_RET_OK;
}

int main(int argc, char* argv[])
{
	unsigned int ignored_ids[10] = {1,2,3,4,5,6,7,8,9,0};

	PutGetObjectCtx ctx = {100, 101, 200, 10001};

	RracRawObjectTypes* types_from_device = NULL;
	RracRawObjectTypes* types_from_test = rrac_test_data_get_types();

	AsmConnection* listen_connection = rrac_host_connection_listen_create(NULL, NULL);
	RracHost* host = rrac_host_create(listen_connection);

	assert(rrac_host_get_types(host, &types_from_device) == ASM_RET_OK);
	assert(memcmp(types_from_device, types_from_test, sizeof(RracRawObjectType) * RRAC_TYPES_NR) == 0);
	ASM_FREE(types_from_device);
	ASM_FREE(types_from_test);

	assert(rrac_host_start_event(host, sizeof(ignored_ids)/sizeof(int), ignored_ids, on_event, NULL) == ASM_RET_OK);
	
	assert(rrac_host_put_objects(host, on_put_object, &ctx) == ASM_RET_OK);

	for(ctx.id = ctx.id_begin; ctx.id < ctx.id_end; ctx.id++)
	{
		assert(rrac_host_get_objects(host, ctx.type, 1, &ctx.id, on_get_object, &ctx) == ASM_RET_OK);
		assert(rrac_host_del_object(host, ctx.type, ctx.id, 0) == ASM_RET_OK);
	}

	for(ctx.id = ctx.id_begin; ctx.id < ctx.id_end; ctx.id++)
	{
		assert(rrac_host_del_object(host, ctx.type, ctx.id, 0) != ASM_RET_OK);
	}

	rrac_host_destroy(host);
	asm_connection_destroy(listen_connection);

	return 0;
}

