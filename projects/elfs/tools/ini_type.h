/*
 * File:    ini_type.h
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   common used types and macros.
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
 * 2009-05-06 Li XianJing <xianjimli@hotmail.com> created
 *
 */
#ifndef INI_TYPE_H
#define INI_TYPE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif/*__cplusplus*/

typedef enum _IniRet
{
	INI_RET_OK = 0,
	INI_RET_FAIL,
	INI_RET_OOM,
	INI_RET_NOT_EXIST,
	INI_RET_IO
}IniRet;

#define return_if_fail(p) if(!(p)) \
    {fprintf(stderr, "%s:%d Warning: "#p" failed.\n", \
        __func__, __LINE__); return;}
#define return_val_if_fail(p, ret) if(!(p)) \
    {fprintf(stderr, "%s:%d Warning: "#p" failed.\n",\
    __func__, __LINE__); return (ret);}

#define DEFAULT_GROUP "_ini_default_"
#ifdef __cplusplus
}
#endif/*__cplusplus*/

#endif/*INI_TYPE_H*/

