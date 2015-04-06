/*
 * File:    rapi_device_fileman.h
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

#include <asm-common.h>
#include <rapi_lib.h>

#ifndef RAPI_DEVICE_FILEMAN_H
#define RAPI_DEVICE_FILEMAN_H

struct _RapiDeviceFileman;
typedef struct _RapiDeviceFileman RapiDeviceFileman;

typedef AsmRet (*RapiDeviceFilemanCreateFileFunc)
	(RapiDeviceFileman* thiz, unsigned int* return_value, WStr* file_name, unsigned int access_flags, unsigned int share_mode, unsigned int creation_disposition, unsigned int flags_and_attributes, unsigned int template_file );
typedef AsmRet (*RapiDeviceFilemanReadFileFunc)
	(RapiDeviceFileman* thiz, unsigned int* return_value, unsigned int handle, unsigned int length, unsigned int* ret_data_length, void** ret_data);
typedef AsmRet (*RapiDeviceFilemanWriteFileFunc)
	(RapiDeviceFileman* thiz, unsigned int* return_value, unsigned int handle, unsigned int data_length, void* data,  unsigned int* bytes_written);
typedef AsmRet (*RapiDeviceFilemanSeekFunc)
	(RapiDeviceFileman* thiz, unsigned int* return_value, unsigned int handle, unsigned int low, unsigned int has_high, unsigned int high, unsigned int mode, unsigned int* ret_high);
typedef AsmRet (*RapiDeviceFilemanSeekToEndFunc)
	(RapiDeviceFileman* thiz, unsigned int* return_value, unsigned int handle );
typedef AsmRet (*RapiDeviceFilemanGetFileTimeFunc)
	(RapiDeviceFileman* thiz, unsigned int* return_value, unsigned int handle, RapiFileTime** create_time, RapiFileTime** last_access_time, RapiFileTime** last_write_time);
typedef AsmRet (*RapiDeviceFilemanSetFileTimeFunc)
	(RapiDeviceFileman* thiz, unsigned int* return_value, unsigned int handle, RapiFileTime* create_time, RapiFileTime* last_access_time, RapiFileTime* last_write_time );
typedef AsmRet (*RapiDeviceFilemanCopyFileFunc)
	(RapiDeviceFileman* thiz, unsigned int* return_value, WStr* from, WStr* to, unsigned int overwrite );
typedef AsmRet (*RapiDeviceFilemanCreateDirectoryFunc)
	(RapiDeviceFileman* thiz, unsigned int* return_value, WStr* path );
typedef AsmRet (*RapiDeviceFilemanDeleteFileFunc)
	(RapiDeviceFileman* thiz, unsigned int* return_value, WStr* file );
typedef AsmRet (*RapiDeviceFilemanRemoveDirectoryFunc)
	(RapiDeviceFileman* thiz, unsigned int* return_value, WStr* path );
typedef AsmRet (*RapiDeviceFilemanMoveFileFunc)
	(RapiDeviceFileman* thiz, unsigned int* return_value, WStr* from, WStr* to );
typedef AsmRet (*RapiDeviceFilemanGetSpecialFolderFunc)
	(RapiDeviceFileman* thiz, unsigned int* return_value, unsigned int folder, unsigned int buffer_length, WStr** ret_folder);
typedef AsmRet (*RapiDeviceFilemanCloseHandleFunc)
	(RapiDeviceFileman* thiz, unsigned int* return_value, unsigned int handle );
typedef AsmRet (*RapiDeviceFilemanGetSizeFunc)
	(RapiDeviceFileman* thiz, unsigned int* return_value, unsigned int handle );
typedef AsmRet (*RapiDeviceFilemanFindAllFilesFunc)
	(RapiDeviceFileman* thiz, unsigned int* return_value, WStr* path, unsigned int flags, unsigned int* count, RapiFindData** find_data);
typedef AsmRet (*RapiDeviceFilemanFindFirstFileFunc)
	(RapiDeviceFileman* thiz, unsigned int* return_value, WStr* path, RapiFindData** find_data, unsigned int* handle);
typedef AsmRet (*RapiDeviceFilemanFindNextFileFunc)
	(RapiDeviceFileman* thiz, unsigned int* return_value, unsigned int handle, RapiFindData** find_data);
typedef AsmRet (*RapiDeviceFilemanFindCloseFunc)
	(RapiDeviceFileman* thiz, unsigned int* return_value, unsigned int* handle );

typedef void (*RapiDeviceFilemanDestroyFunc)(RapiDeviceFileman* thiz);

struct _RapiDeviceFileman
{
	RapiDeviceFilemanCreateFileFunc create_file;
	RapiDeviceFilemanReadFileFunc read_file;
	RapiDeviceFilemanWriteFileFunc write_file;
	RapiDeviceFilemanSeekFunc seek;
	RapiDeviceFilemanSeekToEndFunc seek_to_end;
	RapiDeviceFilemanGetFileTimeFunc get_file_time;
	RapiDeviceFilemanSetFileTimeFunc set_file_time;
	RapiDeviceFilemanCopyFileFunc copy_file;
	RapiDeviceFilemanCreateDirectoryFunc create_directory;
	RapiDeviceFilemanDeleteFileFunc delete_file;
	RapiDeviceFilemanRemoveDirectoryFunc remove_directory;
	RapiDeviceFilemanMoveFileFunc move_file;
	RapiDeviceFilemanGetSpecialFolderFunc get_special_folder;
	RapiDeviceFilemanCloseHandleFunc close_handle;
	RapiDeviceFilemanGetSizeFunc get_size;
	RapiDeviceFilemanFindAllFilesFunc find_all_files;
	RapiDeviceFilemanFindFirstFileFunc find_first_file;
	RapiDeviceFilemanFindNextFileFunc find_next_file;
	RapiDeviceFilemanFindCloseFunc find_close;
	RapiDeviceFilemanDestroyFunc destroy;
	char priv[0];
};

static inline AsmRet rapi_device_fileman_create_file
	(RapiDeviceFileman* thiz, unsigned int* return_value, WStr* file_name, unsigned int access_flags, unsigned int share_mode, unsigned int creation_disposition, unsigned int flags_and_attributes, unsigned int template_file )
{
	asm_return_val_if_fail(thiz != NULL && thiz->create_file != NULL, ASM_RET_FAIL);

	return thiz->create_file(thiz, return_value,  file_name,  access_flags,  share_mode,  creation_disposition,  flags_and_attributes,  template_file);
}

static inline AsmRet rapi_device_fileman_read_file
	(RapiDeviceFileman* thiz, unsigned int* return_value, unsigned int handle, unsigned int length, unsigned int* ret_data_length, void** ret_data)
{
	asm_return_val_if_fail(thiz != NULL && thiz->read_file != NULL, ASM_RET_FAIL);

	return thiz->read_file(thiz, return_value,  handle,  length, ret_data_length,  ret_data);
}

static inline AsmRet rapi_device_fileman_write_file
	(RapiDeviceFileman* thiz, unsigned int* return_value, unsigned int handle, unsigned int data_length, void* data,  unsigned int* bytes_written)
{
	asm_return_val_if_fail(thiz != NULL && thiz->write_file != NULL, ASM_RET_FAIL);

	return thiz->write_file(thiz, return_value,  handle,  data_length,  data,  bytes_written);
}

static inline AsmRet rapi_device_fileman_seek
	(RapiDeviceFileman* thiz, unsigned int* return_value, unsigned int handle, unsigned int low, unsigned int has_high, unsigned int high, unsigned int mode, unsigned int* ret_high)
{
	asm_return_val_if_fail(thiz != NULL && thiz->seek != NULL, ASM_RET_FAIL);

	return thiz->seek(thiz, return_value,  handle,  low,  has_high,  high,  mode, ret_high);
}

static inline AsmRet rapi_device_fileman_seek_to_end
	(RapiDeviceFileman* thiz, unsigned int* return_value, unsigned int handle )
{
	asm_return_val_if_fail(thiz != NULL && thiz->seek_to_end != NULL, ASM_RET_FAIL);

	return thiz->seek_to_end(thiz, return_value,  handle);
}

static inline AsmRet rapi_device_fileman_get_file_time
	(RapiDeviceFileman* thiz, unsigned int* return_value, unsigned int handle, RapiFileTime** create_time, RapiFileTime** last_access_time, RapiFileTime** last_write_time)
{
	asm_return_val_if_fail(thiz != NULL && thiz->get_file_time != NULL, ASM_RET_FAIL);

	return thiz->get_file_time(thiz, return_value,  handle, create_time,  last_access_time,  last_write_time);
}

static inline AsmRet rapi_device_fileman_set_file_time
	(RapiDeviceFileman* thiz, unsigned int* return_value, unsigned int handle, RapiFileTime* create_time, RapiFileTime* last_access_time, RapiFileTime* last_write_time )
{
	asm_return_val_if_fail(thiz != NULL && thiz->set_file_time != NULL, ASM_RET_FAIL);

	return thiz->set_file_time(thiz, return_value,  handle,  create_time,  last_access_time,  last_write_time);
}

static inline AsmRet rapi_device_fileman_copy_file
	(RapiDeviceFileman* thiz, unsigned int* return_value, WStr* from, WStr* to, unsigned int overwrite )
{
	asm_return_val_if_fail(thiz != NULL && thiz->copy_file != NULL, ASM_RET_FAIL);

	return thiz->copy_file(thiz, return_value,  from,  to,  overwrite);
}

static inline AsmRet rapi_device_fileman_create_directory
	(RapiDeviceFileman* thiz, unsigned int* return_value, WStr* path )
{
	asm_return_val_if_fail(thiz != NULL && thiz->create_directory != NULL, ASM_RET_FAIL);

	return thiz->create_directory(thiz, return_value,  path);
}

static inline AsmRet rapi_device_fileman_delete_file
	(RapiDeviceFileman* thiz, unsigned int* return_value, WStr* file )
{
	asm_return_val_if_fail(thiz != NULL && thiz->delete_file != NULL, ASM_RET_FAIL);

	return thiz->delete_file(thiz, return_value,  file);
}

static inline AsmRet rapi_device_fileman_remove_directory
	(RapiDeviceFileman* thiz, unsigned int* return_value, WStr* path )
{
	asm_return_val_if_fail(thiz != NULL && thiz->remove_directory != NULL, ASM_RET_FAIL);

	return thiz->remove_directory(thiz, return_value,  path);
}

static inline AsmRet rapi_device_fileman_move_file
	(RapiDeviceFileman* thiz, unsigned int* return_value, WStr* from, WStr* to )
{
	asm_return_val_if_fail(thiz != NULL && thiz->move_file != NULL, ASM_RET_FAIL);

	return thiz->move_file(thiz, return_value,  from,  to);
}

static inline AsmRet rapi_device_fileman_get_special_folder
	(RapiDeviceFileman* thiz, unsigned int* return_value, unsigned int folder, unsigned int buffer_length, WStr** ret_folder)
{
	asm_return_val_if_fail(thiz != NULL && thiz->get_special_folder != NULL, ASM_RET_FAIL);

	return thiz->get_special_folder(thiz, return_value,  folder,  buffer_length, ret_folder);
}

static inline AsmRet rapi_device_fileman_close_handle
	(RapiDeviceFileman* thiz, unsigned int* return_value, unsigned int handle )
{
	asm_return_val_if_fail(thiz != NULL && thiz->close_handle != NULL, ASM_RET_FAIL);

	return thiz->close_handle(thiz, return_value,  handle);
}

static inline AsmRet rapi_device_fileman_get_size
	(RapiDeviceFileman* thiz, unsigned int* return_value, unsigned int handle )
{
	asm_return_val_if_fail(thiz != NULL && thiz->get_size != NULL, ASM_RET_FAIL);

	return thiz->get_size(thiz, return_value,  handle);
}

static inline AsmRet rapi_device_fileman_find_all_files
	(RapiDeviceFileman* thiz, unsigned int* return_value, WStr* path, unsigned int flags, unsigned int* count, RapiFindData** find_data)
{
	asm_return_val_if_fail(thiz != NULL && thiz->find_all_files != NULL, ASM_RET_FAIL);

	return thiz->find_all_files(thiz, return_value,  path,  flags, count, find_data);
}

static inline AsmRet rapi_device_fileman_find_first_file
	(RapiDeviceFileman* thiz, unsigned int* return_value, WStr* path, RapiFindData** find_data, unsigned int* handle)
{
	asm_return_val_if_fail(thiz != NULL && thiz->find_first_file != NULL, ASM_RET_FAIL);

	return thiz->find_first_file(thiz, return_value,  path, find_data,  handle);
}

static inline AsmRet rapi_device_fileman_find_next_file
	(RapiDeviceFileman* thiz, unsigned int* return_value, unsigned int handle, RapiFindData** find_data)
{
	asm_return_val_if_fail(thiz != NULL && thiz->find_next_file != NULL, ASM_RET_FAIL);

	return thiz->find_next_file(thiz, return_value,  handle, find_data);
}

static inline AsmRet rapi_device_fileman_find_close
	(RapiDeviceFileman* thiz, unsigned int* return_value, unsigned int* handle )
{
	asm_return_val_if_fail(thiz != NULL && thiz->find_close != NULL, ASM_RET_FAIL);

	return thiz->find_close(thiz, return_value,  handle);
}

static inline void rapi_device_fileman_destroy(RapiDeviceFileman* thiz)
{
	asm_return_if_fail(thiz != NULL && thiz->destroy != NULL);
	thiz->destroy(thiz);

	return;
}
#endif/*RAPI_DEVICE_FILEMAN_H*/

