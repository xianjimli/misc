/*
 * File:    rapi_host_fileman_write.c
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

#include <rapi_host_fileman_write.h>


AsmRet rapi_host_write_fileman_create_file(AsmOutputBuffer* output,
	WStr* file_name, unsigned int access_flags, unsigned int share_mode, unsigned int creation_disposition, unsigned int flags_and_attributes, unsigned int template_file)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, RAPI_COMMAND_FILEMAN_CREATE_FILE);
		ret = asm_output_buffer_host_write_wstr(output, file_name);
		ret = asm_output_buffer_write_uint32(output, access_flags);
		ret = asm_output_buffer_write_uint32(output, share_mode);
		ret = asm_output_buffer_write_uint32(output, creation_disposition);
		ret = asm_output_buffer_write_uint32(output, flags_and_attributes);
		ret = asm_output_buffer_write_uint32(output, template_file);

	return ret;
}

AsmRet rapi_host_write_fileman_read_file(AsmOutputBuffer* output,
	unsigned int handle, unsigned int length)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, RAPI_COMMAND_FILEMAN_READ_FILE);
		ret = asm_output_buffer_write_uint32(output, handle);
		ret = asm_output_buffer_write_uint32(output, length);

	return ret;
}

AsmRet rapi_host_write_fileman_write_file(AsmOutputBuffer* output,
	unsigned int handle, unsigned int data_length, void* data)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, RAPI_COMMAND_FILEMAN_WRITE_FILE);
		ret = asm_output_buffer_write_uint32(output, handle);
		ret = asm_output_buffer_write_uint32(output, data_length);
		ret = asm_output_buffer_write_data(output, data, data_length);

	return ret;
}

AsmRet rapi_host_write_fileman_seek(AsmOutputBuffer* output,
	unsigned int handle, unsigned int low, unsigned int has_high, unsigned int high, unsigned int mode)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, RAPI_COMMAND_FILEMAN_SEEK);
		ret = asm_output_buffer_write_uint32(output, handle);
		ret = asm_output_buffer_write_uint32(output, low);
		ret = asm_output_buffer_write_uint32(output, has_high);
		ret = asm_output_buffer_write_uint32(output, high);
		ret = asm_output_buffer_write_uint32(output, mode);

	return ret;
}

AsmRet rapi_host_write_fileman_seek_to_end(AsmOutputBuffer* output,
	unsigned int handle)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, RAPI_COMMAND_FILEMAN_SEEK_TO_END);
		ret = asm_output_buffer_write_uint32(output, handle);

	return ret;
}

AsmRet rapi_host_write_fileman_get_file_time(AsmOutputBuffer* output,
	unsigned int handle)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, RAPI_COMMAND_FILEMAN_GET_FILE_TIME);
		ret = asm_output_buffer_write_uint32(output, handle);

	return ret;
}

AsmRet rapi_host_write_fileman_set_file_time(AsmOutputBuffer* output,
	unsigned int handle, RapiFileTime* create_time, RapiFileTime* last_access_time, RapiFileTime* last_write_time)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, RAPI_COMMAND_FILEMAN_SET_FILE_TIME);
		ret = asm_output_buffer_write_uint32(output, handle);
		ret = asm_output_buffer_write_data(output, create_time, sizeof(*create_time));
		ret = asm_output_buffer_write_data(output, last_access_time, sizeof(*last_access_time));
		ret = asm_output_buffer_write_data(output, last_write_time, sizeof(*last_write_time));

	return ret;
}

AsmRet rapi_host_write_fileman_copy_file(AsmOutputBuffer* output,
	WStr* from, WStr* to, unsigned int overwrite)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, RAPI_COMMAND_FILEMAN_COPY_FILE);
		ret = asm_output_buffer_host_write_wstr(output, from);
		ret = asm_output_buffer_host_write_wstr(output, to);
		ret = asm_output_buffer_write_uint32(output, overwrite);

	return ret;
}

AsmRet rapi_host_write_fileman_create_directory(AsmOutputBuffer* output,
	WStr* path)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, RAPI_COMMAND_FILEMAN_CREATE_DIRECTORY);
		ret = asm_output_buffer_host_write_wstr(output, path);

	return ret;
}

AsmRet rapi_host_write_fileman_delete_file(AsmOutputBuffer* output,
	WStr* file)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, RAPI_COMMAND_FILEMAN_DELETE_FILE);
		ret = asm_output_buffer_host_write_wstr(output, file);

	return ret;
}

AsmRet rapi_host_write_fileman_remove_directory(AsmOutputBuffer* output,
	WStr* path)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, RAPI_COMMAND_FILEMAN_REMOVE_DIRECTORY);
		ret = asm_output_buffer_host_write_wstr(output, path);

	return ret;
}

AsmRet rapi_host_write_fileman_move_file(AsmOutputBuffer* output,
	WStr* from, WStr* to)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, RAPI_COMMAND_FILEMAN_MOVE_FILE);
		ret = asm_output_buffer_host_write_wstr(output, from);
		ret = asm_output_buffer_host_write_wstr(output, to);

	return ret;
}

AsmRet rapi_host_write_fileman_get_special_folder(AsmOutputBuffer* output,
	unsigned int folder, unsigned int buffer_length)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, RAPI_COMMAND_FILEMAN_GET_SPECIAL_FOLDER);
		ret = asm_output_buffer_write_uint32(output, folder);
		ret = asm_output_buffer_write_uint32(output, buffer_length);

	return ret;
}

AsmRet rapi_host_write_fileman_close_handle(AsmOutputBuffer* output,
	unsigned int handle)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, RAPI_COMMAND_FILEMAN_CLOSE_HANDLE);
		ret = asm_output_buffer_write_uint32(output, handle);

	return ret;
}

AsmRet rapi_host_write_fileman_get_size(AsmOutputBuffer* output,
	unsigned int handle)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, RAPI_COMMAND_FILEMAN_GET_SIZE);
		ret = asm_output_buffer_write_uint32(output, handle);

	return ret;
}

AsmRet rapi_host_write_fileman_find_all_files(AsmOutputBuffer* output,
	WStr* path, unsigned int flags)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, RAPI_COMMAND_FILEMAN_FIND_ALL_FILES);
		ret = asm_output_buffer_host_write_wstr(output, path);
		ret = asm_output_buffer_write_uint32(output, flags);

	return ret;
}

AsmRet rapi_host_write_fileman_find_first_file(AsmOutputBuffer* output,
	WStr* path)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, RAPI_COMMAND_FILEMAN_FIND_FIRST_FILE);
		ret = asm_output_buffer_host_write_wstr(output, path);

	return ret;
}

AsmRet rapi_host_write_fileman_find_next_file(AsmOutputBuffer* output,
	unsigned int handle)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, RAPI_COMMAND_FILEMAN_FIND_NEXT_FILE);
		ret = asm_output_buffer_write_uint32(output, handle);

	return ret;
}

AsmRet rapi_host_write_fileman_find_close(AsmOutputBuffer* output,
	unsigned int handle)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, RAPI_COMMAND_FILEMAN_FIND_CLOSE);
		ret = asm_output_buffer_write_uint32(output, handle);

	return ret;
}


