/*
 * File:    rapi_host_fileman.c
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

#include <rapi_host_fileman.h>
struct _RapiHostFileman
{
	AsmStream* stream;
	AsmInputBuffer* input;
	AsmOutputBuffer* output;
};

RapiHostFileman* rapi_host_fileman_create(AsmStream* stream)
{
	RapiHostFileman* thiz = (RapiHostFileman*)ASM_ALLOC(RapiHostFileman, 0);
	thiz->stream = stream;
	thiz->input = asm_input_buffer_create(NULL, 0, ASM_ENDIAN_LITTLE, NULL);
	thiz->output = asm_output_buffer_create(1024, ASM_ENDIAN_LITTLE);

	return thiz;
}

AsmRet rapi_host_fileman_create_file(RapiHostFileman* thiz, unsigned int* last_error, unsigned int* return_value,
	WStr* file_name, unsigned int access_flags, unsigned int share_mode, unsigned int creation_disposition, unsigned int flags_and_attributes, unsigned int template_file )
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ret);

	asm_output_buffer_reset(thiz->output);

	do
	{
		ret = rapi_host_write_fileman_create_file(thiz->output, file_name, access_flags, share_mode, creation_disposition, flags_and_attributes, template_file);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_write(thiz->stream, thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_read(thiz->stream, thiz->input);
		if(ret != ASM_RET_OK) break;
		ret = rapi_host_read_fileman_create_file(thiz->input, last_error, return_value);
	}while(0);

	return ret;
}

AsmRet rapi_host_fileman_read_file(RapiHostFileman* thiz, unsigned int* last_error, unsigned int* return_value,
	unsigned int handle, unsigned int length, unsigned int* ret_data_length, void** ret_data)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ret);

	asm_output_buffer_reset(thiz->output);

	do
	{
		ret = rapi_host_write_fileman_read_file(thiz->output, handle, length);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_write(thiz->stream, thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_read(thiz->stream, thiz->input);
		if(ret != ASM_RET_OK) break;
		ret = rapi_host_read_fileman_read_file(thiz->input, last_error, return_value, ret_data_length, ret_data);
	}while(0);

	return ret;
}

AsmRet rapi_host_fileman_write_file(RapiHostFileman* thiz, unsigned int* last_error, unsigned int* return_value,
	unsigned int handle, unsigned int data_length, void* data,  unsigned int* bytes_written)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ret);

	asm_output_buffer_reset(thiz->output);

	do
	{
		ret = rapi_host_write_fileman_write_file(thiz->output, handle, data_length, data);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_write(thiz->stream, thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_read(thiz->stream, thiz->input);
		if(ret != ASM_RET_OK) break;
		ret = rapi_host_read_fileman_write_file(thiz->input, last_error, return_value, bytes_written);
	}while(0);

	return ret;
}

AsmRet rapi_host_fileman_seek(RapiHostFileman* thiz, unsigned int* last_error, unsigned int* return_value,
	unsigned int handle, unsigned int low, unsigned int has_high, unsigned int high, unsigned int mode, unsigned int* ret_high)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ret);

	asm_output_buffer_reset(thiz->output);

	do
	{
		ret = rapi_host_write_fileman_seek(thiz->output, handle, low, has_high, high, mode);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_write(thiz->stream, thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_read(thiz->stream, thiz->input);
		if(ret != ASM_RET_OK) break;
		ret = rapi_host_read_fileman_seek(thiz->input, last_error, return_value, ret_high);
	}while(0);

	return ret;
}

AsmRet rapi_host_fileman_seek_to_end(RapiHostFileman* thiz, unsigned int* last_error, unsigned int* return_value,
	unsigned int handle )
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ret);

	asm_output_buffer_reset(thiz->output);

	do
	{
		ret = rapi_host_write_fileman_seek_to_end(thiz->output, handle);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_write(thiz->stream, thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_read(thiz->stream, thiz->input);
		if(ret != ASM_RET_OK) break;
		ret = rapi_host_read_fileman_seek_to_end(thiz->input, last_error, return_value);
	}while(0);

	return ret;
}

AsmRet rapi_host_fileman_get_file_time(RapiHostFileman* thiz, unsigned int* last_error, unsigned int* return_value,
	unsigned int handle, RapiFileTime** create_time, RapiFileTime** last_access_time, RapiFileTime** last_write_time)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ret);

	asm_output_buffer_reset(thiz->output);

	do
	{
		ret = rapi_host_write_fileman_get_file_time(thiz->output, handle);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_write(thiz->stream, thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_read(thiz->stream, thiz->input);
		if(ret != ASM_RET_OK) break;
		ret = rapi_host_read_fileman_get_file_time(thiz->input, last_error, return_value, create_time, last_access_time, last_write_time);
	}while(0);

	return ret;
}

AsmRet rapi_host_fileman_set_file_time(RapiHostFileman* thiz, unsigned int* last_error, unsigned int* return_value,
	unsigned int handle, RapiFileTime* create_time, RapiFileTime* last_access_time, RapiFileTime* last_write_time )
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ret);

	asm_output_buffer_reset(thiz->output);

	do
	{
		ret = rapi_host_write_fileman_set_file_time(thiz->output, handle, create_time, last_access_time, last_write_time);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_write(thiz->stream, thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_read(thiz->stream, thiz->input);
		if(ret != ASM_RET_OK) break;
		ret = rapi_host_read_fileman_set_file_time(thiz->input, last_error, return_value);
	}while(0);

	return ret;
}

AsmRet rapi_host_fileman_copy_file(RapiHostFileman* thiz, unsigned int* last_error, unsigned int* return_value,
	WStr* from, WStr* to, unsigned int overwrite )
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ret);

	asm_output_buffer_reset(thiz->output);

	do
	{
		ret = rapi_host_write_fileman_copy_file(thiz->output, from, to, overwrite);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_write(thiz->stream, thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_read(thiz->stream, thiz->input);
		if(ret != ASM_RET_OK) break;
		ret = rapi_host_read_fileman_copy_file(thiz->input, last_error, return_value);
	}while(0);

	return ret;
}

AsmRet rapi_host_fileman_create_directory(RapiHostFileman* thiz, unsigned int* last_error, unsigned int* return_value,
	WStr* path )
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ret);

	asm_output_buffer_reset(thiz->output);

	do
	{
		ret = rapi_host_write_fileman_create_directory(thiz->output, path);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_write(thiz->stream, thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_read(thiz->stream, thiz->input);
		if(ret != ASM_RET_OK) break;
		ret = rapi_host_read_fileman_create_directory(thiz->input, last_error, return_value);
	}while(0);

	return ret;
}

AsmRet rapi_host_fileman_delete_file(RapiHostFileman* thiz, unsigned int* last_error, unsigned int* return_value,
	WStr* file )
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ret);

	asm_output_buffer_reset(thiz->output);

	do
	{
		ret = rapi_host_write_fileman_delete_file(thiz->output, file);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_write(thiz->stream, thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_read(thiz->stream, thiz->input);
		if(ret != ASM_RET_OK) break;
		ret = rapi_host_read_fileman_delete_file(thiz->input, last_error, return_value);
	}while(0);

	return ret;
}

AsmRet rapi_host_fileman_remove_directory(RapiHostFileman* thiz, unsigned int* last_error, unsigned int* return_value,
	WStr* path )
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ret);

	asm_output_buffer_reset(thiz->output);

	do
	{
		ret = rapi_host_write_fileman_remove_directory(thiz->output, path);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_write(thiz->stream, thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_read(thiz->stream, thiz->input);
		if(ret != ASM_RET_OK) break;
		ret = rapi_host_read_fileman_remove_directory(thiz->input, last_error, return_value);
	}while(0);

	return ret;
}

AsmRet rapi_host_fileman_move_file(RapiHostFileman* thiz, unsigned int* last_error, unsigned int* return_value,
	WStr* from, WStr* to )
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ret);

	asm_output_buffer_reset(thiz->output);

	do
	{
		ret = rapi_host_write_fileman_move_file(thiz->output, from, to);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_write(thiz->stream, thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_read(thiz->stream, thiz->input);
		if(ret != ASM_RET_OK) break;
		ret = rapi_host_read_fileman_move_file(thiz->input, last_error, return_value);
	}while(0);

	return ret;
}

AsmRet rapi_host_fileman_get_special_folder(RapiHostFileman* thiz, unsigned int* last_error, unsigned int* return_value,
	unsigned int folder, unsigned int buffer_length, WStr** ret_folder)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ret);

	asm_output_buffer_reset(thiz->output);

	do
	{
		ret = rapi_host_write_fileman_get_special_folder(thiz->output, folder, buffer_length);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_write(thiz->stream, thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_read(thiz->stream, thiz->input);
		if(ret != ASM_RET_OK) break;
		ret = rapi_host_read_fileman_get_special_folder(thiz->input, last_error, return_value, ret_folder);
	}while(0);

	return ret;
}

AsmRet rapi_host_fileman_close_handle(RapiHostFileman* thiz, unsigned int* last_error, unsigned int* return_value,
	unsigned int handle )
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ret);

	asm_output_buffer_reset(thiz->output);

	do
	{
		ret = rapi_host_write_fileman_close_handle(thiz->output, handle);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_write(thiz->stream, thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_read(thiz->stream, thiz->input);
		if(ret != ASM_RET_OK) break;
		ret = rapi_host_read_fileman_close_handle(thiz->input, last_error, return_value);
	}while(0);

	return ret;
}

AsmRet rapi_host_fileman_get_size(RapiHostFileman* thiz, unsigned int* last_error, unsigned int* return_value,
	unsigned int handle )
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ret);

	asm_output_buffer_reset(thiz->output);

	do
	{
		ret = rapi_host_write_fileman_get_size(thiz->output, handle);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_write(thiz->stream, thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_read(thiz->stream, thiz->input);
		if(ret != ASM_RET_OK) break;
		ret = rapi_host_read_fileman_get_size(thiz->input, last_error, return_value);
	}while(0);

	return ret;
}

AsmRet rapi_host_fileman_find_all_files(RapiHostFileman* thiz, unsigned int* last_error, unsigned int* return_value,
	WStr* path, unsigned int flags, unsigned int* count, RapiFindData** find_data)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ret);

	asm_output_buffer_reset(thiz->output);

	do
	{
		ret = rapi_host_write_fileman_find_all_files(thiz->output, path, flags);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_write(thiz->stream, thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_read(thiz->stream, thiz->input);
		if(ret != ASM_RET_OK) break;
		ret = rapi_host_read_fileman_find_all_files(thiz->input, last_error, return_value, count, find_data);
	}while(0);

	return ret;
}

AsmRet rapi_host_fileman_find_first_file(RapiHostFileman* thiz, unsigned int* last_error, unsigned int* return_value,
	WStr* path, RapiFindData** find_data, unsigned int* handle)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ret);

	asm_output_buffer_reset(thiz->output);

	do
	{
		ret = rapi_host_write_fileman_find_first_file(thiz->output, path);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_write(thiz->stream, thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_read(thiz->stream, thiz->input);
		if(ret != ASM_RET_OK) break;
		ret = rapi_host_read_fileman_find_first_file(thiz->input, last_error, return_value, find_data, handle);
	}while(0);

	return ret;
}

AsmRet rapi_host_fileman_find_next_file(RapiHostFileman* thiz, unsigned int* last_error, unsigned int* return_value,
	unsigned int handle, RapiFindData** find_data)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ret);

	asm_output_buffer_reset(thiz->output);

	do
	{
		ret = rapi_host_write_fileman_find_next_file(thiz->output, handle);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_write(thiz->stream, thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_read(thiz->stream, thiz->input);
		if(ret != ASM_RET_OK) break;
		ret = rapi_host_read_fileman_find_next_file(thiz->input, last_error, return_value, find_data);
	}while(0);

	return ret;
}

AsmRet rapi_host_fileman_find_close(RapiHostFileman* thiz, unsigned int* last_error, unsigned int* return_value,
	unsigned int* handle )
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL, ret);

	asm_output_buffer_reset(thiz->output);

	do
	{
		ret = rapi_host_write_fileman_find_close(thiz->output, handle);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_write(thiz->stream, thiz->output);
		if(ret != ASM_RET_OK) break;
		ret = rapi_stream_read(thiz->stream, thiz->input);
		if(ret != ASM_RET_OK) break;
		ret = rapi_host_read_fileman_find_close(thiz->input, last_error, return_value);
	}while(0);

	return ret;
}

void rapi_host_fileman_destroy(RapiHostFileman* thiz)
{
	asm_input_buffer_destroy(thiz->input);
	asm_output_buffer_destroy(thiz->output);
	ASM_FREE(thiz);

	return;
}

