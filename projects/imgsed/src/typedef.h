/*
 * File:    typedef.h
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   
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
 * 2009-07-17 Li XianJing <xianjimli@hotmail.com> created
 *
 */
#ifndef TYPEDEF_H
#define TYPEDEF_H
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

typedef enum _Ret
{
	RET_OK,
	RET_FAIL,
	RET_STOP
}Ret;

typedef struct _ImgExtraInfo
{
	const char* filename;
	struct stat fstat;
}ImgExtraInfo;

#define SET_EXTRA(obj, info) g_object_set_data(G_OBJECT(obj), "extra_info", info)
#define GET_EXTRA(obj) (ImgExtraInfo*)g_object_get_data(G_OBJECT(obj), "extra_info")

#endif/*TYPEDEF_H*/

