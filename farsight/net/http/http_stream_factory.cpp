/*
 * File:    http_stream_factory.cpp
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   stream factory.
 *
 * Copyright (c) 2009  Li XianJing <xianjimli@hotmail.com>
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
 * 2009-05-09 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include <netdb.h>
#include <sys/types.h>
#include <bits/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include "http_url.h"
#include "http_socket_stream.h"
#include "http_stream_factory.h"

CHttpStreamFactory::CHttpStreamFactory(void)
{
}

CHttpStreamFactory::~CHttpStreamFactory(void)
{
}

static int socket_connect(const char* host, int port)
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

CHttpStream* CHttpStreamFactory::CreateStream(const string& protocol, const string& host, int port)
{
	CHttpStream* stream = NULL;

	if(protocol == "http")
	{
		int socket = socket_connect(host.c_str(), port);

		if(socket > 0)
		{
			stream = new CHttpSocketStream(socket);
		}
	}
	
	return stream;
}

#ifdef HTTP_STREAM_FACTORY_TEST
#include <assert.h>
int main(int argc, char* argv[])
{
	CHttpStream* s = CHttpStreamFactory::CreateStream("http", "www.limodev.cn", 80);
	assert(s != NULL);
	delete s;

	return 0;
}
#endif/*HTTP_STREAM_FACTORY_TEST*/
