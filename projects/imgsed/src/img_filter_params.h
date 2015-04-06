/*
 * File:    img_filter_params.h
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   
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
#ifndef IMG_FILTER_PARAMS_H
#define IMG_FILTER_PARAMS_H
#include <glib.h>
#include "typedef.h"
#include <gdk-pixbuf/gdk-pixbuf.h>
#include "img_filter_param_spec.h"

struct _ImgFilterParams;
typedef struct _ImgFilterParams ImgFilterParams;

ImgFilterParams* img_filter_params_create(const FilterParamSpec* specs, GdkPixbuf* pixbuf, const char* params);

gboolean    img_filter_params_get_bool(ImgFilterParams* thiz, const char* param, gboolean defval);
int         img_filter_params_get_int(ImgFilterParams* thiz, const char* param, int defval);
double      img_filter_params_get_double(ImgFilterParams* thiz, const char* param, double defval);
const char* img_filter_params_get_string(ImgFilterParams* thiz, const char* param);

void img_filter_params_destroy(ImgFilterParams* thiz);

#endif/*IMG_FILTER_PARAMS_H*/

