/*
 * File:    asm-wstr.c
 * Author:  Li XianJing <lixianjing@broncho.org>
 * Brief:   
 *
 * Copyright (c) 2008 topwise, Inc.
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
 * 2008-01-28 Li XianJing <lixianjing@topwisesz.com> created
 *
 */

#include <string.h>
#include <asm-types.h>
#include <asm-wstr.h>

size_t wstr_length(const WStr* str)
{
	size_t length = 0;
	if(str == NULL || str[0] == 0)
	{
		return 0;
	}

	for(length = 0; str[length] != 0; length++);

	return length;
}

int    wstr_compare(const WStr* str1, const WStr* str2)
{
	int i = 0;
	if(str1 == NULL) return -1;
	if(str2 == NULL) return 1;

	while(str1[i] && str2[i])
	{
		if(str1[i] != str2[i])
		{
			return str1[i] - str2[i];
		}

		i++;
	}

	return 0;
}

WStr* wstr_from_ascii(WStr* str, const char* ascii, size_t chas_nr)
{
	size_t i = 0;
	asm_return_val_if_fail(str != NULL && ascii != NULL, 0);

	for(i = 0; i < chas_nr; i++)
	{
		str[i] = ascii[i];
	}
	str[i] = 0;

	return str;
}

WStr*  wstr_dup(WStr* str)
{
	asm_return_val_if_fail(str != NULL, NULL);
	size_t length = (wstr_length(str) + 1 )* sizeof(WStr);
	WStr* new_str = (WStr*)malloc(length);
	if(new_str != NULL)
	{
		memcpy(new_str, str, length);
	}

	return new_str;
}

WStr*  wstr_dup_from_ascii(const char* ascii)
{
	asm_return_val_if_fail(ascii != NULL, NULL);
	size_t length = strlen(ascii);
	WStr* str = (WStr*)malloc((length + 1) * sizeof(WStr));
	
	return wstr_from_ascii(str, ascii, length);
}

char*  wstr_to_ascii(WStr* str)
{
	asm_return_val_if_fail(str != NULL, NULL);
	size_t i = 0;
	size_t length = wstr_length(str);
	char* ascii = (char*)malloc(length + 1);

	for(i = 0; i < length; i++)
	{
		ascii[i] = (char)str[i];
	}
	ascii[i] = '\0';

	return ascii;
}

#ifdef ASM_WSTR_TEST
#include <assert.h>
void autotest_wstr_length()
{
	size_t i = 0;
	WStr str[100] = {0};

	assert(wstr_length(NULL) == 0);
	assert(wstr_length(str) == 0);
	for(i = 0; i < (sizeof(str)/sizeof(str[0]) - 1); i++)
	{
		str[i] = 'a';
		assert(wstr_length(str) == (i + 1));
	}

	return;
}

void autotest_wstr_from_ascii()
{
	WStr str[100] = {0};
	WStr str1[100] = {0};
	wstr_from_ascii(str, "", 0);
	assert(str[0] == '\0');

	wstr_from_ascii(str, "a", 1);
	assert(str[0] == 'a' && str[1] == '\0');

	wstr_from_ascii(str, "ab", 2);
	assert(str[0] == 'a' && str[1] == 'b' && str[2] == '\0');

	wstr_from_ascii(str, "ab", 2);
	wstr_from_ascii(str1, "ab", 2);
	assert(wstr_compare(NULL, str1) < 0);
	assert(wstr_compare(str, NULL) > 0);
	assert(wstr_compare(str, str1) == 0);


	return;
}

int main(int argc, char* argv[])
{
	autotest_wstr_length();

	return 0;
}
#endif/*ASM_WSTR_TEST*/
