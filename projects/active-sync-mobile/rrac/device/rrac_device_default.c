/*
 * File:    rrac_device_default.c
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
#include <rrac_test_data.h>
#include <rrac_device_default.h>

typedef struct _PrivInfo
{
	int dummy;

}PrivInfo;

static AsmRet rrac_device_default_get_types(RracDevice* thiz, RracRawObjectTypes** ret_types)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL && ret_types != NULL, ret);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	*ret_types = rrac_test_data_get_types();
	ret = ASM_RET_OK;

	return ret;
}

static AsmRet rrac_device_default_send_negotiation(RracDevice* thiz, RracDeviceSendEventFunc send_event, void* ctx)
{
	RracNegotiation resp = {0};
	resp.command = RRAC_COMMAND_NEGOTIATION;
	resp.length = sizeof(resp) - sizeof(RracCommandHeader);
	resp.type_id = 1;
	resp.old_id = 0x11223344;
	resp.new_id = 0x11223344;
	resp.flags = 0;

	return send_event(ctx, (RracCommandHeader*)&resp);
}

static AsmRet rrac_device_default_send_notify(RracDevice* thiz, RracDeviceSendEventFunc send_event, void* ctx)
{
	size_t i = 0;
	size_t n = 12;
	AsmRet ret = ASM_RET_FAIL;

	size_t length = sizeof(RracNotify) + sizeof(int) * n;
	RracNotify* resp = (RracNotify*)malloc(length);
	resp->command = RRAC_COMMAND_NOTIFY;
	resp->length = length - sizeof(RracCommandHeader);
	resp->notify_code = RRAC_NOTIFY_UPDATE;
	resp->type      = 1003;
	resp->total     = n * sizeof(int);
	resp->changed   = 5;

	for(i = 0; i < n; i++)
	{
		resp->data[i] = i;
	}

	ret = send_event(ctx, (RracCommandHeader*)resp);

	ASM_FREE(resp);

	return ret;
}

static AsmRet rrac_device_default_send_notify_partners(RracDevice* thiz, 
	RracDeviceSendEventFunc send_event, void* ctx)
{
	RracNotifyPartners resp = {0};
	resp.command = RRAC_COMMAND_NOTIFY;
	resp.length = sizeof(resp) - sizeof(RracCommandHeader);
	resp.notify_code = RRAC_NOTIFY_PARTNERS;
	resp.partner_index = 0;
	resp.partner_ids[0] = 0x11223344;
	resp.partner_ids[1] = 0x55667788;

	return send_event(ctx, (RracCommandHeader*)&resp);
}


static AsmRet rrac_device_default_start_event(RracDevice* thiz, 
					unsigned int* ignored_ids, 
					unsigned int ignored_ids_nr,
					RracDeviceSendEventFunc send_event, void* ctx)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL && ignored_ids != NULL && send_event != NULL, ret);

	ret = rrac_device_default_send_negotiation(thiz, send_event, ctx);
	ret = rrac_device_default_send_notify_partners(thiz, send_event, ctx);

	ret = rrac_device_default_send_notify(thiz, send_event, ctx);

	return ret;
}

static AsmRet rrac_device_default_del_object(RracDevice* thiz, 
					unsigned int type, unsigned int id, unsigned int flags)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	char file_name[100] = {0};
	sprintf(file_name, "object-%d-%d.dat", type, id);
	if(asm_file_length(file_name) >= 0)
	{
		unlink(file_name);
		ret = ASM_RET_OK;
	}
	else
	{
		ret = ASM_RET_FAIL;
	}
	printf("%s:%d %s ret=%d\n", __func__, __LINE__, file_name, ret);

	return ret;
}

static AsmRet rrac_device_default_get_objects(RracDevice* thiz,
					unsigned int type,
					unsigned int* ids,
					unsigned int  ids_nr,
					RracDeviceSendObjectFunc send_object, void* ctx)
{
	size_t i = 0;
	size_t j = 0;
	size_t length = 0;
	
	char file_name[100] = {0};

	char* data = NULL;
	RracObject* object = NULL;
	AsmRet ret = ASM_RET_FAIL;

	asm_return_val_if_fail(thiz != NULL && ids != NULL && send_object != NULL, ASM_RET_FAIL);
	for(i = 0; i < ids_nr; i++)
	{
		sprintf(file_name, "object-%d-%d.dat", type, ids[i]);
		if(asm_read_file(file_name, &data, &length) == ASM_RET_OK)
		{
			object = ASM_ALLOC(RracObject, length);
			object->type = type;
			object->id = ids[i];
			object->length = length;

			memcpy(object->data, data, length);

			if((ret = send_object(ctx, object)) != ASM_RET_OK)
			{
				break;
			}
			ASM_FREE(data);
			ASM_FREE(object);
		}
		else
		{
			break;
		}
	}
	RracObject end_object  = {0};
	end_object.id = RRAC_END_OF_OBJECT;
	ret = send_object(ctx, &end_object);

	return ASM_RET_OK;
}

static AsmRet rrac_device_default_destroy(RracDevice* thiz, void* unused)
{
	if(thiz != NULL)
	{
		ASM_FREE(thiz);
	}

	return ASM_RET_OK;
}

static inline AsmRet rrac_device_default_put_object(RracDevice* thiz, RracObject* object)
{
	char file_name[100] = {0};
	sprintf(file_name, "object-%d-%d.dat", object->type, object->id);
	asm_write_file(file_name, object->data, object->length);

	return ASM_RET_OK;
}

RracDevice* rrac_device_default_create(void)
{
	RracDevice* thiz = ASM_ALLOC(RracDevice, sizeof(PrivInfo));
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	thiz->get_types = rrac_device_default_get_types;
	thiz->start_event = rrac_device_default_start_event;
	thiz->get_objects = rrac_device_default_get_objects;
	thiz->put_object = rrac_device_default_put_object;
	thiz->del_object = rrac_device_default_del_object;
	thiz->destroy = rrac_device_default_destroy;
	
	return thiz;
}

