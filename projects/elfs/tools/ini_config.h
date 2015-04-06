/*
 * File:    ini_config.h
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   ini config interface.
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
#ifndef INI_CONFIG_H
#define INI_CONFIG_H

#include "ini_groups.h"

#ifdef __cplusplus
extern "C" {
#endif/*__cplusplus*/

typedef struct _IniConfig
{
	char* file_name;
	IniGroups* groups;
}IniConfig;

IniConfig*  ini_config_create(const char* file_name);
IniRet      ini_config_set(IniConfig* thiz, const char* group, const char* key, const char* value);
const char* ini_config_get(IniConfig* thiz, const char* group, const char* key);
IniRet      ini_config_del(IniConfig* thiz, const char* group, const char* key);
IniRet      ini_config_save(IniConfig* thiz);
void        ini_config_destroy(IniConfig* thiz);

#ifdef __cplusplus
}
#endif/*__cplusplus*/
#endif/*INI_CONFIG_H*/

