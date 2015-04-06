/*
 * File:    img_filter_save.c
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   save the image.
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
#include "img_filter_save.h"
#include "img_filter_params.h"

#define STR_DEFAULT_FILENAME "output.png"

static const FilterParamSpec g_save_param_specs[] =
{
	{PARAM_TYPE_STRING, "filename", "the file name you want to save.", NULL, .defval.svalue=STR_DEFAULT_FILENAME},
	{PARAM_TYPE_NONE}
};

typedef struct _PrivInfo
{
	char* filename;
	char* args;
}PrivInfo;

static Ret img_filter_save_init_params(ImgFilter* thiz, GdkPixbuf* input)
{
	PrivInfo* info = (PrivInfo*)thiz->priv;
	ImgFilterParams* params = img_filter_params_create(thiz->param_specs, input, info->args);

	info->filename = g_strdup(img_filter_params_get_string(params, "filename"));
	if(info->filename == NULL)
	{
		info->filename = g_strdup(STR_DEFAULT_FILENAME);
	}
	img_filter_params_destroy(params);

	return RET_OK;
}

static Ret img_filter_save_run(ImgFilter* thiz, GdkPixbuf* input, GdkPixbuf** output)
{
	PrivInfo* info = (PrivInfo*)thiz->priv;
	g_return_val_if_fail(input != NULL && output != NULL, RET_FAIL);

	img_filter_save_init_params(thiz, input);
	*output = gdk_pixbuf_copy(input);

	if(*output != NULL)
	{
		GError* error = NULL;
		const char* type = strrchr(info->filename, '.');
		if(type != NULL)
		{
			type++;
			if(strcmp(type, "jpg") == 0)
			{
				type = "jpeg";
			}
		}

		if(!gdk_pixbuf_save(*output, info->filename, type, &error, NULL))
		{
			g_debug("%s:%d %s\n", __func__, __LINE__, error->message);
			g_error_free(error);
		}
	}
	
	return RET_FAIL;
}

static void img_filter_save_destroy(ImgFilter* thiz)
{
	g_return_if_fail(thiz != NULL);

	PrivInfo* info = (PrivInfo*)thiz->priv;

	g_free(info->args);
	g_free(info->filename);
	free(thiz);

	return;
}

ImgFilter* img_filter_save_create(const char* args)
{
	ImgFilter* thiz = calloc(1, sizeof(ImgFilter) + sizeof(PrivInfo));

	if(thiz != NULL)
	{
		PrivInfo* info = (PrivInfo*)thiz->priv;
		thiz->run      = img_filter_save_run;
		thiz->destroy  = img_filter_save_destroy;

		thiz->name = "save";
		thiz->param_specs = g_save_param_specs;
		if(args != NULL)
		{
			info->args = g_strdup(args);
		}
		info->filename = NULL;
	}

	return thiz;
}

#ifdef IMG_FILTER_SAVE_TEST
int main(int argc, char* argv[])
{
	ImgFilter* filter = img_filter_save_create("(50, 50)");

	img_filter_save_destroy(filter);

	return 0;
}
#endif/*IMG_FILTER_SAVE_TEST*/

