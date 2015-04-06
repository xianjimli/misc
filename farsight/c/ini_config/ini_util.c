/*
 * File:    ini_util.c
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   some util functions.
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

#include <ctype.h>
#include "ini_util.h"

const char* strtrim(char* str)
{
	char* p = NULL;
	return_val_if_fail(str != NULL && *str != '\0', str);

	p = str + strlen(str) - 1;

	while(p != str && isspace(*p)) 
	{
		*p = '\0';
		p--;
	}

	p = str;
	while(*p != '\0' && isspace(*p)) p++;

	if(p != str)
	{
		char* s = p;
		char* d = str;
		while(*s != '\0')
		{
			*d = *s;
			d++;
			s++;
		}
		*d = '\0';
	}

	return str;
}

#ifdef INI_UTIL_TEST
#include <assert.h>
int main(int argc, char* argv[])
{
	char str[128] = {0};
	strcpy(str, "  aaa");
	assert(strcmp(strtrim(str), "aaa") == 0);
	
	strcpy(str, "  aaa   ");
	assert(strcmp(strtrim(str), "aaa") == 0);
	
	strcpy(str, "aaa");
	assert(strcmp(strtrim(str), "aaa") == 0);
	
	strcpy(str, "aaa   ");
	assert(strcmp(strtrim(str), "aaa") == 0);

	return 0;
}
#endif/*INI_UTIL_TEST*/
