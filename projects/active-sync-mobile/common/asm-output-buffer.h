/*
 * File:    asm-output-buffer.h
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

#ifndef ASM_OUTPUT_BUFFER_H
#define ASM_OUTPUT_BUFFER_H

struct _AsmOutputBuffer;
typedef struct _AsmOutputBuffer AsmOutputBuffer;

AsmOutputBuffer* asm_output_buffer_create(size_t init_size, AsmEndian endian);

size_t asm_output_buffer_get_length(AsmOutputBuffer* thiz);
void*  asm_output_buffer_get_buffer(AsmOutputBuffer* thiz);

AsmRet  asm_output_buffer_destroy(AsmOutputBuffer* thiz);
AsmRet  asm_output_buffer_reset(AsmOutputBuffer* thiz);

AsmRet asm_output_buffer_write_data(AsmOutputBuffer* thiz, void* value, size_t length);
AsmRet asm_output_buffer_write_uint32(AsmOutputBuffer* thiz, unsigned int value);
AsmRet asm_output_buffer_write_uint16(AsmOutputBuffer* thiz, unsigned short value);
AsmRet asm_output_buffer_device_write_wstr(AsmOutputBuffer* thiz, const unsigned short* value);
AsmRet asm_output_buffer_host_write_wstr(AsmOutputBuffer* thiz, const unsigned short* value);

AsmRet asm_output_buffer_write_optional(AsmOutputBuffer* thiz, void* value, size_t length, int with_data);
AsmRet asm_output_buffer_write_optional_in(AsmOutputBuffer* thiz, void* value, size_t length);
AsmRet asm_output_buffer_write_optional_out(AsmOutputBuffer* thiz, void* value, size_t length);
AsmRet asm_output_buffer_write_optional_in_out(AsmOutputBuffer* thiz, void* value, size_t length);
AsmRet asm_output_buffer_write_optional_no_size(AsmOutputBuffer* thiz, void* value, size_t length);

AsmRet asm_output_buffer_write_wstr_optional(AsmOutputBuffer* thiz, const unsigned short* value);
AsmRet asm_output_buffer_write_uint32_optional(AsmOutputBuffer* thiz, unsigned int value, int with_data);



#endif/*ASM_OUTPUT_BUFFER_H*/
