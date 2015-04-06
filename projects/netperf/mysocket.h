/*
 * File:    mysocket.h
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

#ifndef MYSOCKET_H
#define MYSOCKET_H

#include "typedef.h"

struct _Socket;
typedef struct _Socket Socket;

Socket* socket_create(void);
void       socket_destroy(Socket* thiz);

int        socket_get_fd(Socket* thiz);
Result  socket_connect(Socket* thiz, const char* host, int port);
int        socket_recv(Socket* thiz, void *buffer, size_t length);
int        socket_send(Socket* thiz, void *buffer, size_t length);
Result  socket_disconnect(Socket* thiz);
Result  socket_wait_for_data(Socket* thiz, size_t useconds);

#endif/*MYSOCKET_H*/
