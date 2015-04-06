/*
 * File:    asm-input-buffer.h
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

#include <asm-types.h>

#ifndef ASM_INPUT_BUFFER_H
#define ASM_INPUT_BUFFER_H

struct _AsmInputBuffer;
typedef struct _AsmInputBuffer AsmInputBuffer;

AsmInputBuffer* asm_input_buffer_create(char* buffer, size_t length, AsmEndian endian, AsmBufferFreeFunc buffer_free);
AsmRet asm_input_buffer_destroy(AsmInputBuffer* thiz);

size_t asm_input_buffer_get_length(AsmInputBuffer* thiz);
char* asm_input_buffer_get_buffer(AsmInputBuffer* thiz);
size_t asm_input_buffer_tell(AsmInputBuffer* thiz);
AsmRet asm_input_buffer_rewind(AsmInputBuffer* thiz);

AsmEndian asm_input_buffer_get_endian(AsmInputBuffer* thiz);

AsmRet asm_input_buffer_set_buffer(AsmInputBuffer* thiz, char* buffer, size_t length, AsmBufferFreeFunc buffer_free);
AsmRet asm_input_buffer_read_data(AsmInputBuffer* thiz, void* value, size_t length);
AsmRet asm_input_buffer_read_uint16(AsmInputBuffer* thiz, unsigned short* value);
AsmRet asm_input_buffer_read_uint32(AsmInputBuffer* thiz, unsigned int* value);
AsmRet asm_input_buffer_read_wstr(AsmInputBuffer* thiz, unsigned short* wstr, size_t* length);
AsmRet asm_input_buffer_device_read_wstr_dup(AsmInputBuffer* thiz, unsigned short** wstr);
AsmRet asm_input_buffer_device_read_wstr_dup(AsmInputBuffer* thiz, unsigned short** wstr);

AsmRet asm_input_buffer_read_optional(AsmInputBuffer* thiz, void* value, size_t length);
AsmRet asm_input_buffer_read_unint32_optional(AsmInputBuffer* thiz, unsigned int* value);

#endif/*ASM_INPUT_BUFFER_H*/

