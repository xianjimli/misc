/*
 * lrc_internal.h
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

#ifndef LRC_INTERNAL_H
#define LRC_INTERNAL_H
#include "lrc_builder.h"
#include "lrc_list.h"
#include "lrc_id_tag.h"
#include "lrc_time_tag.h"

Lrc* lrc_new(void);

void     lrc_add_id_tag(Lrc* thiz, LrcIdTag* id_tag);
void     lrc_add_time_tag(Lrc* thiz, LrcTimeTag* time_tag);

LrcList* lrc_get_id_tag_list(Lrc* thiz);
LrcList* lrc_get_time_tag_list(Lrc* thiz);

void     lrc_destroy(Lrc* thiz);
void     lrc_weak_ref(Lrc* thiz, LrcDestroyFunc on_destroy, void* on_destroy_ctx);

LRC_RESULT lrc_visit(Lrc* thiz, LrcBuilder* builder);

#endif/*LRC_INTERNAL_H*/
