/*
 * File:    rapi_device_registry_default.c
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
#include <asm-wstr.h>
#include <asm-handle-file.h>
#include <rapi_device_registry_default.h>

#define REG_FILE_FORMAT "registry-%p-%s"

typedef struct _RegRecord
{
	unsigned int type;
	char name[256];
	unsigned int value_length;
	char value[1024];
}RegRecord;

typedef struct _PrivInfo
{
	int dummy;
}PrivInfo;

static AsmRet registry_get_record(FILE* fp, char* str_value_name, RegRecord* record)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(fp != NULL && str_value_name != NULL && record != NULL, ASM_RET_FAIL);

	rewind(fp);
	size_t length = 0;
	while(fread(record, sizeof(RegRecord), 1, fp))
	{
		if(strcmp(record->name, str_value_name) == 0)
		{
			ret = ASM_RET_OK;
			break;
		}
	}

	return ret;
}

static AsmRet registry_add_record(FILE* fp, char* str_value_name, RegRecord* new_record)
{
	AsmRet ret = ASM_RET_FAIL;
	RegRecord record = {0};
	asm_return_val_if_fail(fp != NULL && str_value_name != NULL && new_record != NULL, ASM_RET_FAIL);

	rewind(fp);
	size_t length = 0;
	size_t pos = 0;
	while(fread(&record, sizeof(RegRecord), 1, fp))
	{
		if(record.type == RAPI_REG_NONE)
		{
			fseek(fp, pos, SEEK_SET);
			fwrite(new_record, sizeof(RegRecord), 1, fp);
			fflush(fp);

			return ASM_RET_OK;
		}

		pos = ftell(fp);
	}
	
	fwrite(new_record, sizeof(RegRecord), 1, fp);
	fflush(fp);

	return ASM_RET_OK;
}

static AsmRet registry_del_record(FILE* fp, char* str_value_name)
{
	AsmRet ret = ASM_RET_FAIL;
	RegRecord record = {0};
	asm_return_val_if_fail(fp != NULL && str_value_name != NULL, ASM_RET_FAIL);

	rewind(fp);
	size_t length = 0;
	size_t pos = 0;
	while(fread(&record, sizeof(RegRecord), 1, fp))
	{
		if(strcmp(record.name, str_value_name) == 0)
		{
			fseek(fp, pos, SEEK_SET);
			memset(&record, 0x00, sizeof(RegRecord));
			fwrite(&record, sizeof(RegRecord), 1, fp);
			fflush(fp);
			
			ret = ASM_RET_OK;
			break;
		}

		pos = ftell(fp);
	}
	
	return ret;
}

static AsmRet rapi_device_registry_default_create_key
	(RapiDeviceRegistry* thiz, unsigned int* return_value, RKEY key, WStr* sub_key, WStr* class_name, RKEY* result, unsigned int* disposition)
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	char* str_sub_key = wstr_to_ascii(sub_key);
	char file_name[RAPI_MAX_PATH + 1] = {0};
	FILE* fp = NULL;
	snprintf(file_name, RAPI_MAX_PATH, REG_FILE_FORMAT, key, str_sub_key);
	if(asm_file_length(file_name) < 0)
	{
		fp = fopen(file_name, "wb+");
		*disposition = RAPI_CREATION_DISPOSITION_CREATE_NEW;
	}
	else
	{
		fp = fopen(file_name, "rb+");
		*disposition = RAPI_CREATION_DISPOSITION_OPEN_EXISTING;
	}

	*result = (RKEY)asm_handle_file_create(fp, file_name);
	printf("%s:%d %s ret=%d ret_key=%p\n", __func__, __LINE__, str_sub_key, *return_value, *result);
	ASM_FREE(str_sub_key);

	return ASM_RET_OK;
}

static AsmRet rapi_device_registry_default_open_key
	(RapiDeviceRegistry* thiz, unsigned int* return_value, RKEY key, WStr* sub_key, RKEY* result)
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	
	char* str_sub_key = wstr_to_ascii(sub_key);
	char file_name[RAPI_MAX_PATH + 1] = {0};
	snprintf(file_name, RAPI_MAX_PATH, REG_FILE_FORMAT, key, str_sub_key);
	FILE* fp = fopen(file_name, "rb+");

	*result = (RKEY)asm_handle_file_create(fp, file_name);

	printf("%s:%d %s ret=%d ret_key=%p\n", __func__, __LINE__, str_sub_key, *return_value, *result);
	ASM_FREE(str_sub_key);

	return ASM_RET_OK;
}

static AsmRet rapi_device_registry_default_query_value
	(RapiDeviceRegistry* thiz, unsigned int* return_value, RKEY key, WStr* value_name, unsigned int data_length, unsigned int* type, unsigned int* ret_data_length, void** ret_data)
{
	RegRecord record = {0};
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	FILE* fp = NULL;
	asm_handle_get_handle((AsmHandle*)key, (void**)&fp);

	size_t length = 0;
	char* str_value_name = wstr_to_ascii(value_name);
	if(registry_get_record(fp, str_value_name, &record) == ASM_RET_OK)
	{
		length = MIN(data_length, record.value_length);
		*ret_data = malloc(length);
		memcpy(*ret_data, record.value, length);
		*ret_data_length = length;
	}
	else
	{
		*return_value = -1;
	}
	printf("%s:%d: %s length=%d %d value:", __func__, __LINE__, str_value_name, length, *return_value);

	switch(record.type)
	{
		case RAPI_REG_DWORD:
		{
			printf("%d", *(unsigned int*)record.value);
			break;
		}
		case RAPI_REG_SZ:
		{
			printf("%s", record.value);
			break;
		}
		default:
		{
			printf("%p", record.value);
			break;
		}
	}
	printf("\n");

	ASM_FREE(str_value_name);

	return ASM_RET_OK;
}

static AsmRet rapi_device_registry_default_close_key
	(RapiDeviceRegistry* thiz, unsigned int* return_value, RKEY key )
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	
	asm_handle_destroy((AsmHandle*)key);

	printf("%s:%d key=%p return %d\n", __func__, __LINE__, key, *return_value);

	return ASM_RET_OK;
}

static AsmRet rapi_device_registry_default_delete_key
	(RapiDeviceRegistry* thiz, unsigned int* return_value, RKEY key, WStr* sub_key )
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	char* str_sub_key = wstr_to_ascii(sub_key);
	char file_name[RAPI_MAX_PATH + 1] = {0};
	snprintf(file_name, RAPI_MAX_PATH, "registry-%p-%s", key, str_sub_key);
	
	unlink(file_name);

	printf("%s:%d %s ret=%d\n", __func__, __LINE__, str_sub_key, *return_value);
	ASM_FREE(str_sub_key);

	return ASM_RET_OK;
}

static AsmRet rapi_device_registry_default_delete_value
	(RapiDeviceRegistry* thiz, unsigned int* return_value, RKEY key, WStr* value_name )
{
	RegRecord record = {0};
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	
	FILE* fp = NULL;
	asm_handle_get_handle((AsmHandle*)key, (void**)&fp);

	char* str_value_name = wstr_to_ascii(value_name);
	registry_del_record(fp, str_value_name);

	printf("%s:%d: %s %d\n", __func__, __LINE__, str_value_name, *return_value);

	ASM_FREE(str_value_name);

	return ASM_RET_OK;
}

static AsmRet rapi_device_registry_default_enum_key
	(RapiDeviceRegistry* thiz, unsigned int* return_value, RKEY key, unsigned int index, unsigned int name_length, unsigned int zero1, unsigned int zero2, WStr** name)
{
	RegRecord record = {0};
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	FILE* fp = NULL;
	asm_handle_get_handle((AsmHandle*)key, (void**)&fp);

	fseek(fp, 0, SEEK_SET);
	size_t length = 0;
	size_t i = 0;
	while(fread(&record, sizeof(RegRecord), 1, fp))
	{
		if(record.type == RAPI_REG_NONE)
		{
			continue;
		}
		if(i == index)
		{
			*name = wstr_dup_from_ascii(record.name);
			break;
		}
		else
		{
			i++;
		}
	}

	return ASM_RET_OK;
}

static AsmRet rapi_device_registry_default_set_value
	(RapiDeviceRegistry* thiz, unsigned int* return_value, RKEY key, WStr* value_name, unsigned int type, unsigned int data_length, void* data)
{
	RegRecord record = {0};
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	
	FILE* fp = NULL;
	asm_handle_get_handle((AsmHandle*)key, (void**)&fp);
	char* str_value_name = wstr_to_ascii(value_name);
	registry_del_record(fp, str_value_name);

	record.type = type;
	strncpy(record.name, str_value_name, sizeof(record.name) - 1);
	record.value_length = data_length;
	memcpy(record.value, data, MIN(sizeof(record.value), data_length));

	registry_add_record(fp, str_value_name, &record);
	printf("%s:%d: %s %d value:", __func__, __LINE__, str_value_name, *return_value);
	ASM_FREE(str_value_name);

	switch(record.type)
	{
		case RAPI_REG_DWORD:
		{
			printf("%d", *(unsigned int*)record.value);
			break;
		}
		case RAPI_REG_SZ:
		{
			printf("%s", record.value);
			break;
		}
		default:
		{
			printf("%p", record.value);
			break;
		}
	}
	printf("\n");

	return ASM_RET_OK;
}

void rapi_device_registry_default_destroy(RapiDeviceRegistry* thiz)
{
	ASM_FREE(thiz);

	return;
}

RapiDeviceRegistry* rapi_device_registry_default_create(void)
{
	RapiDeviceRegistry* thiz = (RapiDeviceRegistry*)ASM_ALLOC(RapiDeviceRegistry, sizeof(PrivInfo));
	thiz->create_key = rapi_device_registry_default_create_key;
	thiz->open_key = rapi_device_registry_default_open_key;
	thiz->query_value = rapi_device_registry_default_query_value;
	thiz->close_key = rapi_device_registry_default_close_key;
	thiz->delete_key = rapi_device_registry_default_delete_key;
	thiz->delete_value = rapi_device_registry_default_delete_value;
	thiz->enum_key = rapi_device_registry_default_enum_key;
	thiz->set_value = rapi_device_registry_default_set_value;
	thiz->destroy = rapi_device_registry_default_destroy;

	return thiz;
}

