/*
 * File:    http_util.c
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

#include "http_util.h"

string string_trim(string& s, const string& drop)
{
	s.erase(s.find_last_not_of(drop)+1);
	return s.erase(0,s.find_first_not_of(drop));
}

#ifdef HTTP_UTIL_TEST
#include <assert.h>
int main(int argc, char* argv[])
{
	string str = " aaa ";
	assert(string_trim(str) == "aaa" && str == "aaa");
	str = "\taaa\r\n";
	assert(string_trim(str) == "aaa" && str == "aaa");
	str = "\t    aaa\r\n";
	assert(string_trim(str) == "aaa" && str == "aaa");
	str = "aaa";
	assert(string_trim(str) == "aaa" && str == "aaa");

	return 0;
}
#endif/*HTTP_UTIL_TEST*/
