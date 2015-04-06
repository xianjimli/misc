/*
 * File:    asm-input-buffer.c
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
#include <stdio.h>
#include <asm-macros.h>
#include <asm-input-buffer.h>

struct _AsmInputBuffer
{
	char* buffer;
	size_t length;
	size_t offset;
	AsmEndian endian;
	AsmBufferFreeFunc buffer_free;
};

AsmInputBuffer* asm_input_buffer_create(char* buffer, size_t length, AsmEndian endian, AsmBufferFreeFunc buffer_free)
{
	AsmInputBuffer* thiz = ASM_ALLOC(AsmInputBuffer, 0);

	thiz->endian = endian;
	asm_input_buffer_set_buffer(thiz, buffer, length, buffer_free);

	return thiz;
}

AsmRet asm_input_buffer_destroy(AsmInputBuffer* thiz)
{
	if(thiz != NULL)
	{
		if(thiz->buffer_free != NULL && thiz->buffer != NULL)
		{
			thiz->buffer_free(thiz->buffer);
		}
		free(thiz);
	}

	return ASM_RET_OK;
}

size_t asm_input_buffer_get_length(AsmInputBuffer* thiz)
{
	return thiz != NULL ? thiz->length : 0;
}

char* asm_input_buffer_get_buffer(AsmInputBuffer* thiz)
{
	return thiz != NULL ? thiz->buffer : NULL;
}

size_t asm_input_buffer_tell(AsmInputBuffer* thiz)
{
	return thiz != NULL ? thiz->offset : 0;
}

AsmRet asm_input_buffer_rewind(AsmInputBuffer* thiz)
{
	if(thiz != NULL)
	{
		thiz->offset = 0;
	}

	return ASM_RET_OK;
}

AsmEndian asm_input_buffer_get_endian(AsmInputBuffer* thiz)
{
	return thiz != NULL ? thiz->endian : ASM_ENDIAN_LITTLE;
}

AsmRet asm_input_buffer_set_buffer(AsmInputBuffer* thiz, char* buffer, size_t length, AsmBufferFreeFunc buffer_free)
{
	if(thiz != NULL)
	{
		if(thiz->buffer_free != NULL && thiz->buffer != NULL)
		{
			thiz->buffer_free(thiz->buffer);
			thiz->buffer = NULL;
		}

		thiz->buffer = buffer;
		thiz->buffer_free = buffer_free;
		thiz->length = length;
		thiz->offset = 0;
	}

	return ASM_RET_OK;
}

#define IS_DATA_AVAILABE(thiz, size) ((thiz != NULL) && (thiz->buffer != NULL) && ((thiz->offset + size) <= thiz->length))

AsmRet asm_input_buffer_read_data(AsmInputBuffer* thiz, void* value, size_t length)
{
	AsmRet ret = ASM_RET_FAIL;

	assert(IS_DATA_AVAILABE(thiz, length));

	if(value != NULL && IS_DATA_AVAILABE(thiz, length))
	{
		memcpy(value, thiz->buffer + thiz->offset, length);
		thiz->offset += length;

		ret = ASM_RET_OK;
	}

	return ret;	
}

AsmRet asm_input_buffer_read_uint16(AsmInputBuffer* thiz, unsigned short* value)
{
	AsmRet ret = ASM_RET_FAIL;

	if(asm_input_buffer_read_data(thiz, value, sizeof(*value)) == ASM_RET_OK)
	{
		*value = uint16_from_endian(*value, thiz->endian);

		ret = ASM_RET_OK;
	}

	return ret;
}

AsmRet asm_input_buffer_read_uint32(AsmInputBuffer* thiz, unsigned int* value)
{
	AsmRet ret = ASM_RET_FAIL;

	if(asm_input_buffer_read_data(thiz, value, sizeof(*value)) == ASM_RET_OK)
	{
		*value = uint32_from_endian(*value, thiz->endian);

		ret = ASM_RET_OK;
	}

	return ret;
}

AsmRet asm_input_buffer_read_wstr(AsmInputBuffer* thiz, unsigned short* wstr, size_t* length)
{
	size_t real_length = 0;
	if(wstr == NULL || length == NULL 
		|| asm_input_buffer_read_uint32(thiz, &real_length) != ASM_RET_OK 
		|| real_length > *length)
	{
		return ASM_RET_FAIL;
	}
	
	*length = real_length;

	return asm_input_buffer_read_data(thiz, wstr, (real_length + 1) * sizeof(WStr));
}

AsmRet asm_input_buffer_host_read_wstr_dup(AsmInputBuffer* thiz, unsigned short** wstr)
{
	size_t length = 0;
	if(wstr == NULL || asm_input_buffer_read_uint32(thiz, &length) != ASM_RET_OK)
	{
		return ASM_RET_FAIL;
	}

	length =  (length + 1) * sizeof(WStr);
	*wstr = (WStr*)malloc(length);
	return asm_input_buffer_read_data(thiz, *wstr, length);
}

AsmRet asm_input_buffer_device_read_wstr_dup(AsmInputBuffer* thiz, unsigned short** wstr)
{
	size_t length = 0;
	if(wstr == NULL || asm_input_buffer_read_uint32(thiz, &length) != ASM_RET_OK)
	{
		return ASM_RET_FAIL;
	}

	*wstr = (WStr*)malloc(length);
	return asm_input_buffer_read_data(thiz, *wstr, length);
}

AsmRet asm_input_buffer_read_optional(AsmInputBuffer* thiz, void* value, size_t length)
{
	unsigned int with_param = 0;
	
	AsmRet ret = ASM_RET_FAIL;
	ret = asm_input_buffer_read_uint32(thiz, &with_param);
	
	if(with_param == 1)
	{
		unsigned int real_length = 0;
		unsigned int with_data = 0;
		int overflow = 0;
		if(asm_input_buffer_read_uint32(thiz, &real_length) == ASM_RET_OK
			&& asm_input_buffer_read_uint32(thiz, &with_data) == ASM_RET_OK)
		{
			if(with_data == 1)
			{
				if(value != NULL)
				{
					asm_input_buffer_read_data(thiz, value, MIN(length, real_length));
					overflow = real_length - length;
				}
				else
				{
					overflow = real_length;
				}

				if(overflow > 0)
				{
					thiz->offset += overflow;

					printf("%s: overflow = %d\n", __func__, overflow);
				}
			}
			else
			{
				printf("%s: with_data=%d\n", __func__, with_data);	
			}
		}
		else
		{
			printf("%s: read data failed\n", __func__);	
		}
	}
	else
	{
		printf("%s: with_param=%d\n", __func__, with_param);
	}

	return ret;
}

AsmRet asm_input_buffer_read_unint32_optional(AsmInputBuffer* thiz, unsigned int* value)
{
	if(asm_input_buffer_read_optional(thiz, value, sizeof(*value)) == ASM_RET_OK)
	{
		*value = uint32_from_endian(value, thiz->endian);

		return ASM_RET_OK;
	}
	else
	{
		return ASM_RET_FAIL;
	}
}

#ifdef ASM_INPUT_BUFFER_TEST
int main(int argc, char* argv[])
{
	unsigned int   u32 = 0;
	unsigned short u16 = 0;
	WStr wstr[10] = {0};
	size_t length = 10;
	unsigned int buffer[100] = {0x11223344,0x11221122, 2, 0x00400040,0, 1, 4, 1, 0x44332211,0};
	AsmInputBuffer* thiz = asm_input_buffer_create((void*)buffer, sizeof(buffer), ASM_ENDIAN_LITTLE, NULL);

	assert(asm_input_buffer_get_length(thiz) == sizeof(buffer));
	assert(asm_input_buffer_tell(thiz) == 0);
	assert(asm_input_buffer_read_uint32(thiz, &u32) == ASM_RET_OK && u32 == 0x11223344);
	assert(asm_input_buffer_tell(thiz) == 4);
	assert(asm_input_buffer_read_uint16(thiz, &u16) == ASM_RET_OK && u16 == 0x1122);
	assert(asm_input_buffer_tell(thiz) == 6);
	assert(asm_input_buffer_read_uint16(thiz, &u16) == ASM_RET_OK && u16 == 0x1122);
	assert(asm_input_buffer_tell(thiz) == 8);
	assert(asm_input_buffer_read_wstr(thiz, wstr, &length) == ASM_RET_OK);
	assert(asm_input_buffer_read_uint16(thiz, &u16) == ASM_RET_OK && u16 == 0x00);
	assert(asm_input_buffer_tell(thiz) == 20);
	assert(asm_input_buffer_read_optional(thiz, &u32, sizeof(u32)) == ASM_RET_OK && u32 == 0x44332211);
	asm_input_buffer_destroy(thiz);

	return 0;
}
#endif/*ASM_INPUT_BUFFER_TEST*/
