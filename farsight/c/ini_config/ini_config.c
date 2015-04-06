/*
 * File:    ini_config.c
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
#include "ini_parser.h"
#include "ini_config.h"

IniConfig*  ini_config_create(const char* file_name)
{
	IniConfig* thiz = NULL;
	IniRet ret = INI_RET_FAIL;

	do
	{
		if((thiz = (IniConfig*)calloc(1, sizeof(IniConfig))) == NULL) break;
		if((thiz->file_name = strdup(file_name)) == NULL) break;
		thiz->groups = ini_parse(file_name, '#', '=');

		if(thiz->groups == NULL)
		{
			thiz->groups = ini_groups_create();
		}
		if(thiz->groups == NULL) break;
		ret = INI_RET_OK;
	}while(0);

	if(ret != INI_RET_OK)
	{
		ini_config_destroy(thiz);
		thiz = NULL;
	}

	return thiz;
}

IniRet      ini_config_set(IniConfig* thiz, const char* group_name, const char* key, const char* value)
{
	IniGroup* group = NULL;
	IniRet ret = INI_RET_FAIL;

	return_val_if_fail(thiz != NULL && group_name != NULL && key != NULL && value != NULL, INI_RET_FAIL);

	if((group = ini_groups_find(thiz->groups, group_name)) == NULL)
	{
		ini_groups_append(thiz->groups, group_name);
		group = ini_groups_find(thiz->groups, group_name);
	}

	if(group != NULL)
	{
		IniPair* pair = ini_pairs_find(group->pairs, key);
		if(pair != NULL)
		{
			if((value = strdup(value)) != NULL)
			{
				free(pair->value);
				pair->value = (char*)value;

				ret = INI_RET_OK;
			}
		}
		else
		{
			ret = ini_pairs_append(group->pairs, key, value);
		}
	}

	return ret;
}

const char* ini_config_get(IniConfig* thiz, const char* group_name, const char* key)
{
	IniPair* pair = NULL;
	IniGroup* group = NULL;

	return_val_if_fail(thiz != NULL && group_name != NULL && key != NULL, NULL);

	if((group = ini_groups_find(thiz->groups, group_name)) != NULL)
	{
		pair = ini_pairs_find(group->pairs, key);
	}

	return pair != NULL ? pair->value : NULL;
}

IniRet ini_config_del(IniConfig* thiz, const char* group_name, const char* key)
{
	IniGroup* group = NULL;
	IniRet ret = INI_RET_FAIL;

	return_val_if_fail(thiz != NULL && group_name != NULL && key != NULL, ret);

	if((group = ini_groups_find(thiz->groups, group_name)) != NULL)
	{
		ret = ini_pairs_del(group->pairs, key);
	}

	return ret;
}

IniRet      ini_config_save(IniConfig* thiz)
{
	FILE* fp = NULL;
	IniRet ret = INI_RET_FAIL;
	return_val_if_fail(thiz != NULL, INI_RET_FAIL);
	fp = fopen(thiz->file_name, "wb+");
	return_val_if_fail(fp != NULL, INI_RET_FAIL);

	ret = ini_groups_save(thiz->groups, fp != NULL ? fp : stderr, '=');
	fclose(fp);

	return ret;
}

void        ini_config_destroy(IniConfig* thiz)
{
	if(thiz != NULL)
	{
		free(thiz->file_name);
		thiz->file_name = NULL;
		ini_groups_destroy(thiz->groups);
		thiz->groups = NULL;

		free(thiz);
	}

	return;
}

#ifdef INI_CONFIG_TEST
#include <assert.h>

void ini_config_test1(void)
{
	IniConfig* thiz = ini_config_create("./test1.ini");
	assert(ini_config_set(thiz, "lixianjing", "name", "lixianjing") == INI_RET_OK);
	assert(ini_config_set(thiz, "lixianjing", "gender", "male") == INI_RET_OK);
	assert(ini_config_set(thiz, "lixianjing", "email", "xianjimli@hotmail.com") == INI_RET_OK);
	
	assert(ini_config_set(thiz, "zhangshan", "name", "zhangshan") == INI_RET_OK);
	assert(ini_config_set(thiz, "zhangshan", "gender", "male") == INI_RET_OK);
	assert(ini_config_set(thiz, "zhangshan", "email", "zhangshan@hotmail.com") == INI_RET_OK);
	assert(strcmp(ini_config_get(thiz, "zhangshan", "name"), "zhangshan") == 0);
	assert(strcmp(ini_config_get(thiz, "zhangshan", "gender"), "male") == 0);
	assert(strcmp(ini_config_get(thiz, "zhangshan", "email"), "zhangshan@hotmail.com") == 0);

	assert(ini_config_save(thiz) == INI_RET_OK);
	assert(ini_config_del(thiz, "zhangshan", "name") == INI_RET_OK);
	assert(ini_config_get(thiz, "zhangshan", "name") == NULL);

	ini_config_destroy(thiz);

	return;
}

int main(int argc, char* argv[])
{
	ini_config_test1();
	return 0;
}
#endif/*INI_CONFIG_TEST*/
