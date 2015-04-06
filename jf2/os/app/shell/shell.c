/*
 * File:   shell.c 
 * Author: Li XianJing <xianjimli@hotmail.com>
 * Brief:  shell main
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

#include <stdio.h>
extern void test_all(void);

void shell_main(void)
{
	int i = 0;
	char str[12];
	jmemset(str, 'a', 11);
	str[11] = '\0';

//	jitoa_test();
//	return 0;
	test_all();

	return;
	while(1)
	{
		i++;
		jprintf("aaa:%d\n", __func__, __LINE__);
	}

	return;
}

