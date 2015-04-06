/*
 * File:    rapi_device_fileman_write.c
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

#include <rapi_device_fileman_write.h>


AsmRet rapi_device_write_fileman_create_file(
	AsmOutputBuffer* output, unsigned int last_error, unsigned int return_value)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, last_error);
	ret = asm_output_buffer_write_uint32(output, return_value);

	return ret;
}

AsmRet rapi_device_write_fileman_read_file(
	AsmOutputBuffer* output, unsigned int last_error, unsigned int return_value,
	unsigned int ret_data_length, void* ret_data)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, last_error);
	ret = asm_output_buffer_write_uint32(output, return_value);
		ret = asm_output_buffer_write_uint32(output, ret_data_length);
		ret = asm_output_buffer_write_data(output, ret_data, ret_data_length);

	return ret;
}

AsmRet rapi_device_write_fileman_write_file(
	AsmOutputBuffer* output, unsigned int last_error, unsigned int return_value,
	 unsigned int bytes_written)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, last_error);
	ret = asm_output_buffer_write_uint32(output, return_value);
		ret = asm_output_buffer_write_uint32(output, bytes_written);

	return ret;
}

AsmRet rapi_device_write_fileman_seek(
	AsmOutputBuffer* output, unsigned int last_error, unsigned int return_value,
	unsigned int ret_high)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, last_error);
	ret = asm_output_buffer_write_uint32(output, return_value);
		ret = asm_output_buffer_write_uint32(output, ret_high);

	return ret;
}

AsmRet rapi_device_write_fileman_seek_to_end(
	AsmOutputBuffer* output, unsigned int last_error, unsigned int return_value)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, last_error);
	ret = asm_output_buffer_write_uint32(output, return_value);

	return ret;
}

AsmRet rapi_device_write_fileman_get_file_time(
	AsmOutputBuffer* output, unsigned int last_error, unsigned int return_value,
	RapiFileTime* create_time, RapiFileTime* last_access_time, RapiFileTime* last_write_time)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, last_error);
	ret = asm_output_buffer_write_uint32(output, return_value);
		ret = asm_output_buffer_write_data(output, create_time, sizeof(*create_time));
		ret = asm_output_buffer_write_data(output, last_access_time, sizeof(*last_access_time));
		ret = asm_output_buffer_write_data(output, last_write_time, sizeof(*last_write_time));

	return ret;
}

AsmRet rapi_device_write_fileman_set_file_time(
	AsmOutputBuffer* output, unsigned int last_error, unsigned int return_value)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, last_error);
	ret = asm_output_buffer_write_uint32(output, return_value);

	return ret;
}

AsmRet rapi_device_write_fileman_copy_file(
	AsmOutputBuffer* output, unsigned int last_error, unsigned int return_value)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, last_error);
	ret = asm_output_buffer_write_uint32(output, return_value);

	return ret;
}

AsmRet rapi_device_write_fileman_create_directory(
	AsmOutputBuffer* output, unsigned int last_error, unsigned int return_value)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, last_error);
	ret = asm_output_buffer_write_uint32(output, return_value);

	return ret;
}

AsmRet rapi_device_write_fileman_delete_file(
	AsmOutputBuffer* output, unsigned int last_error, unsigned int return_value)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, last_error);
	ret = asm_output_buffer_write_uint32(output, return_value);

	return ret;
}

AsmRet rapi_device_write_fileman_remove_directory(
	AsmOutputBuffer* output, unsigned int last_error, unsigned int return_value)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, last_error);
	ret = asm_output_buffer_write_uint32(output, return_value);

	return ret;
}

AsmRet rapi_device_write_fileman_move_file(
	AsmOutputBuffer* output, unsigned int last_error, unsigned int return_value)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, last_error);
	ret = asm_output_buffer_write_uint32(output, return_value);

	return ret;
}

AsmRet rapi_device_write_fileman_get_special_folder(
	AsmOutputBuffer* output, unsigned int last_error, unsigned int return_value,
	WStr* ret_folder)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, last_error);
	//ret = asm_output_buffer_write_uint32(output, return_value);/*XXX: skip*/
		ret = asm_output_buffer_device_write_wstr(output, ret_folder);

	return ret;
}

AsmRet rapi_device_write_fileman_close_handle(
	AsmOutputBuffer* output, unsigned int last_error, unsigned int return_value)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, last_error);
	ret = asm_output_buffer_write_uint32(output, return_value);

	return ret;
}

AsmRet rapi_device_write_fileman_get_size(
	AsmOutputBuffer* output, unsigned int last_error, unsigned int return_value)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, last_error);
	ret = asm_output_buffer_write_uint32(output, return_value);

	return ret;
}

AsmRet rapi_device_write_fileman_find_all_files(
	AsmOutputBuffer* output, unsigned int last_error, unsigned int return_value,
	unsigned int count, RapiFindData* find_data)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, last_error);
	ret = asm_output_buffer_write_uint32(output, return_value);
		ret = asm_output_buffer_write_uint32(output, count);
		ret = asm_output_buffer_write_data(output, find_data, sizeof(*find_data));

	return ret;
}

AsmRet rapi_device_write_fileman_find_first_file(
	AsmOutputBuffer* output, unsigned int last_error, unsigned int return_value,
	RapiFindData* find_data, unsigned int handle)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, last_error);
	ret = asm_output_buffer_write_uint32(output, return_value);
		ret = asm_output_buffer_write_data(output, find_data, sizeof(*find_data));
		ret = asm_output_buffer_write_uint32(output, handle);

	return ret;
}

AsmRet rapi_device_write_fileman_find_next_file(
	AsmOutputBuffer* output, unsigned int last_error, unsigned int return_value,
	RapiFindData* find_data)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, last_error);
	ret = asm_output_buffer_write_uint32(output, return_value);
		ret = asm_output_buffer_write_data(output, find_data, sizeof(*find_data));

	return ret;
}

AsmRet rapi_device_write_fileman_find_close(
	AsmOutputBuffer* output, unsigned int last_error, unsigned int return_value)
{	
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(output != NULL, ret);

	ret = asm_output_buffer_write_uint32(output, last_error);
	ret = asm_output_buffer_write_uint32(output, return_value);

	return ret;
}


