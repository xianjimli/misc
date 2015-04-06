/*
 * File:    ini_pairs.c
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
#include "ini_util.h"
#include "ini_pairs.h"

static void ini_pair_destroy(IniPair* pair);

IniPairs*  ini_pairs_create(void)
{
	return (IniPairs*)calloc(1, sizeof(IniPairs));
}

size_t     ini_pairs_size(IniPairs* thiz)
{
	size_t   size = 0;
	IniPair* iter = NULL;
	return_val_if_fail(thiz != NULL && thiz->first_pair != NULL, 0);

	for(iter = thiz->first_pair; iter != NULL; iter = iter->next)
	{
		size++;
	}

	return size;
}

IniRet     ini_pairs_del(IniPairs* thiz, const char* key)
{
	IniPair* iter = NULL;
	IniPair* prev = NULL;
	return_val_if_fail(thiz != NULL && thiz->first_pair != NULL && key != NULL, INI_RET_FAIL);

	for(iter = thiz->first_pair, prev = iter; iter != NULL; prev = iter, iter = iter->next)
	{
		if(strcmp(key, iter->key) == 0)
		{
			if(iter == thiz->first_pair)
			{
				thiz->first_pair = thiz->first_pair->next;
			}
			else
			{
				prev->next = iter->next;
			}
			ini_pair_destroy(iter);

			return INI_RET_OK;
		}
	}

	return INI_RET_NOT_EXIST;
}

IniPair*   ini_pairs_find(IniPairs* thiz, const char* key)
{
	IniPair* iter = NULL;
	return_val_if_fail(thiz != NULL && thiz->first_pair != NULL, NULL);

	for(iter = thiz->first_pair; iter != NULL; iter = iter->next)
	{
		if(strcmp(iter->key, key) == 0)
		{
			return iter;
		}
	}

	return NULL;
}

static void ini_pair_destroy(IniPair* pair)
{
	if(pair != NULL)
	{
		free(pair->key);
		pair->key = NULL;
		free(pair->value);
		pair->value = NULL;
		pair->next = NULL;
		free(pair);
	}

	return;
}

static IniPair* ini_pair_create(const char* key, const char* value)
{
	IniRet ret = INI_RET_FAIL;
	IniPair* pair = calloc(1, sizeof(IniPair));

	do
	{
		if(pair == NULL) break;
		if((pair->key = strdup(key)) == NULL) break;
		if((pair->value = strdup(value)) == NULL) break;

		ret = INI_RET_OK;
	}while(0);

	if(ret != INI_RET_OK)
	{
		ini_pair_destroy(pair);
		pair = NULL;
	}

	return pair;
}

IniRet   ini_pairs_append(IniPairs* thiz, const char* key, const char* value)
{
	IniPair* pair = NULL;
	IniPair* last = NULL;
	return_val_if_fail(thiz != NULL && key != NULL && value != NULL, INI_RET_FAIL);
	pair = ini_pair_create(key, value);
	return_val_if_fail(pair != NULL, INI_RET_FAIL);

	if(thiz->first_pair == NULL)
	{
		thiz->first_pair = pair;

		return INI_RET_OK;
	}

	for(last = thiz->first_pair; last->next != NULL; last = last->next)
	{
	}

	last->next = pair;

	return INI_RET_OK;
}

IniRet     ini_pairs_save(IniPairs* thiz, FILE* fp, char delim_char)
{
	IniPair* iter = NULL;
	return_val_if_fail(thiz != NULL, INI_RET_FAIL);

	for(iter = thiz->first_pair; iter != NULL; iter = iter->next)
	{
		fprintf(fp, "  %s %c %s\n", iter->key, delim_char, iter->value);
	}

	return INI_RET_OK;
}

void       ini_pairs_destroy(IniPairs* thiz)
{
	IniPair* iter = NULL;
	IniPair* next = NULL;

	if(thiz != NULL)
	{
		iter = thiz->first_pair;
		while(iter != NULL)
		{
			next = iter->next;
			ini_pair_destroy(iter);
			iter = next;
		}

		free(thiz);
	}

	return;
}

#ifdef INI_PAIRS_TEST
#include <assert.h>

int main(int argc, char* argv[])
{
	IniPair* pair = NULL;
	IniPairs* thiz = ini_pairs_create();
	assert(ini_pairs_append(thiz, "name", "lixianjing") == INI_RET_OK);
	assert(ini_pairs_size(thiz) == 1);
	assert(ini_pairs_append(thiz, "gender", "male") == INI_RET_OK);
	assert(ini_pairs_size(thiz) == 2);

	assert((pair = ini_pairs_find(thiz, "name")) != NULL);
	assert(strcmp(pair->key, "name") == 0);
	assert(strcmp(pair->value, "lixianjing") == 0);
	
	assert((pair = ini_pairs_find(thiz, "gender")) != NULL);
	assert(strcmp(pair->key, "gender") == 0);
	assert(strcmp(pair->value, "male") == 0);
	assert(ini_pairs_save(thiz, stdout, '=') == INI_RET_OK);
	assert((pair = ini_pairs_find(thiz, "age")) == NULL);
	assert(ini_pairs_del(thiz, "name") == INI_RET_OK);
	assert(ini_pairs_size(thiz) == 1);

	assert(ini_pairs_del(thiz, "name") != INI_RET_OK);

	ini_pairs_destroy(thiz);

	return 0;
}
#endif/*INI_PAIRS_TEST*/

