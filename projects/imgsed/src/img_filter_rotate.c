/*
 * File:    img_filter_rotate.c
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   rotate the image.
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
#include "img_filter_rotate.h"
#include "img_filter_params.h"

static const FilterParamSpec g_rotate_param_specs[] =
{
	{PARAM_TYPE_INT, "angle", "the angle to rotate.", NULL, .defval.ivalue=0},
	{PARAM_TYPE_NONE}
};

typedef struct _PrivInfo
{
	int angle;
	char* args;
}PrivInfo;

static Ret img_filter_rotate_init_params(ImgFilter* thiz, GdkPixbuf* input)
{
	PrivInfo* info = (PrivInfo*)thiz->priv;
	ImgFilterParams* params = img_filter_params_create(thiz->param_specs, input, info->args);

	info->angle = img_filter_params_get_int(params, "angle", 0);
	if(info->angle < 90)
	{
		info->angle = 0;
	}
	else if(info->angle > 180)
	{
		info->angle = 90;
	}
	else if(info->angle < 270)
	{
		info->angle = 180;
	}
	else
	{
		info->angle = 270;
	}
	img_filter_params_destroy(params);

	return RET_OK;
}

static Ret img_filter_rotate_run(ImgFilter* thiz, GdkPixbuf* input, GdkPixbuf** output)
{
	PrivInfo* info = (PrivInfo*)thiz->priv;
	g_return_val_if_fail(input != NULL && output != NULL, RET_FAIL);

	img_filter_rotate_init_params(thiz, input);

	*output = gdk_pixbuf_rotate_simple(input, info->angle);

	return RET_OK;
}

static void img_filter_rotate_destroy(ImgFilter* thiz)
{
	if(thiz != NULL)
	{
		PrivInfo* info = (PrivInfo*)thiz->priv;
		free(info->args);
		free(thiz);
	}

	return;
}

ImgFilter* img_filter_rotate_create(const char* args)
{
	ImgFilter* thiz = calloc(1, sizeof(ImgFilter) + sizeof(PrivInfo));

	if(thiz != NULL)
	{
		PrivInfo* info = (PrivInfo*)thiz->priv;
		thiz->run      = img_filter_rotate_run;
		thiz->destroy  = img_filter_rotate_destroy;

		thiz->name = "rotate";
		thiz->param_specs = g_rotate_param_specs;
		info->args = args != NULL ? strdup(args) : NULL;
	}

	return thiz;
}

#ifdef IMG_FILTER_ROTATE_TEST
int main(int argc, char* argv[])
{
	ImgFilter* filter = img_filter_rotate_create("(50, 50)");

	img_filter_rotate_destroy(filter);

	return 0;
}
#endif/*IMG_FILTER_ROTATE_TEST*/

