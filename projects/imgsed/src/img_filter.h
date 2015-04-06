/*
 * File:    img_filter.h
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   image filter interface.
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
 * 2009-07-17 Li XianJing <xianjimli@hotmail.com> created
 *
 */
#ifndef IMG_FILTER_H
#define IMG_FILTER_H

#include <glib.h>
#include "typedef.h"
#include <gdk-pixbuf/gdk-pixbuf.h>
#include "img_filter_param_spec.h"

struct _ImgFilter;
typedef struct _ImgFilter ImgFilter;

typedef Ret (*ImgFilterRunFunc)(ImgFilter* thiz, GdkPixbuf* input, GdkPixbuf** output);
typedef void (*ImgFilterDestroyFunc)(ImgFilter* thiz);

struct _ImgFilter
{
	ImgFilterRunFunc run;
	ImgFilterDestroyFunc destroy;

	const char* name;
	const FilterParamSpec* param_specs;

	char priv[1];
};

static inline Ret img_filter_run(ImgFilter* thiz, GdkPixbuf* input, GdkPixbuf** output)
{
	g_return_val_if_fail(thiz != NULL && thiz->run != NULL, RET_FAIL);

	return thiz->run(thiz, input, output);
}

static inline void img_filter_destroy(ImgFilter* thiz)
{
	g_return_if_fail(thiz != NULL && thiz->destroy != NULL);

	thiz->destroy(thiz);

	return;
}

static inline const char* img_filter_get_name(ImgFilter* thiz)
{
	return thiz != NULL ? thiz->name:NULL;
}

static inline const FilterParamSpec* img_filter_get_param_specs(ImgFilter* thiz)
{
	return thiz != NULL ? thiz->param_specs : NULL;
}

#endif/*IMG_FILTER_H*/

