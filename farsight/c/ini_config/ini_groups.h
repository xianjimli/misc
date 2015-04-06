/*
 * File:    ini_groups.h
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   ini groups manager.
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

#ifndef INI_GROUPS_H
#define INI_GROUPS_H

#include "ini_pairs.h"

#ifdef __cplusplus
extern "C" {
#endif/*__cplusplus*/

typedef struct _IniGroup
{
	char* name;
	struct _IniGroup* next;

	IniPairs* pairs;
}IniGroup;

typedef struct _IniGroups
{
	IniGroup* first_group;
}IniGroups;

IniGroups* ini_groups_create(void);
int        ini_groups_size(IniGroups* thiz);
IniRet     ini_groups_del(IniGroups* thiz, const char* group_name);
IniGroup*  ini_groups_find(IniGroups* thiz, const char* group_name);
IniRet     ini_groups_append(IniGroups* thiz, const char* group_name);
IniRet     ini_groups_save(IniGroups* thiz, FILE* fp, char delim_char);
void       ini_groups_destroy(IniGroups* thiz);

#ifdef __cplusplus
}
#endif/*__cplusplus*/

#endif/*INI_GROUPS_H*/

