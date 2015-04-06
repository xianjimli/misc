/*
 * File:    buffer_test.c
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

#include <asm-macros.h>
#include <asm-output-buffer.h>
#include <asm-input-buffer.h>

int main(int argc, char* argv[])
{
	unsigned int data_w[10] = {0,1,2,3,4,5,6,7,8,9};
	unsigned int data_r[10] = {0};
	unsigned int u32 = 0;
	unsigned int u16 = 0;
	WStr* wstr_w = wstr_dup_from_ascii("test");
	WStr* wstr_r = NULL;

	AsmOutputBuffer* output = asm_output_buffer_create(1024, ASM_ENDIAN_LITTLE);
	AsmOutputBuffer* input = asm_input_buffer_create(asm_output_buffer_get_buffer(output),
		1024, ASM_ENDIAN_LITTLE, NULL);
	assert(asm_output_buffer_write_data(output, data_w, sizeof(data_w)) == ASM_RET_OK);
	assert(asm_input_buffer_read_data(input, data_r, sizeof(data_r)) == ASM_RET_OK);
	assert(memcmp(data_r, data_w, sizeof(data_w)) == 0);

	assert(asm_output_buffer_write_uint32(output, 0x11223344) == ASM_RET_OK);
	assert(asm_input_buffer_read_uint32(input, &u32) == ASM_RET_OK && u32 == 0x11223344);

	assert(asm_output_buffer_write_uint16(output, 0x1122) == ASM_RET_OK);
	assert(asm_input_buffer_read_uint16(input, &u16) == ASM_RET_OK && u16 == 0x1122);

	assert(asm_output_buffer_write_optional(output, data_w, sizeof(data_w), 1) == ASM_RET_OK);
	assert(asm_input_buffer_read_optional(input, data_r, sizeof(data_r)) == ASM_RET_OK);
	assert(memcmp(data_r, data_w, sizeof(data_w)) == 0);
	
	assert(asm_output_buffer_write_optional(output, data_w, sizeof(data_w), 0) == ASM_RET_OK);
	assert(asm_input_buffer_read_optional(input, data_r, sizeof(data_r)) == ASM_RET_OK);

	assert(asm_output_buffer_write_optional(output, NULL, sizeof(data_w), 0) == ASM_RET_OK);
	assert(asm_input_buffer_read_optional(input, data_r, sizeof(data_r)) == ASM_RET_OK);

	assert(asm_output_buffer_device_write_wstr(output, wstr_w) == ASM_RET_OK);
	assert(asm_input_buffer_host_read_wstr_dup(input, &wstr_r) == ASM_RET_OK);
	assert(wstr_compare(wstr_w, wstr_r) == 0);
	ASM_FREE(wstr_r);

	assert(asm_output_buffer_host_write_wstr(output, wstr_w) == ASM_RET_OK);
	assert(asm_input_buffer_device_read_wstr_dup(input, &wstr_r) == ASM_RET_OK);
	assert(wstr_compare(wstr_w, wstr_r) == 0);
	ASM_FREE(wstr_r);

	asm_output_buffer_destroy(output);
	asm_input_buffer_destroy(input);

	return 0;
}
