/*
 * lrc_defaultbuilder.c
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lrc_defaultbuilder.h"

typedef struct _LrcOnDestroyCtx
{
	LrcPool* id_tag_pool;
	LrcPool* time_tag_pool;
	char* buffer;
}LrcOnDestroyCtx;

struct _LrcDefaultBuilder
{
	char* p;
	char* buffer;
	size_t buffer_length;
	
	Lrc* lrc;
	LrcPool* id_tag_pool;
	LrcPool* time_tag_pool;
	LrcList* temp_time_tags;
};
typedef struct _LrcDefaultBuilder LrcDefaultBuilder;

static void lrc_on_destroy(void* data)
{
	LrcOnDestroyCtx* ctx = data;

	if(ctx != NULL)
	{
		lrc_pool_destroy(ctx->id_tag_pool);
		lrc_pool_destroy(ctx->time_tag_pool);
		LRC_FREE(ctx->buffer);
		LRC_FREE(ctx);
	}

	return;
}

Lrc* lrc_default_builder_get_lrc(LrcBuilder* thiz)
{
	Lrc* lrc = NULL;
	LrcDefaultBuilder* data = NULL;
	
	LRC_ASSERT(thiz != NULL);
	
	if(thiz != NULL)
	{
		data = (LrcDefaultBuilder*)thiz->priv;	
		lrc = data->lrc;
		data->lrc = NULL;
	}

	return lrc;
}

static LRC_RESULT lrc_default_builder_reset(LrcBuilder* thiz)
{
	LrcDefaultBuilder* data = NULL;
	
	LRC_ASSERT(thiz != NULL);
	
	if(thiz != NULL)
	{
		data = (LrcDefaultBuilder*)thiz->priv;	
		
		if(data->lrc != NULL)
		{
			lrc_destroy(data->lrc);
			data->lrc = NULL;
		}
		
		if(data->temp_time_tags != NULL)
		{
			lrc_list_destroy(data->temp_time_tags);
			data->temp_time_tags = NULL;
		}
	}

	return LRC_RESULT_OK;
}

static LRC_RESULT lrc_default_builder_on_begin(LrcBuilder* thiz, const char* buffer)
{
	LrcDefaultBuilder* data = NULL;
	
	printf("%s\n", __func__);

	LRC_ASSERT(thiz != NULL && buffer != NULL);
	
	lrc_default_builder_reset(thiz);

	if(thiz != NULL && buffer != NULL)
	{
		data = (LrcDefaultBuilder*)thiz->priv;	

		data->buffer = strdup(buffer);
		data->p = data->buffer;
		data->lrc          = lrc_new();
		data->id_tag_pool   = lrc_pool_new(lrc_id_tag_size(), 10);
		data->time_tag_pool = lrc_pool_new(lrc_time_tag_size(), 120);
		data->buffer_length  = strlen(buffer);
		data->temp_time_tags = lrc_list_new(NULL, 20);
		
		return LRC_RESULT_OK;
	}
	else
	{
		return LRC_RESULT_FAIL;
	}
}

static char* lrc_strdup(LrcDefaultBuilder* thiz, const char* str, size_t length)
{
	char* new_str = thiz->p;

	LRC_ASSERT((new_str + length) < (thiz->buffer + thiz->buffer_length));

	if((new_str + length + 1) < (thiz->buffer + thiz->buffer_length))
	{
		strncpy(new_str, str, length);
		new_str[length] = '\0';
		thiz->p += length + 1;
	}

	return new_str;
}

static LRC_RESULT lrc_default_builder_on_id_tag(LrcBuilder* thiz, const char* key, size_t key_length, 
					const char* value, size_t value_length)
{
	LrcDefaultBuilder* data = NULL;
	
	LRC_ASSERT(thiz != NULL && key != NULL && value != NULL);

	if(thiz != NULL && key != NULL && value != NULL)
	{
		LrcIdTag* id_tag = NULL;
		data = (LrcDefaultBuilder*)thiz->priv;
		
		id_tag = lrc_id_tag_new(data->id_tag_pool, lrc_strdup(data, key, key_length), lrc_strdup(data, value, value_length));

		lrc_add_id_tag(data->lrc, id_tag);
	}

	return LRC_RESULT_OK;
}

static LRC_RESULT lrc_default_builder_on_time_tag(LrcBuilder* thiz, size_t start_time)
{
	LrcDefaultBuilder* data = NULL;
	
	LRC_ASSERT(thiz != NULL);

	if(thiz != NULL)
	{
		LrcTimeTag* time_tag = NULL;
		LrcListIter iter = {0};
		data = (LrcDefaultBuilder*)thiz->priv;
		time_tag = lrc_time_tag_new(data->time_tag_pool, start_time, NULL);
		
		iter = lrc_list_first(data->temp_time_tags);
		lrc_list_insert(&iter, time_tag, 0);
	}
	
	return LRC_RESULT_OK;
}

static LRC_RESULT lrc_default_builder_on_lrc(LrcBuilder* thiz, const char* lrc, size_t lrc_length)
{
	LrcDefaultBuilder* data = NULL;
	
	LRC_ASSERT(thiz != NULL && lrc != NULL);

	if(thiz != NULL && lrc != NULL)
	{
		char* new_lrc = NULL;
		LrcListIter iter = {0};
		LrcTimeTag* time_tag = NULL;
		
		data = (LrcDefaultBuilder*)thiz->priv;
		iter = lrc_list_first(data->temp_time_tags);
	
		new_lrc = lrc_strdup(data, lrc, lrc_length);
		while(!lrc_list_iter_is_null(&iter))
		{
			time_tag = (LrcTimeTag*)lrc_list_iter_data(&iter);
			lrc_time_tag_set_lrc(time_tag, new_lrc);
			lrc_add_time_tag(data->lrc, time_tag);

			iter = lrc_list_iter_next(&iter);
		}
	}

	lrc_list_reset(data->temp_time_tags);

	return LRC_RESULT_OK;
}

static LRC_RESULT lrc_default_builder_on_end(LrcBuilder* thiz)
{
	LrcDefaultBuilder* data = (LrcDefaultBuilder*)thiz->priv;
	
	LrcOnDestroyCtx* ctx = LRC_CALLOC(1, sizeof(LrcOnDestroyCtx));
	ctx->id_tag_pool = data->id_tag_pool;
	ctx->time_tag_pool = data->time_tag_pool;
	ctx->buffer = data->buffer;
	lrc_weak_ref(data->lrc, lrc_on_destroy, ctx);

	printf("%s\n", __func__);

	return LRC_RESULT_OK;
}

static LRC_RESULT lrc_default_builder_destroy(LrcBuilder* thiz)
{
	LrcDefaultBuilder* data = (LrcDefaultBuilder*)thiz->priv;

	lrc_default_builder_reset(thiz);

	LRC_FREE(thiz);

	return LRC_RESULT_OK;
}

LrcBuilder* lrc_default_builder_new(void)
{
	LrcDefaultBuilder* data =  NULL;
	LrcBuilder* thiz = (LrcBuilder*)calloc(sizeof(LrcBuilder) + sizeof(LrcDefaultBuilder), 1);

	if(thiz != NULL)
	{
		thiz->on_begin     = lrc_default_builder_on_begin;
		thiz->on_id_tag    = lrc_default_builder_on_id_tag;
		thiz->on_time_tag  = lrc_default_builder_on_time_tag;
		thiz->on_lrc       = lrc_default_builder_on_lrc;
		thiz->on_end       = lrc_default_builder_on_end;
		thiz->destroy      = lrc_default_builder_destroy;
		data = (LrcDefaultBuilder*)thiz->priv;
	}

	return thiz;
}

