/*
 * File:    asm-common.h
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
#include <asm-macros.h>

#ifndef ASM_COMMON_H
#define ASM_COMMON_H

int  socket_listen(int port);
int  socket_accept(int sock_no);
int  socket_connect(const char* host, int port);
void socket_close(int sock_no);
int  socket_recv_length(int sock_no, void* buffer, size_t length); 
int  socket_from_same_client(int sock_no1, int sock_no2);

unsigned int   uint32_to_endian(unsigned int value, AsmEndian endian);
unsigned short uint16_to_endian(unsigned short value, AsmEndian endian);

unsigned int   uint32_from_endian(unsigned int value, AsmEndian endian);
unsigned short uint16_from_endian(unsigned short value, AsmEndian endian);

int    asm_dir_exist(const char* path);
int    asm_file_length(const char* file_name);
AsmRet asm_read_file(const char* file_name, char** content, size_t* length);
AsmRet asm_write_file(const char* file_name, const char* content, size_t length);
int    asm_is_file_open(const char* file_name);

#endif/*ASM_COMMON_H*/

