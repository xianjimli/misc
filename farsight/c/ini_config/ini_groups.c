/*
 * File:    ini_groups.c
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
#include "ini_util.h"
#include "ini_groups.h"

static void ini_group_destroy(IniGroup* group);

IniGroups* ini_groups_create(void)
{
	return (IniGroups*)calloc(1, sizeof(IniGroups));
}

int        ini_groups_size(IniGroups* thiz)
{
	size_t size = 0;
	IniGroup* iter = NULL;

	return_val_if_fail(thiz != NULL && thiz->first_group != NULL, 0);

	for(iter = thiz->first_group; iter != NULL; iter = iter->next)
	{
		size++;
	}

	return size;
}

IniRet     ini_groups_del(IniGroups* thiz, const char* group_name)
{
	IniGroup* iter = NULL;
	IniGroup* prev = NULL;

	return_val_if_fail(thiz != NULL && thiz->first_group != NULL && group_name != NULL, INI_RET_FAIL);

	for(iter = thiz->first_group, prev = iter; iter != NULL; prev = iter, iter = iter->next)
	{
		if(strcmp(group_name, iter->name) == 0)
		{
			if(iter == thiz->first_group)
			{
				thiz->first_group = thiz->first_group->next;
			}
			else
			{
				prev->next = iter->next;
			}
		
			ini_group_destroy(iter);

			return INI_RET_OK;
		}
	}

	return INI_RET_NOT_EXIST;
}

IniGroup*  ini_groups_find(IniGroups* thiz, const char* group_name)
{
	IniGroup* iter = NULL;
	return_val_if_fail(thiz != NULL && thiz->first_group != NULL, NULL);

	for(iter = thiz->first_group; iter != NULL; iter = iter->next)
	{
		if(strcmp(iter->name, group_name) == 0)
		{
			return iter;
		}
	}

	return NULL;
}

static void ini_group_destroy(IniGroup* group)
{
	if(group != NULL)
	{
		free(group->name);
		group->name = NULL;
		group->next = NULL;
		if(group->pairs != NULL)
		{
			ini_pairs_destroy(group->pairs);
			group->pairs = NULL;
		}

		free(group);
	}

	return;
}

static IniGroup* ini_group_create(const char* group_name)
{
	IniRet ret = INI_RET_FAIL;
	IniGroup* group = (IniGroup*)calloc(1, sizeof(IniGroup));

	do
	{
		if((group->name = strdup(group_name)) == NULL) break;
		if((group->pairs = ini_pairs_create()) == NULL) break;
		
		ret = INI_RET_OK;
	}while(0);

	if(ret != INI_RET_OK)
	{
		ini_group_destroy(group);
		group = NULL;
	}

	return group;
}

IniRet  ini_groups_append(IniGroups* thiz, const char* group_name)
{
	IniGroup* group = NULL;
	IniGroup* last = NULL;

	return_val_if_fail(thiz != NULL && group_name != NULL, INI_RET_FAIL);
	group = ini_group_create(group_name);
	return_val_if_fail(group != NULL, INI_RET_FAIL);

	if(thiz->first_group == NULL)
	{
		thiz->first_group = group;

		return INI_RET_OK;
	}

	for(last = thiz->first_group; last->next != NULL; last = last->next)
	{
	}
	last->next = group;

	return INI_RET_OK;
}

IniRet     ini_groups_save(IniGroups* thiz, FILE* fp, char delim_char)
{
	IniGroup* iter = NULL;

	return_val_if_fail(thiz != NULL && thiz->first_group != NULL, 0);

	for(iter = thiz->first_group; iter != NULL; iter = iter->next)
	{
		if(strcmp(DEFAULT_GROUP, iter->name) != 0)
		{
			fprintf(fp, "[%s]\n", iter->name);
		}
		ini_pairs_save(iter->pairs, fp, delim_char);
	}

	return INI_RET_OK;
}

void ini_groups_destroy(IniGroups* thiz)
{
	IniGroup* iter = NULL;
	IniGroup* next = NULL;

	if(thiz != NULL)
	{
		iter = thiz->first_group;
		while(iter != NULL)
		{
			next = iter->next;
			ini_group_destroy(iter);
			iter = next;
		}

		free(thiz);
	}

	return;
}

#ifdef INI_GROUPS_TEST
#include <assert.h>

int main(int argc, char* argv[])
{
	IniGroup* group = NULL;
	IniGroups* thiz = ini_groups_create();
	assert(ini_groups_append(thiz, "name") == INI_RET_OK);
	assert(ini_groups_size(thiz) == 1);
	assert(ini_groups_append(thiz, "gender") == INI_RET_OK);
	assert(ini_groups_size(thiz) == 2);

	assert((group = ini_groups_find(thiz, "name")) != NULL);
	assert(strcmp(group->name, "name") == 0);
	
	assert((group = ini_groups_find(thiz, "gender")) != NULL);
	assert(strcmp(group->name, "gender") == 0);
	assert(ini_groups_save(thiz, stdout, '=') == INI_RET_OK);
	assert((group = ini_groups_find(thiz, "age")) == NULL);
	assert(ini_groups_del(thiz, "name") == INI_RET_OK);
	assert(ini_groups_size(thiz) == 1);

	assert(ini_groups_del(thiz, "name") != INI_RET_OK);

	ini_groups_destroy(thiz);

	return 0;
}
#endif/*INI_GROUPS_TEST*/

