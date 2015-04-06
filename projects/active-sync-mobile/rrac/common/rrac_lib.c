/*
 * File:    rrac_lib.c
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
#include <rrac_lib.h>

AsmRet rrac_read_command(AsmStream* stream, RracCommandHeader** ret_command)
{
	int length = 0;
	RracCommandHeader cmd = {0};
	AsmRet ret = ASM_RET_FAIL;

	asm_return_val_if_fail(stream != NULL && ret_command != NULL, ASM_RET_FAIL);

	*ret_command = NULL;

	ret = asm_stream_read(stream, &cmd, sizeof(cmd), &length); 
	printf("%s:%d length=%d ret=%d\n", __func__, __LINE__, length, ret);

	if(length == 0)
	{
		ret = ASM_RET_EOF;
	}
	else if(length < 0)
	{
		ret = ASM_RET_INVALID_FD;
	}
	else if(length == sizeof(cmd));
	{
		ret = ASM_RET_OK;
	}

	RracCommandHeader* command = NULL;

	if(ret == ASM_RET_OK)
	{
		cmd.command = uint16_from_endian(cmd.command, ASM_ENDIAN_LITTLE);
		cmd.length = uint16_from_endian(cmd.length, ASM_ENDIAN_LITTLE);

		command = ASM_ALLOC(RracCommandHeader, cmd.length);
		command->command = cmd.command;
		command->length  = cmd.length;

		asm_stream_read(stream, command->data, command->length, &length);
	}

	if(length == 0)
	{
		ret = ASM_RET_EOF;
	}
	else if(length < 0)
	{
		ret = ASM_RET_INVALID_FD;
	}
	else if(length != cmd.length)
	{
		ret = ASM_RET_FAIL;
	}
	else
	{
		ret = ASM_RET_OK;
	}

	printf("%s:%d: 0x%02x 0x%02x ret=%d\n", __func__, __LINE__, command->command, command->length, ret);

	if(ret == ASM_RET_OK)
	{
		*ret_command = command;
	}
	else
	{
		if(command != NULL)
		{
			free(command);
		}
	}

	return ret;
}

AsmRet rrac_write_command(AsmStream* stream, const RracCommandHeader* command)
{
	int length = 0;
	AsmRet ret = ASM_RET_FAIL;

	asm_return_val_if_fail(stream != NULL && command != NULL, ret);
	if((asm_stream_write(stream, (void*)command, sizeof(RracCommandHeader), &length)) == ASM_RET_OK 
		&& length == sizeof(RracCommandHeader))
	{
		if((asm_stream_write(stream, (void*)command->data, command->length, &length)) == ASM_RET_OK 
			&& length == command->length)
		{
			ret = ASM_RET_OK;
		}
	}
	
	printf("%s:%d: 0x%02x 0x%02x ret=%d\n", __func__, __LINE__, command->command, command->length, ret);

	return ret;
}

AsmRet rrac_read_object(AsmStream* stream,  RracObject** ret_object)
{
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(stream != NULL && ret_object != NULL, ret);

	char*  data = NULL;
	int    length = 0;
	size_t aligned_length = 0;
	size_t total_length = 0;
	size_t chunk_nr = 0;
	RracObjectHeader header = {0};
	RracChunkHeader chunk_header = {0};

	do
	{
		if((asm_stream_read(stream, &header, sizeof(header), &length)) != ASM_RET_OK)
		{
			break;
		}
		header.id = ASM_FROM_LE16(header.id); 
		header.type = ASM_FROM_LE16(header.type); 
		header.flags = ASM_FROM_LE16(header.flags); 

		if(header.id == RRAC_END_OF_OBJECT)
		{
			printf("%s:%d: end of object.\n", __func__, __LINE__);
			ret = ASM_RET_EOF;
			break;
		}

		do
		{
			ret = ASM_RET_FAIL;
			asm_stream_read(stream, &chunk_header, sizeof(chunk_header), &length);
			if(length != sizeof(chunk_header)) break;

			chunk_header.length = ASM_FROM_LE16(chunk_header.length);
			chunk_header.stuff = ASM_FROM_LE16(chunk_header.stuff);
			aligned_length = (chunk_header.length + 3) & ~3;

			printf("%s:%d: (%d) chunk_header.stuff=%p %d\n", __func__, __LINE__, 
				chunk_nr, chunk_header.stuff, chunk_header.length);
			chunk_nr++;

			data = realloc(data, total_length + aligned_length);

			asm_stream_read(stream, data + total_length, aligned_length, &length);
			if(length != aligned_length) break;

			total_length += chunk_header.length;

			ret = ASM_RET_OK;
		}while(!(chunk_header.stuff & 0x8000));
		
	}while(0);
		
	if(ret == ASM_RET_OK)
	{
		RracObject* object = (RracObject*)malloc(sizeof(RracObject) + total_length);
		object->id = header.id;
		object->type = header.type;
		object->flags = header.flags;
		object->length = total_length;
		if(total_length > 0)
		{
			memcpy(object->data, data, total_length);
		}
		*ret_object = object;
	
		printf("%s:%d: object type=%d id=%d length=%d \n", 
			__func__, __LINE__, object->type, object->id, object->length);
	}

	if(data != NULL)
	{
		free(data);
		data = NULL;
	}

	return ret;
}

AsmRet rrac_write_object(AsmStream* stream, const RracObject* object)
{
	int length = 0;
	size_t offset = 0;
	size_t bytes_left = 0;
	unsigned short chunk_block_count = 0x0010;
	AsmRet ret = ASM_RET_FAIL;

	asm_return_val_if_fail(stream != NULL && object != NULL, ret);

	RracObjectHeader header = {0};
	RracChunkHeader chunk_header = {0};
	char* data = (char*)object->data;

	printf("%s:%d: object type=%d id=%d length=%d \n", 
		__func__, __LINE__, object->type, object->id, object->length);

	header.id    = ASM_TO_LE32(object->id);
	header.type  = ASM_TO_LE32(object->type);
	header.flags = ASM_TO_LE32(object->flags);
	
	bytes_left = object->length;
	do
	{
		asm_stream_write(stream, &header, sizeof(header), &length);
		if(length != sizeof(header)) break;

		if(header.id == RRAC_END_OF_OBJECT)
		{
			ret = ASM_RET_OK;
			break;	
		}

		while(bytes_left)
		{
			unsigned short stuff = 0xffa0;
			size_t chunk_length = MIN(bytes_left, RRAC_CHUNK_MAX_SIZE);
			size_t aligned_length = (chunk_length + 3) & ~3;

			ret = ASM_RET_FAIL;

			chunk_header.length = ASM_TO_LE32(chunk_length);
			bytes_left -= chunk_length;
			
			if(bytes_left > 0)
			{
				chunk_header.stuff = ASM_TO_LE16(chunk_block_count);
			}
			else
			{
				if (aligned_length > chunk_length)
				{
					stuff |= (aligned_length - chunk_length) << 2;
				}
				chunk_header.stuff = ASM_TO_LE16(stuff);
			}

			if((asm_stream_write(stream, &chunk_header, sizeof(chunk_header), &length)) != ASM_RET_OK) break;
			if((asm_stream_write(stream, data + offset, chunk_length, &length)) != ASM_RET_OK) break;

			if(aligned_length > chunk_length)
			{
				char pad[3] = {0,0,0};
				asm_stream_write(stream, pad, aligned_length - chunk_length, &length);
				if(length != (aligned_length - chunk_length)) break;
			}

			offset += chunk_length;
			chunk_block_count += 0x0010;
			ret = ASM_RET_OK;
		}
	}while(0);

	return ret;
}

