/*
 * File:    elfs-merge.c
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   a tool to merge ini config file for elfs.
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
 * 2009-05-29 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include <ini_config.h>

static void merge_one(IniConfig* ini, IniConfig* other);

int main(int argc, char* argv[])
{
	int i = 0;
	IniConfig* ini = NULL;
	
	if(argc < 3)
	{
		printf("Usage: %s pkg-config1 pkg-config2 ...\n", argv[0]);

		return 0;
	}

	ini = ini_config_create(argv[1]);
	if(ini != NULL)
	{
		for(i = 2; i < argc; i++)
		{
			IniConfig* other = ini_config_create(argv[i]);
			printf("merging %s ...\n", argv[i]);
			if(other != NULL)
			{
				merge_one(ini, other);
				ini_config_destroy(other);
			}
		}
		ini_config_save(ini);
		ini_config_destroy(ini);
	}

	return 0;
}

static void merge_one(IniConfig* ini, IniConfig* other)
{
	IniGroup* group = NULL;
	
	return_if_fail(ini != NULL && other != NULL && other->groups != NULL);

	for(group = other->groups->first_group; group != NULL; group = group->next)
	{
		IniPair* pair = group->pairs->first_pair;
		for(; pair != NULL; pair = pair->next)
		{
			if(pair->key != NULL && pair->value != NULL)
			{
				ini_config_set(ini, group->name, pair->key, pair->value);
			}
		}
	}

	return;
}

