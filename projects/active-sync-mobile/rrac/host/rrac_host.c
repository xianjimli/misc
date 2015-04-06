/*
 * File:    rrac_host.c
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
#include <rrac_host_connection_listen.h>
#define RRAC_CMD_TIMEOUT 3
#define RRAC_DATA_TIMEOUT 5

struct _RracHost
{
	AsmConnection* cmd;
	AsmConnection* data;
};

RracHost* rrac_host_create(AsmConnection* listen_connection)
{
	AsmConnection* cmd = NULL;
	AsmConnection* data = NULL;
	asm_return_val_if_fail(listen_connection != NULL, NULL);

	rrac_host_connection_request_sync(listen_connection, &cmd, &data);
	asm_return_val_if_fail(cmd != NULL && data != NULL, NULL);

	RracHost* thiz = ASM_ALLOC(RracHost, 0);
	thiz->cmd = cmd;
	thiz->data = data;

	return thiz;
}

AsmRet    rrac_host_start_event(RracHost* thiz, unsigned int ignored_ids_nr, 
	unsigned int* ignored_ids, RracHostOnEventFunc on_event, void* ctx)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL && on_event != NULL, ret);

	RracCommandStartEvent* cmd = (RracCommandStartEvent*)ASM_ALLOC(RracCommandStartEvent, sizeof(int)*ignored_ids_nr);
	cmd->command = RRAC_COMMAND_70;
	cmd->subcommand = RRAC_SUB_CMD_START_EVENT;
	cmd->count = ignored_ids_nr;
	cmd->length = sizeof(RracCommandStartEvent), sizeof(int)*ignored_ids_nr - sizeof(RracCommandHeader);
	cmd->size2 = cmd->length - sizeof(int);
	cmd->unknown1 = 0xf0000001;
	cmd->unknown2[0] = 2;

	if(ignored_ids_nr > 0 && ignored_ids != NULL)
	{
		memcpy(cmd->data, ignored_ids, sizeof(int)*ignored_ids_nr);
	}

	RracCommandHeader* resp = NULL;
	RracCommandStartEventResp* event_resp = NULL;
	do
	{
		asm_break_if_fail(rrac_host_connection_cmd_send_command(thiz->cmd, (RracCommandHeader*)cmd) == ASM_RET_OK);
		asm_break_if_fail(rrac_host_connection_cmd_read_resp(thiz->cmd, RRAC_CMD_TIMEOUT, &event_resp) == ASM_RET_OK);
		asm_break_if_fail(event_resp->command == RRAC_COMMAND_70_RESP);
		asm_break_if_fail(event_resp->reply_to == RRAC_COMMAND_70);
		
		ASM_FREE(event_resp);
		while(rrac_host_connection_cmd_read_resp(thiz->cmd, RRAC_CMD_TIMEOUT, &resp) == ASM_RET_OK)
		{
			on_event(ctx, resp);
			ASM_FREE(resp);
		}

		ret = ASM_RET_OK;
	}while(0);
	
	ASM_FREE(cmd);

	return ret;
}

AsmRet    rrac_host_get_types(RracHost* thiz, RracRawObjectTypes** types)
{
	AsmRet ret = ASM_RET_FAIL;

	asm_return_val_if_fail(thiz != NULL && types != NULL, ret);
	RracCommand6F cmd = {0};
	cmd.command = RRAC_COMMAND_6F;
	cmd.length = sizeof(cmd) - sizeof(RracCommandHeader);
	cmd.subcommand = RRAC_SUB_CMD_RETRIEVE_TYPES;

	RracRetrieveTypesResp* resp = NULL;
	do
	{
		asm_break_if_fail(rrac_host_connection_cmd_send_command(thiz->cmd, (RracCommandHeader*)&cmd) == ASM_RET_OK);
		asm_break_if_fail(rrac_host_connection_cmd_read_resp(thiz->cmd, RRAC_CMD_TIMEOUT, &resp) == ASM_RET_OK);
		asm_break_if_fail(resp->reply_to == RRAC_COMMAND_6F);
		asm_break_if_fail(resp->command == RRAC_COMMAND_6F_RESP);
	
		*types = ASM_ALLOC(RracRawObjectTypes, sizeof(RracRawObjectType)*(resp->types.nr));
		(*types)->nr = resp->types.nr;
		memcpy((*types)->types, resp->types.types, sizeof(RracRawObjectType)*(resp->types.nr));

		ret = ASM_RET_OK;
	}while(0);

	ASM_FREE(resp);

	return ret;
}

AsmRet    rrac_host_get_objects(RracHost* thiz, unsigned int type, unsigned int id_nr, 
	unsigned int* ids, RracHostOnGetObjectFunc on_get_object, void* ctx)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL && on_get_object != NULL && ids != NULL, ret);

	RracCommandGetObjects* cmd = ASM_ALLOC(RracCommandGetObjects, sizeof(id_nr) * sizeof(int));
	cmd->command = RRAC_COMMAND_GET_OBJECTS;
	cmd->length = sizeof(RracCommandGetObjects) + sizeof(id_nr) * sizeof(int) - sizeof(RracCommandHeader);
	cmd->type = type;
	cmd->count = id_nr;
	memcpy(cmd->data, ids, sizeof(int)*id_nr);

	RracObject* object = NULL;
	do
	{
		asm_break_if_fail(rrac_host_connection_cmd_send_command(thiz->cmd, (RracCommandHeader*)cmd) == ASM_RET_OK);
		while(rrac_host_connection_data_get_object(thiz->data, RRAC_DATA_TIMEOUT, &object) == ASM_RET_OK)
		{
			on_get_object(ctx, object);
		}

		ASM_FREE(object);

		ret = ASM_RET_OK;
	}while(0);

	ASM_FREE(cmd);

	return ret;
}

AsmRet    rrac_host_del_object(RracHost* thiz, unsigned int type, unsigned int id, unsigned int flags)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);

	RracCommandDelObject cmd = {0};
	cmd.command = RRAC_COMMAND_DEL_OBJECT;
	cmd.type  = type;
	cmd.id    = id;
	cmd.flags = flags;
	cmd.length = sizeof(RracCommandDelObject) - sizeof(RracCommandHeader);

	RracCommandDelObjectResp* resp = NULL;
	do
	{
		asm_break_if_fail(rrac_host_connection_cmd_send_command(thiz->cmd, (RracCommandHeader*)&cmd) == ASM_RET_OK);
		asm_break_if_fail(rrac_host_connection_cmd_read_resp(thiz->cmd, RRAC_CMD_TIMEOUT, &resp) == ASM_RET_OK);
		asm_break_if_fail(resp->command == RRAC_COMMAND_DEL_OBJECT_RESP);
		asm_break_if_fail(resp->req_id == resp->resp_id);
		asm_break_if_fail(resp->req_id == id);
		asm_break_if_fail(resp->type == type);

		ret = ASM_RET_OK;

	}while(0);

	printf("%s: %d %d %d\n", __func__, id, resp->req_id, resp->resp_id);

	ASM_FREE(resp);

	return ret;
}

AsmRet    rrac_host_put_objects(RracHost* thiz, RracHostOnPutObjectFunc on_put_object, void* ctx)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL && on_put_object != NULL, ASM_RET_FAIL);

	RracObject* object = NULL;

	while(on_put_object(ctx, &object) == ASM_RET_OK)
	{
		ret = rrac_host_connection_data_put_object(thiz->data, object);

		do
		{
			RracCommandPutObjectResp* resp = NULL;
			asm_break_if_fail(ret == ASM_RET_OK);

			asm_break_if_fail(rrac_host_connection_cmd_read_resp(thiz->cmd, RRAC_CMD_TIMEOUT, &resp) == ASM_RET_OK);
			asm_break_if_fail(resp->command == RRAC_COMMAND_DEL_OBJECT_RESP);
			asm_break_if_fail(resp->req_id == resp->resp_id);
			asm_break_if_fail(resp->req_id == object->id);
			asm_break_if_fail(resp->type == object->type);

			ASM_FREE(resp);
		}while(0);
		
		ASM_FREE(object);
		asm_break_if_fail(ret == ASM_RET_OK);
	}

	return ret;
}

AsmRet    rrac_host_get_object(RracHost* thiz, unsigned int type, unsigned int id, RracObject** object)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL && object != NULL, ASM_RET_FAIL);

	return ret;
}

void      rrac_host_destroy(RracHost* thiz)
{
	if(thiz != NULL)
	{
		asm_connection_destroy(thiz->cmd);
		asm_connection_destroy(thiz->data);

		ASM_FREE(thiz);
	}

	return;
}

