#include "lrc_type.h"

#ifndef LRC_BUILDER_H
#define LRC_BUILDER_H

struct _LrcBuilder;
typedef struct _LrcBuilder LrcBuilder;

typedef LRC_RESULT (*LrcBuilderOnBegin)(LrcBuilder* thiz, const char* buffer);
typedef LRC_RESULT (*LrcBuilderOnIDTag)(LrcBuilder* thiz, const char* key, size_t key_length, 
					const char* value, size_t value_length);
typedef LRC_RESULT (*LrcBuilderOnTimeTag)(LrcBuilder* thiz, size_t start_time);
typedef LRC_RESULT (*LrcBuilderOnLrc)(LrcBuilder* thiz, const char* lrc, size_t lrc_length);
typedef LRC_RESULT (*LrcBuilderOnEnd)(LrcBuilder* thiz);
typedef LRC_RESULT (*LrcBuilderDestroy)(LrcBuilder* thiz);

struct _LrcBuilder
{
	LrcBuilderOnBegin   on_begin;
	LrcBuilderOnIDTag   on_id_tag;
	LrcBuilderOnTimeTag on_time_tag;
	LrcBuilderOnLrc     on_lrc;
	LrcBuilderOnEnd     on_end;
	LrcBuilderDestroy   destroy;

	char priv[1];
};

static inline LRC_RESULT lrc_builder_on_begin(LrcBuilder* thiz, const char* buffer)
{
	return_val_if_fail(thiz != NULL && thiz->on_begin != NULL, LRC_RESULT_FAIL);

	return thiz->on_begin(thiz, buffer);
}

static inline LRC_RESULT lrc_builder_on_id_tag(LrcBuilder* thiz, 
	const char* key, size_t key_length, 
	const char* value, size_t value_length)
{
	return_val_if_fail(thiz != NULL && thiz->on_id_tag != NULL, LRC_RESULT_FAIL);

	return thiz->on_id_tag(thiz, key, key_length, value, value_length);
}

static inline LRC_RESULT lrc_builder_on_time_tag(LrcBuilder* thiz, 
	size_t start_time)
{
	return_val_if_fail(thiz != NULL && thiz->on_time_tag != NULL, LRC_RESULT_FAIL);

	return thiz->on_time_tag(thiz, start_time);
}

static inline LRC_RESULT lrc_builder_on_lrc(LrcBuilder* thiz, 
	const char* lrc, size_t lrc_length)
{
	return_val_if_fail(thiz != NULL && thiz->on_lrc != NULL, LRC_RESULT_FAIL);

	return thiz->on_lrc(thiz, lrc, lrc_length);
}

static inline LRC_RESULT lrc_builder_on_end(LrcBuilder* thiz)
{
	return_val_if_fail(thiz != NULL && thiz->on_end != NULL, LRC_RESULT_FAIL);

	return thiz->on_end(thiz);
}

static inline void lrc_builder_destroy(LrcBuilder* thiz)
{
	return_if_fail(thiz != NULL && thiz->destroy != NULL);

	thiz->destroy(thiz);

	return;
}

#endif/*LRC_BUILDER_H*/

