/*
 * File:    rapi_lib.c
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

#include <rapi_lib.h>

AsmRet rapi_socket_write(int sock_no, AsmOutputBuffer* output)
{
	AsmRet ret = ASM_RET_FAIL;

	assert(sock_no >= 0 && output != NULL);

	if(sock_no >= 0 && output != NULL)
	{
		int send_length = 0;
		unsigned int length = uint32_to_endian(asm_output_buffer_get_length(output), ASM_ENDIAN_LITTLE);
		send_length = send(sock_no, &length, sizeof(length), 0);
		assert(send_length == sizeof(length));

		send_length = send(sock_no, asm_output_buffer_get_buffer(output), asm_output_buffer_get_length(output), 0);
		assert(send_length == asm_output_buffer_get_length(output));

		ret = ASM_RET_OK;
	}

	return ret;
}

AsmRet rapi_stream_read(AsmStream* stream, AsmInputBuffer* input)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(stream != NULL && input != NULL, ret);

	char* buffer = NULL;
	unsigned int length = 0;
	unsigned int recv_length = 0;

	do
	{
		ret = asm_stream_read(stream, &length, sizeof(length), &recv_length);
		if(recv_length == 0)
		{
			ret = ASM_RET_INVALID_FD;
			printf("%s: socket %d is closed.\n", __func__, asm_stream_get_fd(stream));		
			break;
		}
		asm_break_if_fail(recv_length == sizeof(length));

		length = uint32_from_endian(length, ASM_ENDIAN_LITTLE);
		if(length > asm_input_buffer_get_length(input))
		{
			buffer = (char*)malloc(length);
			asm_input_buffer_set_buffer(input, buffer, length, free);
		}
		else
		{
			buffer = asm_input_buffer_get_buffer(input);
			asm_input_buffer_rewind(input);
		}

		ret = asm_stream_read(stream, buffer, length, &recv_length);
	
	}while(0);

	return ret;
}

AsmRet rapi_stream_write(AsmStream* stream, AsmOutputBuffer* output)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(stream != NULL && output != NULL, ret);

	do
	{
		int send_length = 0;
		unsigned int length = ASM_TO_LE32(asm_output_buffer_get_length(output));
		
		ret = asm_stream_write(stream, &length, sizeof(length), &send_length);
		asm_break_if_fail(ret == ASM_RET_OK);

		ret = asm_stream_write(stream, asm_output_buffer_get_buffer(output), 
			asm_output_buffer_get_length(output), &send_length);
	}while(0);

	return ret;
}

