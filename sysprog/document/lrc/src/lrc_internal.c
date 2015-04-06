/*
 * lrc_tree.c
 * Copyright (C) 2006-2009 Li XianJing <xianjimli@hotmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330, 
 * Boston, MA 02111-1307, USA.
 */

#include <string.h>
#include <stdlib.h>
#include "lrc_internal.h"

struct _Lrc
{
	LrcList* id_tags;
	LrcList* time_tags;
	
	LrcDestroyFunc on_destroy;
	void* on_destroy_ctx;
};

Lrc* lrc_new(void)
{
	Lrc* thiz = LRC_ALLOC(Lrc, 1);

	if(thiz != NULL)
	{
		thiz->id_tags = lrc_list_new((LrcItemDestroyFunc)lrc_id_tag_destroy, 10);
		thiz->time_tags = lrc_list_new((LrcItemDestroyFunc)lrc_time_tag_destroy, 120);
	}

	return thiz;
}

void     lrc_add_id_tag(Lrc* thiz, LrcIdTag* id_tag)
{
	LRC_ASSERT(thiz != NULL && id_tag != NULL);

	if(thiz != NULL && id_tag != NULL)
	{
		LrcListIter iter = lrc_list_first(thiz->id_tags);
		lrc_list_insert(&iter, id_tag, 0);
	}

	return;
}

void     lrc_add_time_tag(Lrc* thiz, LrcTimeTag* time_tag)
{
	LRC_ASSERT(thiz != NULL && time_tag != NULL);

	if(thiz != NULL && time_tag != NULL)
	{
		lrc_list_insert_sorted(thiz->time_tags, time_tag, lrc_time_tag_compare);
	}

	return;
}

LrcList* lrc_get_id_tag_list(Lrc* thiz)
{
	LRC_ASSERT(thiz != NULL);

	return thiz != NULL ? thiz->id_tags : NULL;
}

LrcList* lrc_get_time_tag_list(Lrc* thiz)
{
	LRC_ASSERT(thiz != NULL);

	return thiz != NULL ? thiz->time_tags : NULL;
}

void     lrc_destroy(Lrc* thiz)
{
	if(thiz != NULL)
	{
		if(thiz->id_tags != NULL)
		{
			lrc_list_destroy(thiz->id_tags);
			thiz->id_tags = NULL;
		}

		if(thiz->time_tags != NULL)
		{
			lrc_list_destroy(thiz->time_tags);
			thiz->time_tags = NULL;
		}
	
		if(thiz->on_destroy != NULL)
		{
			thiz->on_destroy(thiz->on_destroy_ctx);
		}
		LRC_FREE(thiz);
	}

	return;
}

LRC_RESULT lrc_visit(Lrc* thiz, LrcBuilder* builder)
{
	LrcIdTag* id_tag = NULL;
	LrcTimeTag* time_tag = NULL;
	LrcListIter iter = {0};

	LRC_ASSERT(thiz != NULL && builder != NULL);

	if(thiz != NULL && builder != NULL)
	{
		const char* key = NULL;
		const char* value = NULL;
		const char* lrc = NULL;
		
		iter = lrc_list_first(thiz->id_tags);
		while(!lrc_list_iter_is_null(&iter))
		{
			id_tag = (LrcIdTag*)lrc_list_iter_data(&iter);
			key = lrc_id_tag_get_key(id_tag);
			value = lrc_id_tag_get_value(id_tag);
			
			builder->on_id_tag(builder, key, strlen(key), value, strlen(value));
			
			iter = lrc_list_iter_next(&iter);			
		}

		iter = lrc_list_first(thiz->time_tags);
		while(!lrc_list_iter_is_null(&iter))
		{
			time_tag = (LrcTimeTag*)lrc_list_iter_data(&iter);
		
			lrc = lrc_time_tag_get_lrc(time_tag);
			builder->on_time_tag(builder, lrc_time_tag_get_start_time(time_tag));
			builder->on_lrc(builder, lrc, strlen(lrc));
			
			iter = lrc_list_iter_next(&iter);
		}
	}

	return LRC_RESULT_OK;
}

void     lrc_weak_ref(Lrc* thiz, LrcDestroyFunc on_destroy, void* on_destroy_ctx)
{
	if(thiz != NULL)
	{
		thiz->on_destroy = on_destroy;
		thiz->on_destroy_ctx = on_destroy_ctx;
	}

	return;
}

#ifdef LRC_TREE_TEST
#include <stdio.h>
#include "lrc_dumpbuilder.h"
#define N 10
int main(int argc, char* argv[])
{
	int i = 0;
	char key[100] = {"key"};
	char value[100] = {"value"};
	char lrc[100] = {"lrc"};
	
	LrcPool* id_tag_pool = lrc_pool_new(lrc_id_tag_size(), 10);
	LrcPool* time_tag_pool = lrc_pool_new(lrc_time_tag_size(), 100);
	LrcIdTag* id_tag = NULL;
	LrcTimeTag* time_tag = NULL;
	LrcBuilder* dumper = lrc_dump_builder_new(stdout);
	Lrc* thiz = lrc_new();
	
	for(i = 0; i < N; i++)
	{
		id_tag = lrc_id_tag_new(id_tag_pool, key, value);
		lrc_add_id_tag(thiz, id_tag);
		time_tag = lrc_time_tag_new(time_tag_pool, i, lrc);
		lrc_add_time_tag(thiz, time_tag);
	}
	
	lrc_visit(thiz, dumper);

	dumper->destroy(dumper);
	lrc_destroy(thiz);
	lrc_pool_destroy(id_tag_pool);
	lrc_pool_destroy(time_tag_pool);
	
	return 0;
}
#endif
