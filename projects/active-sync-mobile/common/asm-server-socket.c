/*
 * File:    asm-server-socket.c
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
#include <asm-server-socket.h>
#include <asm-stream-socket.h>

typedef struct _PrivInfo
{
	char* ip;
	int port;

	int sock_no;
}PrivInfo;

static AsmRet asm_server_socket_accept(AsmServer* thiz,  AsmStream** stream)
{
	AsmRet  ret = ASM_RET_FAIL;
	asm_return_val_if_fail(thiz != NULL && stream != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	
	int new_sock_no = socket_accept(priv->sock_no);
	
	if(ASM_IS_SOCKET_VALID(new_sock_no))
	{
		*stream = asm_stream_socket_create(new_sock_no);
		ret = ASM_RET_OK;
	}

	return ret;
}

static int asm_server_socket_get_fd(AsmServer* thiz )
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	return priv->sock_no;
}

void asm_server_socket_destroy(AsmServer* thiz)
{
	if(thiz != NULL)
	{
		PrivInfo* priv = (PrivInfo*)thiz->priv;
		
		close(priv->sock_no);
		ASM_FREE(priv->ip);
		ASM_FREE(thiz);
	}

	return;
}

AsmServer* asm_server_socket_create(const char* ip, int port)
{
	int sock_no = socket_listen(port);
	asm_return_val_if_fail(ASM_IS_SOCKET_VALID(sock_no), NULL);

	AsmServer* thiz = (AsmServer*)ASM_ALLOC(AsmServer, sizeof(PrivInfo));
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	if(ip != NULL)
	{
		priv->ip = strdup(ip);
	}

	priv->port = port;
	priv->sock_no = sock_no;

	thiz->accept = asm_server_socket_accept;
	thiz->get_fd = asm_server_socket_get_fd;
	thiz->destroy = asm_server_socket_destroy;

	return thiz;
}

#ifdef SERVER_SOCKET_TEST 
int main(int argc, char* argv[])
{
	AsmStream* stream = NULL;
	AsmServer* server = asm_server_socket_create(NULL, 2000);
	while(asm_server_accept(server, &stream) == ASM_RET_OK)
	{
		printf("%s:%d socket=%d\n", __func__, __LINE__, asm_stream_get_fd(stream));
		asm_stream_destroy(stream);
	}
	asm_server_destroy(server);

	return 1;
}

#endif/*SERVER_SOCKET_TEST*/
