/*
 * File:    mysocket.c
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   
 *
 * Copyright (c) 2009 Li XianJing
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
 * 2006-12-13 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "mysocket.h"


#define		SOCKET_ONCE_WRITE_BYTES	2048

struct _Socket
{
	int socket;
	struct sockaddr_in addr;
};

Socket* socket_create(void)
{
	Socket* thiz = (Socket*)calloc(1, sizeof(Socket));

	if(thiz != NULL)
	{
		thiz->socket = -1;
	}
	
	return thiz;
}

void       socket_destroy(Socket* thiz)
{
	if(thiz != NULL)
	{
		if(thiz->socket >= 0)
		{
			close_socket(thiz->socket);
			thiz->socket = -1;
		}

		free(thiz);

		return;
	}
}

int        socket_get_fd(Socket* thiz)
{
	return_val_if_fail(thiz != NULL, -1)

	return thiz->socket;
}

Result  socket_connect(Socket* thiz, const char* host, int port)
{
	struct hostent* hostent_ptr = NULL;

	return_val_if_fail(thiz != NULL && host != NULL && thiz->socket < 0, RESULT_FAIL);

	hostent_ptr = gethostbyname(host);
	return_val_if_fail(hostent_ptr != NULL, RESULT_FAIL);

	thiz->addr.sin_family = PF_INET;
	thiz->addr.sin_port = htons((unsigned short)port);
	thiz->addr.sin_addr.s_addr = *(unsigned long*)(hostent_ptr->h_addr_list[0]);

	thiz->socket = socket(PF_INET, SOCK_STREAM, 0);	
	
	if(connect(thiz->socket, (struct sockaddr*)&(thiz->addr), sizeof(thiz->addr)) == 0)
	{
		return RESULT_OK;
	}
	else
	{
		perror("connect");
		return RESULT_FAIL;
	}
}

int socket_recv(Socket* thiz, void *buffer, size_t length)
{
	return_val_if_fail(thiz != NULL && buffer != NULL && thiz->socket >= 0, 0);

	return recv(thiz->socket, buffer, length, 0);
}

int socket_send(Socket* thiz, void *buffer, size_t length)
{
	int ret = 0;
	fd_set fdset = {0};
	struct timeval atime = {0};

	return_val_if_fail(thiz != NULL && buffer != NULL && thiz->socket >= 0, 0);	

	atime.tv_sec = 60;
	while (ret < length)
	{
		FD_ZERO(&fdset);
		FD_SET(thiz->socket, &fdset);
    	if(select(thiz->socket + 1, NULL, &fdset, NULL, &atime) > 0 && FD_ISSET(thiz->socket, &fdset))
    	{
			int once_send = ((length - ret) > SOCKET_ONCE_WRITE_BYTES) ? SOCKET_ONCE_WRITE_BYTES : (length - ret);
			
			if ((once_send = send(thiz->socket, buffer + ret, once_send, 0)) == 0)
			{
				break;
			}
			ret += once_send;
    	}
		else
		{
			break;
		}
	}

	return ret;
}

Result  socket_disconnect(Socket* thiz)
{
	return_val_if_fail(thiz != NULL && thiz->socket >= 0, RESULT_FAIL);

	if(thiz->socket >= 0)
	{
		close_socket(thiz->socket);
		thiz->socket = -1;
	}

	return RESULT_OK;
}

Result socket_wait_for_data(Socket* thiz, size_t useconds)
{
	fd_set fdset = {0};
	struct timeval atime = {0};
	return_val_if_fail(thiz != NULL && thiz->socket >= 0, RESULT_FAIL);	

	atime.tv_sec = useconds/1000;
	atime.tv_usec = useconds%1000;

	FD_ZERO(&fdset);
	FD_SET(thiz->socket, &fdset);

    if(select(thiz->socket + 1, &fdset, NULL, NULL, &atime) > 0 && FD_ISSET(thiz->socket, &fdset))
    {
	    return RESULT_OK;
    }
    else
    {
        perror("select");
	    return RESULT_FAIL;
	}
}


#ifdef SOCKET_TEST
int main(int argc, char* argv[])
{
	int i = 0;
	int n = 3;
	char request[2048] = {0};
	char response[2048] = {0};
	Socket* thiz = socket_create();

	snprintf(request, 2000, "HEAD %s HTTP/1.0\r\n\r\n", argc > 1 ? argv[1] : "/");

	if(thiz != NULL)
	{
		for(i = 0; i < n; i++)
		{
			socket_connect(thiz, "localhost", 80);
			assert(socket_send(thiz, request, strlen(request)) > 0);
			assert(socket_wait_for_data(thiz, 3000) > 0);
			assert(socket_recv(thiz, (void*)response, 2000) > 0);
			socket_disconnect(thiz);
		}	

		printf("response:\n%s", response);
	}

	socket_destroy(thiz);

	return 0;
}
#endif/*SOCKET_TEST*/

