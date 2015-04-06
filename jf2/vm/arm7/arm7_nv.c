/*
 * File:    arm7_nv.c
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   
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
 * 2009-1-25 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include <jtype.h>
#include <arm7_nv.h>

static const char* r_names[] = 
{
	"r0",
	"r1",
	"r2",
	"r3",
	"r4",
	"r5",
	"r6",
	"r7",
	"r8",
	"r9",
	"r10",
	"fp",
	"ip",
	"sp",
	"lr",
	"pc"
};

const char*   arm7_r_name(int r)
{
	if(r >= 0 && r < A_SIZE(r_names))
	{
		return r_names[r];
	}

	return NULL;
}

int arm7_r_index(const char* name)
{
	int i = 0;
	j_ret_val_if_fail(name != NULL, -1);

	for(i = 0; i < A_SIZE(r_names); i++)
	{
		if(strcasecmp(r_names[i], name) == 0)
		{
			return i;
		}
	}

	return -1;
}

static const char* cond_names[] =
{
	"eq",
	"ne",
	"cs",
	"cc",
	"mi",
	"pl",
	"vs",
	"vc",
	"hi",
	"ls",
	"ge",
	"lt",
	"gt",
	"le",
	"",/*al*/
	"nv"
};

const char*   arm7_cond_name(int c)
{
	if(c >= 0 && c < A_SIZE(cond_names))
	{
		return cond_names[c];
	}

	return NULL;
}

int arm7_cond_value(const char* name)
{
	int i = 0;
	j_ret_val_if_fail(name != NULL, -1);

	for(i = 0; i < A_SIZE(cond_names); i++)
	{
		if(strcasecmp(cond_names[i], name) == 0)
		{
			return i;
		}
	}

	return -1;
}

static const char* logic_names[] =
{
	"lsl",
	"lsr",
	"asr",
	"ror"
};

const char* arm7_logic_name(int logic)
{
	if(logic >= 0 && logic < A_SIZE(logic_names))
	{
		return logic_names[logic];
	}

	return NULL;
}

int arm7_logic_value(const char* logic)
{
	int i = 0;
	j_ret_val_if_fail(logic != NULL, -1);

	for(i = 0; i < A_SIZE(logic_names); i++)
	{
		if(strcasecmp(logic_names[i], logic) == 0)
		{
			return i;
		}
	}

	return -1;
}

#ifdef ARM7_NV_TEST
int main(int argc, char* argv[])
{
	int i = 0;
	for(i = 0; i < A_SIZE(r_names); i++)
	{
		printf("[%d]: %s\n", i, arm7_r_name(i));
		assert(arm7_r_index(arm7_r_name(i)) == i);
	}

	for(i = 0; i < A_SIZE(cond_names); i++)
	{
		printf("[%d]: %s\n", i, arm7_cond_name(i));
		assert(arm7_cond_value(arm7_cond_name(i)) == i);
	}
	
	return 0;
}
#endif/*ARM7_NV_TEST*/
