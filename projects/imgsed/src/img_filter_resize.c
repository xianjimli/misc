/*
 * File:    img_filter_resize.c
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   resize to image.
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
#include "img_filter_resize.h"
#include "img_filter_params.h"

static const FilterParamSpec g_resize_param_specs[] =
{
	{PARAM_TYPE_DOUBLE, "wscale", "wscale(>1)/wscale resize scale.", NULL, .defval.dvalue=1},
	{PARAM_TYPE_DOUBLE, "hscale", "hscale(>1)/wscale resize scale.", NULL, .defval.dvalue=1 },
	{PARAM_TYPE_NONE}
};

typedef struct _PrivInfo
{
	double wscale;
	double hscale;
	char*  args;
}PrivInfo;

static Ret img_filter_resize_init_params(ImgFilter* thiz, GdkPixbuf* input)
{
	PrivInfo* info = (PrivInfo*)thiz->priv;
	ImgFilterParams* params = img_filter_params_create(thiz->param_specs, input, info->args);

	double width = gdk_pixbuf_get_width(input);
	double height = gdk_pixbuf_get_height(input);

	info->wscale = img_filter_params_get_double(params, "wscale", 0);
	info->hscale = img_filter_params_get_double(params, "hscale", 0);

	if(info->wscale == 0 && info->hscale != 0)
	{
		info->wscale = info->hscale > 1 ? (info->hscale * width)/height : info->hscale;
	}
	
	if(info->wscale != 0 && info->hscale == 0)
	{
		info->hscale = info->wscale > 1 ? (info->wscale * height)/width : info->wscale;
	}
	
	if(info->wscale == 0 && info->hscale == 0)
	{
		info->wscale = info->hscale = 1;
	}

	if(info->wscale <= 1)
	{
		info->wscale = gdk_pixbuf_get_width(input) * info->wscale;
	}
	
	if(info->hscale <= 1)
	{
		info->hscale = gdk_pixbuf_get_height(input) * info->hscale;
	}

	img_filter_params_destroy(params);

	return RET_OK;
}

static Ret img_filter_resize_run(ImgFilter* thiz, GdkPixbuf* input, GdkPixbuf** output)
{
	PrivInfo* info = (PrivInfo*)thiz->priv;
	g_return_val_if_fail(input != NULL && output != NULL, RET_FAIL);

	img_filter_resize_init_params(thiz, input);

	*output = gdk_pixbuf_scale_simple(input, info->wscale, info->hscale, GDK_INTERP_NEAREST);

	return RET_OK;
}

static void img_filter_resize_destroy(ImgFilter* thiz)
{
	g_return_if_fail(thiz != NULL);

	PrivInfo* info = (PrivInfo*)thiz->priv;
	free(info->args);
	free(thiz);

	return;
}

ImgFilter* img_filter_resize_create(const char* args)
{
	ImgFilter* thiz = calloc(1, sizeof(ImgFilter) + sizeof(PrivInfo));

	if(thiz != NULL)
	{
		PrivInfo* info = (PrivInfo*)thiz->priv;
		thiz->run      = img_filter_resize_run;
		thiz->destroy  = img_filter_resize_destroy;

		thiz->name = "resize";
		thiz->param_specs = g_resize_param_specs;

		if(args != NULL)
		{
			info->args = strdup(args);
		}
	}

	return thiz;
}

#ifdef IMG_FILTER_RESIZE_TEST
int main(int argc, char* argv[])
{
	ImgFilter* filter = img_filter_resize_create("(50, 50)");

	img_filter_resize_destroy(filter);

	return 0;
}
#endif/*IMG_FILTER_RESIZE_TEST*/
