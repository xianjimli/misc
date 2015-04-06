/*
 * File:    httpclient.c 
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   a http speed tester 
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
 * 2009-10-17 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#define _GNU_SOURCE
#include <string.h>
#include <sys/time.h>
#include "mysocket.h"

typedef struct _NetStat
{
	int send_bytes;
	int recv_bytes;
	int cost_msec;
}NetStat;

void* run_one_test(const char* host, int port, const char* file)
{
	int ret = 0;
	char buffer[32000] = {0};
	NetStat net_stat = {0};
	Socket* s = socket_create();
	socket_connect(s, host, port); 
	struct timeval tv_begin = {0};
	struct timeval tv_end = {0};

	snprintf(buffer, sizeof(buffer), 
		"GET %s HTTP/1.1\r\nHost: %s\r\nAccept:*/*\r\nConnection: close\r\n\r\n",
		file, host);

	gettimeofday(&tv_begin, NULL);
	net_stat.send_bytes = socket_send(s, buffer, strlen(buffer));
	while((ret =  socket_recv(s, buffer, sizeof(buffer))) > 0)
	{
		net_stat.recv_bytes += ret;
	}
	gettimeofday(&tv_end, NULL);
	socket_destroy(s);
	net_stat.cost_msec = (tv_end.tv_sec - tv_begin.tv_sec) * 1000 + (tv_end.tv_usec - tv_begin.tv_usec)/1000;
	
	printf("send=%d recv=%d cost=%d recv-speed=%d(bytes/ms)\n", 
		net_stat.send_bytes, 
		net_stat.recv_bytes,
		net_stat.cost_msec,
		net_stat.recv_bytes/net_stat.cost_msec);

	return NULL;
}

typedef struct _ThreadParam
{
	char* host;
	int port;
	char* file;
}ThreadParam;

#include <pthread.h>
#define THREAD_NR 10

void* thread_entry(void* param)
{
	ThreadParam* p = param;
	return run_one_test(p->host, p->port, p->file);
}

void parse_url(const char* url, char** host, char** path)
{
	const char* h = strstr(url, "://");

	if(h != NULL)
	{
		h += 3;
	}
	else
	{
		h = url;
	}

	const char* p = strrchr(h, '/');
	if(p != NULL)
	{
		*path = strdup(p);
	}
	else
	{
		*path = strdup("/");
	}

	*host = strndup(h, (size_t)(p - h));

	printf("host=%s path=%s\n", *host, *path);

	return;
}

int main(int argc, char* argv[])
{
	int i = 0;
	int nr = 0;
	char* host = NULL;
	char* path = NULL;
	pthread_t tid[THREAD_NR] = {0};
	ThreadParam param = {.port=80};

	if(argc != 3)
	{
		printf("usage: %s thread_nr url\n", argv[0]);

		return 0;
	}
	
	nr = atoi(argv[1]);
	parse_url(argv[2], &host, &path);

	param.host = host;
	param.file = path;

	for(i = 0; i < nr; i++)
	{
		pthread_create(tid+i, NULL, &thread_entry, &param);
	}

	for(i = 0; i < nr; i++)
	{
		pthread_join(tid[i], NULL);
	}

	return 0;
}

