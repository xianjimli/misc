/*
 * File:    rapi_device_fileman_dispatch.c
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

#include <rapi_device_fileman_dispatch.h>

static AsmRet rapi_device_connection_session_handle_create_file(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	WStr* file_name = NULL;
	unsigned int access_flags = 0;
	unsigned int share_mode = 0;
	unsigned int creation_disposition = 0;
	unsigned int flags_and_attributes = 0;
	unsigned int template_file = 0;

	unsigned int return_value = RAPI_SUCCESS;

	do
	{
		ret = rapi_device_read_fileman_create_file(priv->input, &file_name, &access_flags, &share_mode, &creation_disposition, &flags_and_attributes, &template_file);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_fileman_create_file(priv->fileman, &return_value, file_name, access_flags, share_mode, creation_disposition, flags_and_attributes, template_file);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_write_fileman_create_file(priv->output, RAPI_SUCCESS, return_value);
	}while(0);

	ASM_FREE(file_name);
	return ret;
}
static AsmRet rapi_device_connection_session_handle_read_file(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	unsigned int handle = 0;
	unsigned int length = 0;
	unsigned int ret_data_length = 0;
	void* ret_data = NULL;

	unsigned int return_value = RAPI_SUCCESS;

	do
	{
		ret = rapi_device_read_fileman_read_file(priv->input, &handle, &length);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_fileman_read_file(priv->fileman, &return_value, handle, length, &ret_data_length, &ret_data);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_write_fileman_read_file(priv->output, RAPI_SUCCESS, return_value, ret_data_length, ret_data);
	}while(0);

	ASM_FREE(ret_data);
	return ret;
}
static AsmRet rapi_device_connection_session_handle_write_file(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	unsigned int handle = 0;
	unsigned int data_length = 0;
	void* data = NULL;
	unsigned int bytes_written = 0;

	unsigned int return_value = RAPI_SUCCESS;

	do
	{
		ret = rapi_device_read_fileman_write_file(priv->input, &handle, &data_length, &data);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_fileman_write_file(priv->fileman, &return_value, handle, data_length, data, &bytes_written);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_write_fileman_write_file(priv->output, RAPI_SUCCESS, return_value, bytes_written);
	}while(0);

	ASM_FREE(data);
	return ret;
}
static AsmRet rapi_device_connection_session_handle_seek(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	unsigned int handle = 0;
	unsigned int low = 0;
	unsigned int has_high = 0;
	unsigned int high = 0;
	unsigned int mode = 0;
	unsigned int ret_high = 0;

	unsigned int return_value = RAPI_SUCCESS;

	do
	{
		ret = rapi_device_read_fileman_seek(priv->input, &handle, &low, &has_high, &high, &mode);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_fileman_seek(priv->fileman, &return_value, handle, low, has_high, high, mode, &ret_high);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_write_fileman_seek(priv->output, RAPI_SUCCESS, return_value, ret_high);
	}while(0);

	return ret;
}
static AsmRet rapi_device_connection_session_handle_seek_to_end(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	unsigned int handle = 0;

	unsigned int return_value = RAPI_SUCCESS;

	do
	{
		ret = rapi_device_read_fileman_seek_to_end(priv->input, &handle);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_fileman_seek_to_end(priv->fileman, &return_value, handle);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_write_fileman_seek_to_end(priv->output, RAPI_SUCCESS, return_value);
	}while(0);

	return ret;
}
static AsmRet rapi_device_connection_session_handle_get_file_time(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	unsigned int handle = 0;
	RapiFileTime* create_time = 0;
	RapiFileTime* last_access_time = 0;
	RapiFileTime* last_write_time = 0;

	unsigned int return_value = RAPI_SUCCESS;

	do
	{
		ret = rapi_device_read_fileman_get_file_time(priv->input, &handle);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_fileman_get_file_time(priv->fileman, &return_value, handle, &create_time, &last_access_time, &last_write_time);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_write_fileman_get_file_time(priv->output, RAPI_SUCCESS, return_value, create_time, last_access_time, last_write_time);
	}while(0);

	ASM_FREE(create_time);
	ASM_FREE(last_access_time);
	ASM_FREE(last_write_time);
	return ret;
}
static AsmRet rapi_device_connection_session_handle_set_file_time(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	unsigned int handle = 0;
	RapiFileTime* create_time = 0;
	RapiFileTime* last_access_time = 0;
	RapiFileTime* last_write_time = 0;

	unsigned int return_value = RAPI_SUCCESS;

	do
	{
		ret = rapi_device_read_fileman_set_file_time(priv->input, &handle, &create_time, &last_access_time, &last_write_time);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_fileman_set_file_time(priv->fileman, &return_value, handle, create_time, last_access_time, last_write_time);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_write_fileman_set_file_time(priv->output, RAPI_SUCCESS, return_value);
	}while(0);

	ASM_FREE(create_time);
	ASM_FREE(last_access_time);
	ASM_FREE(last_write_time);
	return ret;
}
static AsmRet rapi_device_connection_session_handle_copy_file(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	WStr* from = NULL;
	WStr* to = NULL;
	unsigned int overwrite = 0;

	unsigned int return_value = RAPI_SUCCESS;

	do
	{
		ret = rapi_device_read_fileman_copy_file(priv->input, &from, &to, &overwrite);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_fileman_copy_file(priv->fileman, &return_value, from, to, overwrite);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_write_fileman_copy_file(priv->output, RAPI_SUCCESS, return_value);
	}while(0);

	ASM_FREE(from);
	ASM_FREE(to);
	return ret;
}
static AsmRet rapi_device_connection_session_handle_create_directory(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	WStr* path = NULL;

	unsigned int return_value = RAPI_SUCCESS;

	do
	{
		ret = rapi_device_read_fileman_create_directory(priv->input, &path);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_fileman_create_directory(priv->fileman, &return_value, path);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_write_fileman_create_directory(priv->output, RAPI_SUCCESS, return_value);
	}while(0);

	ASM_FREE(path);
	return ret;
}
static AsmRet rapi_device_connection_session_handle_delete_file(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	WStr* file = NULL;

	unsigned int return_value = RAPI_SUCCESS;

	do
	{
		ret = rapi_device_read_fileman_delete_file(priv->input, &file);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_fileman_delete_file(priv->fileman, &return_value, file);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_write_fileman_delete_file(priv->output, RAPI_SUCCESS, return_value);
	}while(0);

	ASM_FREE(file);
	return ret;
}
static AsmRet rapi_device_connection_session_handle_remove_directory(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	WStr* path = NULL;

	unsigned int return_value = RAPI_SUCCESS;

	do
	{
		ret = rapi_device_read_fileman_remove_directory(priv->input, &path);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_fileman_remove_directory(priv->fileman, &return_value, path);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_write_fileman_remove_directory(priv->output, RAPI_SUCCESS, return_value);
	}while(0);

	ASM_FREE(path);
	return ret;
}
static AsmRet rapi_device_connection_session_handle_move_file(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	WStr* from = NULL;
	WStr* to = NULL;

	unsigned int return_value = RAPI_SUCCESS;

	do
	{
		ret = rapi_device_read_fileman_move_file(priv->input, &from, &to);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_fileman_move_file(priv->fileman, &return_value, from, to);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_write_fileman_move_file(priv->output, RAPI_SUCCESS, return_value);
	}while(0);

	ASM_FREE(from);
	ASM_FREE(to);
	return ret;
}
static AsmRet rapi_device_connection_session_handle_get_special_folder(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	unsigned int folder = 0;
	unsigned int buffer_length = 0;
	WStr* ret_folder = NULL;

	unsigned int return_value = RAPI_SUCCESS;

	do
	{
		ret = rapi_device_read_fileman_get_special_folder(priv->input, &folder, &buffer_length);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_fileman_get_special_folder(priv->fileman, &return_value, folder, buffer_length, &ret_folder);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_write_fileman_get_special_folder(priv->output, RAPI_SUCCESS, return_value, ret_folder);
	}while(0);

	ASM_FREE(ret_folder);
	return ret;
}
static AsmRet rapi_device_connection_session_handle_close_handle(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	unsigned int handle = 0;

	unsigned int return_value = RAPI_SUCCESS;

	do
	{
		ret = rapi_device_read_fileman_close_handle(priv->input, &handle);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_fileman_close_handle(priv->fileman, &return_value, handle);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_write_fileman_close_handle(priv->output, RAPI_SUCCESS, return_value);
	}while(0);

	return ret;
}
static AsmRet rapi_device_connection_session_handle_get_size(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	unsigned int handle = 0;

	unsigned int return_value = RAPI_SUCCESS;

	do
	{
		ret = rapi_device_read_fileman_get_size(priv->input, &handle);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_fileman_get_size(priv->fileman, &return_value, handle);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_write_fileman_get_size(priv->output, RAPI_SUCCESS, return_value);
	}while(0);

	return ret;
}
static AsmRet rapi_device_connection_session_handle_find_all_files(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	WStr* path = NULL;
	unsigned int flags = 0;
	unsigned int count = 0;
	RapiFindData* find_data = 0;

	unsigned int return_value = RAPI_SUCCESS;

	do
	{
		ret = rapi_device_read_fileman_find_all_files(priv->input, &path, &flags);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_fileman_find_all_files(priv->fileman, &return_value, path, flags, &count, &find_data);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_write_fileman_find_all_files(priv->output, RAPI_SUCCESS, return_value, count, find_data);
	}while(0);

	ASM_FREE(path);
	ASM_FREE(find_data);
	return ret;
}
static AsmRet rapi_device_connection_session_handle_find_first_file(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	WStr* path = NULL;
	RapiFindData* find_data = 0;
	unsigned int handle = 0;

	unsigned int return_value = RAPI_SUCCESS;

	do
	{
		ret = rapi_device_read_fileman_find_first_file(priv->input, &path);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_fileman_find_first_file(priv->fileman, &return_value, path, &find_data, &handle);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_write_fileman_find_first_file(priv->output, RAPI_SUCCESS, return_value, find_data, handle);
	}while(0);

	ASM_FREE(path);
	ASM_FREE(find_data);
	return ret;
}
static AsmRet rapi_device_connection_session_handle_find_next_file(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	unsigned int handle = 0;
	RapiFindData* find_data = 0;

	unsigned int return_value = RAPI_SUCCESS;

	do
	{
		ret = rapi_device_read_fileman_find_next_file(priv->input, &handle);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_fileman_find_next_file(priv->fileman, &return_value, handle, &find_data);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_write_fileman_find_next_file(priv->output, RAPI_SUCCESS, return_value, find_data);
	}while(0);

	ASM_FREE(find_data);
	return ret;
}
static AsmRet rapi_device_connection_session_handle_find_close(AsmConnection* thiz)
{
	AsmRet ret = ASM_RET_FAIL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	unsigned int* handle = 0;

	unsigned int return_value = RAPI_SUCCESS;

	do
	{
		ret = rapi_device_read_fileman_find_close(priv->input, &handle);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_fileman_find_close(priv->fileman, &return_value, handle);
		if(ret != ASM_RET_OK) break;
		ret = rapi_device_write_fileman_find_close(priv->output, RAPI_SUCCESS, return_value);
	}while(0);

	return ret;
}
AsmRet rapi_device_connection_session_fileman_command_dispatch(AsmConnection* thiz, unsigned int cmd)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);

	switch(cmd)
	{
		case RAPI_COMMAND_FILEMAN_CREATE_FILE:
		{
			ret = rapi_device_connection_session_handle_create_file(thiz);
			break;
		}
		case RAPI_COMMAND_FILEMAN_READ_FILE:
		{
			ret = rapi_device_connection_session_handle_read_file(thiz);
			break;
		}
		case RAPI_COMMAND_FILEMAN_WRITE_FILE:
		{
			ret = rapi_device_connection_session_handle_write_file(thiz);
			break;
		}
		case RAPI_COMMAND_FILEMAN_SEEK:
		{
			ret = rapi_device_connection_session_handle_seek(thiz);
			break;
		}
		case RAPI_COMMAND_FILEMAN_SEEK_TO_END:
		{
			ret = rapi_device_connection_session_handle_seek_to_end(thiz);
			break;
		}
		case RAPI_COMMAND_FILEMAN_GET_FILE_TIME:
		{
			ret = rapi_device_connection_session_handle_get_file_time(thiz);
			break;
		}
		case RAPI_COMMAND_FILEMAN_SET_FILE_TIME:
		{
			ret = rapi_device_connection_session_handle_set_file_time(thiz);
			break;
		}
		case RAPI_COMMAND_FILEMAN_COPY_FILE:
		{
			ret = rapi_device_connection_session_handle_copy_file(thiz);
			break;
		}
		case RAPI_COMMAND_FILEMAN_CREATE_DIRECTORY:
		{
			ret = rapi_device_connection_session_handle_create_directory(thiz);
			break;
		}
		case RAPI_COMMAND_FILEMAN_DELETE_FILE:
		{
			ret = rapi_device_connection_session_handle_delete_file(thiz);
			break;
		}
		case RAPI_COMMAND_FILEMAN_REMOVE_DIRECTORY:
		{
			ret = rapi_device_connection_session_handle_remove_directory(thiz);
			break;
		}
		case RAPI_COMMAND_FILEMAN_MOVE_FILE:
		{
			ret = rapi_device_connection_session_handle_move_file(thiz);
			break;
		}
		case RAPI_COMMAND_FILEMAN_GET_SPECIAL_FOLDER:
		{
			ret = rapi_device_connection_session_handle_get_special_folder(thiz);
			break;
		}
		case RAPI_COMMAND_FILEMAN_CLOSE_HANDLE:
		{
			ret = rapi_device_connection_session_handle_close_handle(thiz);
			break;
		}
		case RAPI_COMMAND_FILEMAN_GET_SIZE:
		{
			ret = rapi_device_connection_session_handle_get_size(thiz);
			break;
		}
		case RAPI_COMMAND_FILEMAN_FIND_ALL_FILES:
		{
			ret = rapi_device_connection_session_handle_find_all_files(thiz);
			break;
		}
		case RAPI_COMMAND_FILEMAN_FIND_FIRST_FILE:
		{
			ret = rapi_device_connection_session_handle_find_first_file(thiz);
			break;
		}
		case RAPI_COMMAND_FILEMAN_FIND_NEXT_FILE:
		{
			ret = rapi_device_connection_session_handle_find_next_file(thiz);
			break;
		}
		case RAPI_COMMAND_FILEMAN_FIND_CLOSE:
		{
			ret = rapi_device_connection_session_handle_find_close(thiz);
			break;
		}
		default: ret = ASM_RET_UNHANDLED;break;
	}
	return ret;
}
