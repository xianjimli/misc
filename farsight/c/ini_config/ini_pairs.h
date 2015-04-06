/*
 * File:    ini_pairs.h
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   ini pairs manager
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
#ifndef INI_PAIRS_H
#define INI_PAIRS_H

#include "ini_type.h"

#ifdef __cplusplus
extern "C" {
#endif/*__cplusplus*/

typedef struct _IniPair
{
	struct _IniPair* next;
	char* key;
	char* value;
}IniPair;

typedef struct _IniPairs
{
	IniPair* first_pair;	
}IniPairs;

IniPairs*  ini_pairs_create(void);
size_t     ini_pairs_size(IniPairs* thiz);
IniRet     ini_pairs_del(IniPairs* thiz, const char* key);
IniPair*   ini_pairs_find(IniPairs* thiz, const char* key);
IniRet     ini_pairs_append(IniPairs* thiz, const char* key, const char* value);
IniRet     ini_pairs_save(IniPairs* thiz, FILE* fp, char delim_char);
void       ini_pairs_destroy(IniPairs* thiz);

#ifdef __cplusplus
}
#endif/*__cplusplus*/

#endif/*INI_PAIRS_H*/

