/*
 * File:    rapi_device_fileman_default.c
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

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <asm-wstr.h>
#include <rapi_test_data.h>
#include <asm-handle-file.h>
#include <rapi_device_fileman_default.h>

typedef struct _PrivInfo
{
	int dummy;

}PrivInfo;

static AsmRet rapi_device_fileman_default_create_file
	(RapiDeviceFileman* thiz, unsigned int* return_value, WStr* file_name, unsigned int access_flags, unsigned int share_mode, unsigned int creation_disposition, unsigned int flags_and_attributes, unsigned int template_file )
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	char* name = wstr_to_ascii(file_name);
	int file_exist = 0;
	FILE* fp = NULL;
	mode_t f_mode = S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH;
	int ret = ASM_RET_NR; 
	
	if(access(name, F_OK) == 0)
	{
//		*return_value = ERROR_ALREADY_EXISTS; //183
		file_exist = 1;
	}
	
	switch(creation_disposition)
	{
		case RAPI_CREATION_DISPOSITION_CREATE_NEW:
		{
			if(file_exist)
			{
				ret = ASM_RET_FAIL; 
			}
			else
			{
				if((fp = fopen(name, "wb+")) != NULL)
				{
					ret = ASM_RET_OK;
				}
				else
				{
					ret = ASM_RET_FAIL; 
				}
			}
			break;
		}
		case RAPI_CREATION_DISPOSITION_CREATE_ALWAYS:
		{
			if((fp = fopen(name, "wb+")) != NULL)
			{
				ret = ASM_RET_OK;
			}
			else
			{
				ret = ASM_RET_FAIL; 
			}
			break;
		}
		case RAPI_CREATION_DISPOSITION_OPEN_EXISTING:
		{
			if(file_exist)
			{
				const char* open_flag = NULL;
				if((access_flags & RAPI_ACCESS_READ) &&
					(access_flags & RAPI_ACCESS_WRITE))
				{
					open_flag = "rb+";
				}
				else if(access_flags & RAPI_ACCESS_WRITE)
				{
					open_flag = "ab";
				}
				else 
				{
					open_flag = "rb";
				}

				if((fp = fopen(name, open_flag)) != NULL)
				{
					ret = ASM_RET_OK;
				}
				else
				{
					ret = ASM_RET_FAIL; 
				}
			}
			else
			{
				ret = ASM_RET_FAIL;
			}
			break;
		}
		case RAPI_CREATION_DISPOSITION_OPEN_ALWAYS:
		{
			if((fp = fopen(name, "ab+")) != NULL)
			{
				ret = ASM_RET_OK;
			}
			else
			{
				ret = ASM_RET_FAIL; 
			}
			break;
		}
		case RAPI_CREATION_DISPOSITION_TRUNCATE_EXISTING:
		{
			if(file_exist)
			{
				if((fp = fopen(name, "wb+")) != NULL)
				{
					ret = ASM_RET_OK;
				}
				else
				{
					ret = ASM_RET_FAIL; 
				}
			}
			else
			{
				ret = ASM_RET_FAIL;
			}
			break;
		}
		case RAPI_CREATION_DISPOSITION_OPEN_FOR_LOADER:
		default:
		{
			ret = ASM_RET_NR;
			break;
		}
	}
	
	if((ret == ASM_RET_OK)&&
		(fp != NULL) &&
		!(flags_and_attributes & RAPI_FILE_ATTRIBUTE_NORMAL)
		)
	{
		if(flags_and_attributes & RAPI_FILE_ATTRIBUTE_READONLY)
		{
			f_mode &= ~S_IWOTH;
			f_mode &= ~S_IWGRP;
			f_mode &= ~S_IWUSR;
		}
		if(flags_and_attributes & RAPI_FILE_ATTRIBUTE_SYSTEM)
		{
			f_mode &= ~S_IWOTH;
			f_mode &= ~S_IWGRP;
		}
			
	}
	
	*return_value = (unsigned int)asm_handle_file_create(fp, name);

	ASM_FREE(name);
	printf("%s:%d: creation_disposition = %p %s\n", __func__, __LINE__, creation_disposition, name);

	return ASM_RET_OK;
}

static AsmRet rapi_device_fileman_default_read_file
	(RapiDeviceFileman* thiz, unsigned int* return_value, unsigned int handle, unsigned int length, unsigned int* ret_data_length, void** ret_data)
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	FILE* fp = NULL;
	asm_handle_get_handle((AsmHandle*)handle, (void**)&fp);

	*ret_data = (char*)malloc(length);
	*ret_data_length = fread(*ret_data, 1, length, fp);
	*return_value = 1;

	printf("%s:%d: ret_data_length = %d length=%d\n", __func__, __LINE__, *ret_data_length, length);

	return ASM_RET_OK;
}

static AsmRet rapi_device_fileman_default_write_file
	(RapiDeviceFileman* thiz, unsigned int* return_value, unsigned int handle, unsigned int data_length, void* data,  unsigned int* bytes_written)
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	FILE* fp = NULL;
	asm_handle_get_handle((AsmHandle*)handle, (void**)&fp);

	*bytes_written = fwrite(data, 1, data_length, fp);
	fflush(fp);

	*return_value = 1;
	
	printf("%s:%d: length=%d\n", __func__, __LINE__, data_length);

	return ASM_RET_OK;
}

static AsmRet rapi_device_fileman_default_seek
	(RapiDeviceFileman* thiz, unsigned int* return_value, unsigned int handle, unsigned int low, unsigned int has_high, unsigned int high, unsigned int mode, unsigned int* ret_high)
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	int seek_type = SEEK_SET;
	switch(mode)
	{
		case RAPI_FILE_SEEK_TYPE_BEGIN: seek_type = SEEK_SET;break;
		case RAPI_FILE_SEEK_TYPE_CURRENT:seek_type = SEEK_CUR;break;
		case RAPI_FILE_SEEK_TYPE_END:seek_type = SEEK_END;break;
		default:seek_type = SEEK_SET;break;
	}

	FILE* fp = NULL;
	asm_handle_get_handle((AsmHandle*)handle, (void**)&fp);

	fseek(fp, low, seek_type);

	*return_value = 1;

	printf("%s:%d: handle=%p mode=%d offset=%d\n", __func__, __LINE__, handle, mode, low);

	return ASM_RET_OK;
}

static AsmRet rapi_device_fileman_default_seek_to_end
	(RapiDeviceFileman* thiz, unsigned int* return_value, unsigned int handle )
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	FILE* fp = NULL;
	asm_handle_get_handle((AsmHandle*)handle, (void**)&fp);

	fseek(fp, 0, SEEK_END);

	*return_value = 1;

	return ASM_RET_OK;
}

static AsmRet rapi_device_fileman_default_get_file_time
	(RapiDeviceFileman* thiz, unsigned int* return_value, unsigned int handle, RapiFileTime** create_time, RapiFileTime** last_access_time, RapiFileTime** last_write_time)
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	return ASM_RET_OK;
}

static AsmRet rapi_device_fileman_default_set_file_time
	(RapiDeviceFileman* thiz, unsigned int* return_value, unsigned int handle, RapiFileTime* create_time, RapiFileTime* last_access_time, RapiFileTime* last_write_time )
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	return ASM_RET_OK;
}

static AsmRet rapi_device_fileman_default_copy_file
	(RapiDeviceFileman* thiz, unsigned int* return_value, WStr* from, WStr* to, unsigned int overwrite )
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	
	char* file_from = wstr_to_ascii(from);
	char* file_to = wstr_to_ascii(to);

	*return_value = 0;
	if(asm_file_length(file_from) >= 0)
	{
		char* content = NULL;
		size_t length = 0;
		
		if(asm_read_file(file_from, &content, &length) == ASM_RET_OK)
		{
			asm_write_file(file_to, content, length);
			ASM_FREE(content);
			*return_value = 1;
		}
	}

	printf("%s:%d %s --> %s %d\n", __func__, __LINE__, file_from, file_to, *return_value);

	ASM_FREE(file_from);
	ASM_FREE(file_to);

	return ASM_RET_OK;
}

static AsmRet rapi_device_fileman_default_create_directory
	(RapiDeviceFileman* thiz, unsigned int* return_value, WStr* path )
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	char* folder = wstr_to_ascii(path);
	if(!asm_dir_exist(folder))
	{
		mkdir(folder, 0777);
		*return_value = 1;
	}
	else
	{
		*return_value = 0;
	}

	printf("%s:%d %s %d\n", __func__, __LINE__, folder, *return_value);
	ASM_FREE(folder);

	return ASM_RET_OK;
}

static AsmRet rapi_device_fileman_default_delete_file
	(RapiDeviceFileman* thiz, unsigned int* return_value, WStr* file )
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	char* name = wstr_to_ascii(file);

	if(asm_is_file_open(name))
	{
		*return_value = 0;
	}
	else
	{
		unlink(name);
		*return_value = 1;
	}

	printf("%s:%d: file_name=%s return_value = %d\n", __func__, __LINE__, name, *return_value);

	ASM_FREE(name);

	return ASM_RET_OK;
}

static AsmRet rapi_device_fileman_default_remove_directory
	(RapiDeviceFileman* thiz, unsigned int* return_value, WStr* path )
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	char* folder = wstr_to_ascii(path);
	if(asm_dir_exist(folder))
	{
		rmdir(folder);
		*return_value = 1;
	}
	else
	{
		*return_value = 0;
	}

	printf("%s:%d %s %d\n", __func__, __LINE__, folder, *return_value);
	ASM_FREE(folder);

	return ASM_RET_OK;
}

static AsmRet rapi_device_fileman_default_move_file
	(RapiDeviceFileman* thiz, unsigned int* return_value, WStr* from, WStr* to )
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	char* file_from = wstr_to_ascii(from);
	char* file_to = wstr_to_ascii(to);

	*return_value = 0;
	if(asm_file_length(file_from) >= 0)
	{
		char* content = NULL;
		size_t length = 0;
		
		if(asm_read_file(file_from, &content, &length) == ASM_RET_OK)
		{
			asm_write_file(file_to, content, length);
			ASM_FREE(content);
		}
		else
		{
			asm_write_file(file_to, "", 0);
		}

		*return_value = 1;
		unlink(file_from);
	}

	printf("%s:%d %s --> %s %d\n", __func__, __LINE__, file_from, file_to, *return_value);

	ASM_FREE(file_from);
	ASM_FREE(file_to);

	return ASM_RET_OK;
}

static AsmRet rapi_device_fileman_default_get_special_folder
	(RapiDeviceFileman* thiz, unsigned int* return_value, unsigned int folder, unsigned int buffer_length, WStr** ret_folder)
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	
	switch(folder)
	{
		case RAPI_CSIDL_PROGRAMS:
		{
			*ret_folder = wstr_dup_from_ascii(TEST_DATA_SPECIAL_FOLDER_PROGRAMS);
			break;
		}
		case RAPI_CSIDL_PERSONAL:
		{
			*ret_folder = wstr_dup_from_ascii(TEST_DATA_SPECIAL_FOLDER_PERSONAL);
			break;
		}
		case RAPI_CSIDL_FAVORITES_GRYPHON:
		{
			*ret_folder = wstr_dup_from_ascii(TEST_DATA_SPECIAL_FOLDER_FAVORITES_GRYPHON);
			break;
		}
		case RAPI_CSIDL_STARTUP:
		{
			*ret_folder = wstr_dup_from_ascii(TEST_DATA_SPECIAL_FOLDER_STARTUP);
			break;
		}
		case RAPI_CSIDL_RECENT:
		{
			*ret_folder = wstr_dup_from_ascii(TEST_DATA_SPECIAL_FOLDER_RECENT);
			break;
		}
		case RAPI_CSIDL_STARTMENU:
		{
			*ret_folder = wstr_dup_from_ascii(TEST_DATA_SPECIAL_FOLDER_STARTMENU);
			break;
		}
		case RAPI_CSIDL_DESKTOPDIRECTORY:
		{
			*ret_folder = wstr_dup_from_ascii(TEST_DATA_SPECIAL_FOLDER_DESKTOPDIRECTORY);
			break;
		}
		case RAPI_CSIDL_FONTS:
		{
			*ret_folder = wstr_dup_from_ascii(TEST_DATA_SPECIAL_FOLDER_FONTS);
			break;
		}
		case RAPI_CSIDL_FAVORITES:
		{
			*ret_folder = wstr_dup_from_ascii(TEST_DATA_SPECIAL_FOLDER_FAVORITES);
			break;
		}

		default:
		{
			printf("%s:%d: unknown folder %d\n", __func__, __LINE__, folder);
			break;
		}
	}

	return ASM_RET_OK;
}

static AsmRet rapi_device_fileman_default_close_handle
	(RapiDeviceFileman* thiz, unsigned int* return_value, unsigned int handle )
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	asm_handle_destroy((AsmHandle*)handle);

	*return_value = 1;

	printf("%s:%d: %d\n", __func__, __LINE__, *return_value);

	return ASM_RET_OK;
}

static AsmRet rapi_device_fileman_default_get_size
	(RapiDeviceFileman* thiz, unsigned int* return_value, unsigned int handle )
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	FILE* fp = NULL;
	struct stat st = {0};
	asm_handle_get_handle((AsmHandle*)handle, (void**)&fp);
	if(fstat(fileno(fp), &st) == 0)
	{
		*return_value = st.st_size;
	}
	else
	{
		*return_value = -1;
	}

	printf("%s:%d %d\n", __func__, __LINE__, *return_value);
	return ASM_RET_OK;
}

static AsmRet rapi_device_fileman_default_find_all_files
	(RapiDeviceFileman* thiz, unsigned int* return_value, WStr* path, unsigned int flags, unsigned int* count, RapiFindData** find_data)
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	return ASM_RET_OK;
}

static AsmRet rapi_device_fileman_default_find_first_file
	(RapiDeviceFileman* thiz, unsigned int* return_value, WStr* path, RapiFindData** find_data, unsigned int* handle)
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	return ASM_RET_OK;
}

static AsmRet rapi_device_fileman_default_find_next_file
	(RapiDeviceFileman* thiz, unsigned int* return_value, unsigned int handle, RapiFindData** find_data)
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	return ASM_RET_OK;
}

static AsmRet rapi_device_fileman_default_find_close
	(RapiDeviceFileman* thiz, unsigned int* return_value, unsigned int* handle )
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	return ASM_RET_OK;
}


void rapi_device_fileman_default_destroy(RapiDeviceFileman* thiz)
{
	ASM_FREE(thiz);

	return;
}

RapiDeviceFileman* rapi_device_fileman_default_create(void)
{
	RapiDeviceFileman* thiz = (RapiDeviceFileman*)ASM_ALLOC(RapiDeviceFileman, sizeof(PrivInfo));
	thiz->create_file = rapi_device_fileman_default_create_file;
	thiz->read_file = rapi_device_fileman_default_read_file;
	thiz->write_file = rapi_device_fileman_default_write_file;
	thiz->seek = rapi_device_fileman_default_seek;
	thiz->seek_to_end = rapi_device_fileman_default_seek_to_end;
	thiz->get_file_time = rapi_device_fileman_default_get_file_time;
	thiz->set_file_time = rapi_device_fileman_default_set_file_time;
	thiz->copy_file = rapi_device_fileman_default_copy_file;
	thiz->create_directory = rapi_device_fileman_default_create_directory;
	thiz->delete_file = rapi_device_fileman_default_delete_file;
	thiz->remove_directory = rapi_device_fileman_default_remove_directory;
	thiz->move_file = rapi_device_fileman_default_move_file;
	thiz->get_special_folder = rapi_device_fileman_default_get_special_folder;
	thiz->close_handle = rapi_device_fileman_default_close_handle;
	thiz->get_size = rapi_device_fileman_default_get_size;
	thiz->find_all_files = rapi_device_fileman_default_find_all_files;
	thiz->find_first_file = rapi_device_fileman_default_find_first_file;
	thiz->find_next_file = rapi_device_fileman_default_find_next_file;
	thiz->find_close = rapi_device_fileman_default_find_close;
	thiz->destroy = rapi_device_fileman_default_destroy;

	return thiz;
}

