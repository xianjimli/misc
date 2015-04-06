/*
 * File:   syscall.c 
 * Author: Li XianJing <xianjimli@hotmail.com>
 * Brief:  syscall entry. 
 *
 * Copyright (c) 2009  Li XianJing
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
 * 2009-1-28 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include <syscall.h>

typedef struct _SysCallParam
{
	jword_t r[4];
}SysCallParam;

extern int _syscall(SysCallParam* param);

int syscall(jword_t p1, jword_t p2, jword_t p3, jword_t p4)
{
	SysCallParam param = {0};
	param.r[0] = p1;
	param.r[1] = p2;
	param.r[2] = p3;
	param.r[3] = p4;

	return _syscall(&param);
}

