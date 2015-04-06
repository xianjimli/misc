/*
 * File:    type.h
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

#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>

#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>

#define PRINTF printf
#define close_socket(fd) close(fd)
#define log_expr(p) PRINTF("%s(%d): "#p" failed.\n", __FILE__, __LINE__);
#define return_if_fail(p)  if(!(p)) { log_expr(p); return;}
#define return_val_if_fail(p, ret); if(!(p)) { log_expr(p); return (ret);}

typedef enum _Result
{
	RESULT_NONE,
	RESULT_OK,
	RESULT_FAIL,
	RESULT_NR
}Result;

#endif/*TYPEDEF_H*/

