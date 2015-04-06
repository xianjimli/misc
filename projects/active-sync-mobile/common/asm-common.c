/*
 * File:    asm-common.c
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

#include <netdb.h>
#include <sys/types.h>
#include <bits/socket.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdio.h>
#include <netinet/in.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "asm-common.h"

int socket_accept(int sock_no)
{
	struct sockaddr_in cli_addr = {0};
	socklen_t cli_addr_len = sizeof(cli_addr);

	int new_sock_no = accept(sock_no, (struct sockaddr *) &cli_addr, &cli_addr_len);

	return new_sock_no;
}

int socket_listen(int port)
{
	struct sockaddr_in serv_addr = {0};
	int sock_no = socket(AF_INET, SOCK_STREAM, 0);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);

	int sock_opt = 1;
	if (setsockopt(sock_no, SOL_SOCKET, SO_REUSEADDR, (void*)&sock_opt, sizeof(sock_opt) ) < 0)
	{
		close(sock_no);

		return -1;
	}
	
	if (bind(sock_no, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
		close(sock_no);
		sock_no = -1;

		printf("%s: bind failed. port=%d\n", __func__, port);
	}
	else
	{
		if(listen(sock_no, 10) < 0)
		{
			printf("%s: listening on %d failed. errno=%d\n", __func__, port, errno);
		}
		else
		{
			printf("%s: listening on %d %d\n", __func__, port, sock_no);
		}
	}

	return sock_no;
}

int socket_connect(const char* host, int port)
{
	int sock_no = 0;
	struct sockaddr_in serv_addr ={0};
	struct hostent* server = NULL;

	sock_no = socket(AF_INET, SOCK_STREAM, 0);
	server = gethostbyname(host);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	memcpy((char*)(&serv_addr.sin_addr.s_addr), (char*)server->h_addr, (size_t)server->h_length);

	if(connect(sock_no, (const struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
	{
		close(sock_no);
		sock_no = -1;
	}

	return sock_no;
}

void socket_close(int sock_no)
{
	close(sock_no);

	return;
}

int socket_recv_length(int sock_no, void* buffer, size_t length)
{
	int ret = 0;
	size_t offset = 0;
	size_t bytes_left = 0;
	asm_return_val_if_fail(ASM_IS_SOCKET_VALID(sock_no) && buffer != NULL && length != 0, ASM_RET_FAIL);
	
	bytes_left = length;
	do
	{
		
		ret = recv(sock_no, buffer+offset, bytes_left, 0);
		if(ret >= 0)
		{
			bytes_left -= ret;
			offset += ret;
		}
	}while(ret > 0 && bytes_left > 0);

	return (length - bytes_left);
}

int  socket_is_from_same_client(int sock_no1, int sock_no2)
{
	asm_return_val_if_fail(ASM_IS_SOCKET_VALID(sock_no1) && ASM_IS_SOCKET_VALID(sock_no2), 0);

	int ret = 0;
	struct sockaddr name1 = {0};
	socklen_t namelen1 = 0;
	if(getpeername(sock_no1, &name1, &namelen1) != 0)
	{
		return 0;
	}

	struct sockaddr name2 = {0};
	socklen_t namelen2 = 0;
	if(getpeername(sock_no2, &name2, &namelen2) != 0)
	{
		return 0;
	}

	if(namelen1 != namelen2)
	{
		return 0;
	}

	if(memcmp(&name1, &name2, namelen1) == 0)
	{
		return 1;
	}

	return 0;
}

unsigned int   uint32_to_endian(unsigned int value, AsmEndian endian)
{
	/*TODO*/
	return value;
}

unsigned short uint16_to_endian(unsigned short value, AsmEndian endian)
{
	/*TODO*/
	return value;
}

unsigned int   uint32_from_endian(unsigned int value, AsmEndian endian)
{
	/*TODO*/
	return value;
}

unsigned short uint16_from_endian(unsigned short value, AsmEndian endian)
{
	/*TODO*/
	return value;
}

int    asm_dir_exist(const char* path)
{
	struct stat st = {0};
	asm_return_val_if_fail(path != NULL, 0);

	if(stat(path, &st) == 0)
	{
		return S_ISDIR(st.st_mode);	
	}
	
	return 0;
}

int asm_file_length(const char* file_name)
{
	struct stat st = {0};
	asm_return_val_if_fail(file_name != NULL, -1);

	if(stat(file_name, &st) == 0)
	{
		return st.st_size;
	}
	else
	{
		return -1;
	}
}

AsmRet asm_read_file(const char* file_name, char** content, size_t* length)
{
	FILE* fp = NULL;
	int file_length = 0;
	char* data = NULL;
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(file_name != NULL && content != NULL && length != NULL, ASM_RET_FAIL);

	*content = NULL;
	do
	{
		if((fp = fopen(file_name, "rb")) == NULL) break;
		if((file_length = asm_file_length(file_name)) <= 0) break;
		if((data = (char*)malloc(file_length + 1)) == NULL) break;

		fread(data, file_length, 1, fp);

		*content = data;
		*length = file_length;
		data = NULL;
	}while(0);

	ASM_FREE(data);
	if(fp != NULL)
	{
		fclose(fp);
	}

	return *content != NULL ? ASM_RET_OK : ASM_RET_FAIL;
}

AsmRet asm_write_file(const char* file_name, const char* content, size_t length)
{
	FILE* fp = NULL;
	AsmRet ret = ASM_RET_FAIL;
	asm_return_val_if_fail(file_name != NULL && content != NULL, ASM_RET_FAIL);

	do
	{
		if((fp = fopen(file_name, "wb+")) == NULL) break;
		fwrite(content, length, 1, fp);
		fflush(fp);
		ret = ASM_RET_OK;
	}while(0);

	if(fp != NULL)
	{
		fclose(fp);
	}

	return ret;
}

int    asm_is_file_open(const char* file_name)
{

	return 1;
}

#ifdef ASM_COMMON_TEST
#include <stdio.h>

static void autotest_socket(void)
{
	int sock_no = socket_connect("localhost", 80);

	printf("%s: socket_connect %d\n", __func__, sock_no);
	if(sock_no >= 0)
	{
		close(sock_no);
	}

	return;
}

static void autotest_file(void)
{
	size_t length = 0;
	char content[100] = {1, 0};
	char* out = NULL;
	const char* file_name = "_test_file";

	assert(asm_write_file(file_name, content, sizeof(content)) == ASM_RET_OK);
	assert(asm_file_length(file_name) == sizeof(content));
	assert(asm_read_file(file_name, &out, &length) == ASM_RET_OK);
	assert(memcmp(out, content, length) == 0);
	assert(length == sizeof(content));

	assert(asm_dir_exist("./"));
	assert(!asm_dir_exist("asdfadfag23"));
	mkdir("testdir", 0777);
	assert(asm_dir_exist("testdir"));
	rmdir("testdir");
	assert(!asm_dir_exist("testdir"));

	return;
}

int main(int argc, char* argv[])
{
	autotest_socket();
	autotest_file();

	return 0;
}
#endif/*ASM_COMMON_TEST*/
