/*
 * File:    asm-output-buffer.c
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
#include <asm-macros.h>
#include <asm-output-buffer.h>

#define TRANS_NR 32

struct _AsmOutputBuffer
{
	char* buffer;
	size_t buffer_length;
	size_t buffer_total_length;

	size_t trans[TRANS_NR];
	size_t trans_index;
	AsmEndian endian;
};

AsmOutputBuffer* asm_output_buffer_create(size_t init_size, AsmEndian endian)
{
	AsmOutputBuffer* thiz = ASM_ALLOC(AsmOutputBuffer, 0);

	thiz->buffer_total_length = init_size;
	thiz->endian = endian;

	if(init_size != 0)
	{
		thiz->buffer = malloc(init_size);
	}

	return thiz;
}

AsmRet  asm_output_buffer_destroy(AsmOutputBuffer* thiz)
{
	if(thiz != NULL)
	{
		free(thiz->buffer);

		free(thiz);
	}

	return ASM_RET_OK;
}

size_t asm_output_buffer_get_length(AsmOutputBuffer* thiz)
{
	assert(thiz != NULL);

	return thiz != NULL ? thiz->buffer_length : 0;
}

void*  asm_output_buffer_get_buffer(AsmOutputBuffer* thiz)
{
	assert(thiz != NULL);

	return thiz != NULL ? thiz->buffer : NULL;
}

static AsmRet asm_output_buffer_extend(AsmOutputBuffer* thiz, size_t mini_size)
{
	AsmRet ret = ASM_RET_FAIL;

	assert(thiz != NULL);

	if(thiz == NULL)
	{
		return ret;
	}

	if((thiz->buffer_length + mini_size) >= thiz->buffer_total_length)
	{
		size_t length = thiz->buffer_length * 1.5 + mini_size;
		void*  buffer = realloc(thiz->buffer, length);
		if(buffer != NULL)
		{
			thiz->buffer = buffer;
			thiz->buffer_length = length;
			ret = ASM_RET_OK;
		}
	}
	else
	{
		ret = ASM_RET_OK;
	}

	return ret;
}

AsmRet asm_output_buffer_write_data(AsmOutputBuffer* thiz, void* value, size_t length)
{
	AsmRet ret = ASM_RET_FAIL;

	assert(thiz != NULL && value != NULL);

	if(asm_output_buffer_extend(thiz, length) == ASM_RET_OK && value != NULL)
	{
		memcpy(thiz->buffer + thiz->buffer_length, value, length);
		thiz->buffer_length += length;
		ret = ASM_RET_OK;
	}

	return ret;
}

AsmRet asm_output_buffer_write_uint32(AsmOutputBuffer* thiz, unsigned int value)
{
	value = uint32_to_endian(value, thiz->endian);

	return asm_output_buffer_write_data(thiz, &value, sizeof(value));
}

AsmRet asm_output_buffer_write_uint16(AsmOutputBuffer* thiz, unsigned short value)
{
	value = uint16_to_endian(value, thiz->endian);

	return asm_output_buffer_write_data(thiz, &value, sizeof(value));
}

AsmRet asm_output_buffer_host_write_wstr(AsmOutputBuffer* thiz, const unsigned short* value)
{
	if(value != NULL)
	{
		size_t length = (wstr_length(value) + 1) * sizeof(value[0]);

		asm_output_buffer_write_uint32(thiz, length);
		return asm_output_buffer_write_data(thiz, (void*)value, length);
	}
	else
	{
		return asm_output_buffer_write_uint32(thiz, 0);
	}
}

AsmRet asm_output_buffer_device_write_wstr(AsmOutputBuffer* thiz, const unsigned short* value)
{
	if(value != NULL)
	{
		size_t length = (wstr_length(value) + 1) * sizeof(value[0]);

		asm_output_buffer_write_uint32(thiz, wstr_length(value));
		return asm_output_buffer_write_data(thiz, (void*)value, length);
	}
	else
	{
		return asm_output_buffer_write_uint32(thiz, 0);
	}
}

AsmRet asm_output_buffer_write_wstr_optional(AsmOutputBuffer* thiz, const unsigned short* value)
{
	size_t length = value != NULL ? (wstr_length(value) + 1) * sizeof(value[0]) : 0;

	return asm_output_buffer_write_optional(thiz, (void*)value, length, 1);
}

AsmRet asm_output_buffer_write_uint32_optional(AsmOutputBuffer* thiz, unsigned int value, int with_data)
{
	value = uint32_to_endian(value, thiz->endian);
	
	return asm_output_buffer_write_optional(thiz, &value, sizeof(value), with_data);
}

AsmRet  asm_output_buffer_reset(AsmOutputBuffer* thiz)
{
	AsmRet ret = ASM_RET_FAIL;

	assert(thiz != NULL);
	if(thiz != NULL)
	{
		thiz->buffer_length = 0;
		ret= ASM_RET_OK;
	}

	return ret;
}

AsmRet asm_output_buffer_write_optional(AsmOutputBuffer* thiz, void* value, size_t length, int with_data)
{
	if(value != NULL)
	{
		asm_output_buffer_write_uint32(thiz, 1);
		asm_output_buffer_write_uint32(thiz, length);
		if(with_data != 0)
		{
			asm_output_buffer_write_uint32(thiz, 1);
			return asm_output_buffer_write_data(thiz, value, length);
		}
		else
		{
			return asm_output_buffer_write_uint32(thiz, 0);
		}
	}
	else
	{
		return asm_output_buffer_write_uint32(thiz, 0);	
	}
}

AsmRet asm_output_buffer_write_optional_in(AsmOutputBuffer* thiz, void* value, size_t length)
{
	if(value != NULL)
	{
		asm_output_buffer_write_uint32(thiz, 1);
		asm_output_buffer_write_uint32(thiz, length);
		return asm_output_buffer_write_data(thiz, value, length);
	}
	else
	{
		return asm_output_buffer_write_uint32(thiz, 0);	
	}
}

AsmRet asm_output_buffer_write_optional_out(AsmOutputBuffer* thiz, void* value, size_t length)
{
	if(value != NULL)
	{
		asm_output_buffer_write_uint32(thiz, 1);
		asm_output_buffer_write_uint32(thiz, length);
		return asm_output_buffer_write_uint32(thiz, 0);
	}
	else
	{
		return asm_output_buffer_write_uint32(thiz, 0);	
	}
}

AsmRet asm_output_buffer_write_optional_in_out(AsmOutputBuffer* thiz, void* value, size_t length)
{
	if(value != NULL)
	{
		asm_output_buffer_write_uint32(thiz, 1);
		asm_output_buffer_write_uint32(thiz, length);
		asm_output_buffer_write_uint32(thiz, 1);
		return asm_output_buffer_write_data(thiz, value, length);
	}
	else
	{
		return asm_output_buffer_write_uint32(thiz, 0);	
	}
}

AsmRet asm_output_buffer_write_optional_no_size(AsmOutputBuffer* thiz, void* value, size_t length)
{
	if(value != NULL)
	{
		asm_output_buffer_write_uint32(thiz, 1);
		return asm_output_buffer_write_data(thiz, value, length);
	}
	else
	{
		return asm_output_buffer_write_uint32(thiz, 0);	
	}
}


#ifdef ASM_OUTPUT_BUFFER_TEST

void asm_output_buffer_test(AsmOutputBuffer* thiz)
{
	WStr str[100] = {0};
	size_t length = 0;

	memset(str, 'a', sizeof(str) - 2);
	assert(asm_output_buffer_reset(thiz) == ASM_RET_OK);
	assert(asm_output_buffer_get_length(thiz) == length);
	assert(asm_output_buffer_write_uint32(thiz, 100) == ASM_RET_OK);
	length += sizeof(unsigned int);
	assert(asm_output_buffer_get_length(thiz) == length);
	
	assert(asm_output_buffer_write_uint16(thiz, 100) == ASM_RET_OK);
	length += sizeof(unsigned short);
	assert(asm_output_buffer_get_length(thiz) == length);

	assert(asm_output_buffer_device_write_wstr(thiz, str) == ASM_RET_OK);
	length += sizeof(str) + sizeof(unsigned int);
	assert(asm_output_buffer_get_length(thiz) == length);

	assert(asm_output_buffer_write_wstr_optional(thiz, str) == ASM_RET_OK);
	length += sizeof(str) + 3 * sizeof(unsigned int);
	assert(asm_output_buffer_get_length(thiz) == length);

	assert(asm_output_buffer_write_optional(thiz, &length, sizeof(length), 1) == ASM_RET_OK);
	length += 4 * sizeof(unsigned int);
	assert(asm_output_buffer_get_length(thiz) == length);
	
	assert(asm_output_buffer_write_optional(thiz, &length, sizeof(length), 0) == ASM_RET_OK);
	length += 3 * sizeof(unsigned int);
	assert(asm_output_buffer_get_length(thiz) == length);
	
	assert(asm_output_buffer_write_optional(thiz, NULL, sizeof(length), 0) == ASM_RET_OK);
	length += sizeof(unsigned int);
	assert(asm_output_buffer_get_length(thiz) == length);

	assert(asm_output_buffer_write_optional_in(thiz, &length, sizeof(length)) == ASM_RET_OK);
	length += 3 * sizeof(unsigned int);
	assert(asm_output_buffer_get_length(thiz) == length);
	
	assert(asm_output_buffer_write_optional_in(thiz, NULL, sizeof(length)) == ASM_RET_OK);
	length += sizeof(unsigned int);
	assert(asm_output_buffer_get_length(thiz) == length);

	assert(asm_output_buffer_write_optional_out(thiz, &length, sizeof(length)) == ASM_RET_OK);
	length += 3 * sizeof(unsigned int);
	assert(asm_output_buffer_get_length(thiz) == length);
	
	assert(asm_output_buffer_write_optional_out(thiz, NULL, sizeof(length)) == ASM_RET_OK);
	length += sizeof(unsigned int);
	assert(asm_output_buffer_get_length(thiz) == length);

	assert(asm_output_buffer_write_optional_in_out(thiz, &length, sizeof(length)) == ASM_RET_OK);
	length += 4 * sizeof(unsigned int);
	assert(asm_output_buffer_get_length(thiz) == length);
	
	assert(asm_output_buffer_write_optional_in_out(thiz, NULL, sizeof(length)) == ASM_RET_OK);
	length += sizeof(unsigned int);
	assert(asm_output_buffer_get_length(thiz) == length);

	assert(asm_output_buffer_write_optional_no_size(thiz, &length, sizeof(length)) == ASM_RET_OK);
	length += 2 * sizeof(unsigned int);
	assert(asm_output_buffer_get_length(thiz) == length);
	
	assert(asm_output_buffer_write_optional_no_size(thiz, NULL, sizeof(length)) == ASM_RET_OK);
	length += sizeof(unsigned int);
	assert(asm_output_buffer_get_length(thiz) == length);

	return;
}

int main(int argc, char* argv[])
{
	AsmOutputBuffer* thiz = asm_output_buffer_create(1024, ASM_ENDIAN_LITTLE);

	asm_output_buffer_test(thiz);
	asm_output_buffer_test(thiz);

	asm_output_buffer_destroy(thiz);

	return 0;
}
#endif/*ASM_OUTPUT_BUFFER_TEST*/
