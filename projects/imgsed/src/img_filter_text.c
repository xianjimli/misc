/*
 * File:    img_filter_text.c
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   draw text on the image.
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

#include <gdk/gdk.h>
#include "img_filter_text.h"
#include "img_filter_params.h"

static const FilterParamSpec g_text_param_specs[] =
{
	{PARAM_TYPE_STRING,  "font",   "text font",                         NULL, .defval.svalue="Sans Serif"},
	{PARAM_TYPE_INT,     "size",   "font size",                         NULL, .defval.ivalue=32},
	{PARAM_TYPE_STRING,  "text",   "text to draw",                      NULL, .defval.svalue="imgsed"},
	{PARAM_TYPE_INT,     "x",      "x position",                        NULL, .defval.ivalue=0},
	{PARAM_TYPE_INT,     "y",      "y position",                        NULL, .defval.ivalue=0},
	{PARAM_TYPE_STRING,  "color",  "text color(format: rrggbb in hex)", NULL, .defval.svalue="ff8080"},
	{PARAM_TYPE_BOOL,    "i",      "italic",                            NULL, .defval.bvalue=FALSE},
	{PARAM_TYPE_BOOL,    "b",      "bold",                              NULL, .defval.bvalue=TRUE},
	{PARAM_TYPE_NONE}
};

typedef struct _PrivInfo
{
	char* args;
	char* font;
	char* text;
	int   size;
	int   x;
	int   y;
	gboolean i;
	gboolean b;
	unsigned int color;
}PrivInfo;

static Ret img_filter_text_init_params(ImgFilter* thiz, GdkPixbuf* input)
{
	PrivInfo* info = (PrivInfo*)thiz->priv;
	ImgFilterParams* params = img_filter_params_create(thiz->param_specs, input, info->args);

	info->font = g_strdup(img_filter_params_get_string(params, "font"));
	info->text = g_strdup(img_filter_params_get_string(params, "text"));
	info->size    = img_filter_params_get_int(params, "size", 24);
	info->x       = img_filter_params_get_int(params, "x", 0);
	info->y       = img_filter_params_get_int(params, "y", 0);
	const char* color  = img_filter_params_get_string(params, "color");
	info->i       = img_filter_params_get_bool(params, "i", FALSE);
	info->b       = img_filter_params_get_bool(params, "b", FALSE);
	if(color != NULL)
	{
		sscanf(color, "%x", &info->color);
	}
	else
	{
		info->color = 0x8080ff;
	}
	img_filter_params_destroy(params);

	return RET_OK;
}

static Ret img_filter_text_run(ImgFilter* thiz, GdkPixbuf* input, GdkPixbuf** output)
{
	PrivInfo* info = (PrivInfo*)thiz->priv;
	g_return_val_if_fail(input != NULL && output != NULL, RET_FAIL);

	int width = gdk_pixbuf_get_width(input);
	int height = gdk_pixbuf_get_height(input);

	img_filter_text_init_params(thiz, input);
	double b = ((info->color>>16)&0xff)/256.0;
	double g = ((info->color>>8)&0xff)/256.0;
	double r = (info->color&0xff)/256.0;

	gtk_init(NULL, NULL);
	GdkPixmap* pixmap = gdk_pixmap_new(NULL, width, height, 24);
	GdkGC* gc = gdk_gc_new(pixmap);
	gdk_draw_pixbuf(pixmap, gc, input, 0, 0, 0, 0, width, height, 0, 0, 0);

	cairo_t* cr = gdk_cairo_create(pixmap);
	cairo_select_font_face (cr, info->font, 
		info->i ? CAIRO_FONT_SLANT_ITALIC : CAIRO_FONT_SLANT_NORMAL,
        info->b ? CAIRO_FONT_WEIGHT_BOLD : CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size (cr, info->size);
	cairo_move_to (cr, info->x, info->y);
	cairo_text_path (cr, info->text);
	cairo_set_source_rgb (cr, r, g, b);
	cairo_fill_preserve (cr);
	cairo_set_source_rgb (cr, 0, 0, 0);
	if(info->size > 70)
	{
		cairo_set_line_width (cr, 2.56);
		cairo_stroke (cr);
	}
	*output = gdk_pixbuf_get_from_drawable(NULL, pixmap, 
		gdk_screen_get_default_colormap(gdk_screen_get_default()),
		0, 0, 0, 0, width, height);
	g_object_unref(G_OBJECT(pixmap));

	return RET_OK;
}

static void img_filter_text_destroy(ImgFilter* thiz)
{
	if(thiz != NULL)
	{
		PrivInfo* info = (PrivInfo*)thiz->priv;
		g_free(info->args);
		g_free(info->font);
		g_free(info->text);
		free(thiz);
	}

	return;
}

ImgFilter* img_filter_text_create(const char* args)
{
	ImgFilter* thiz = calloc(1, sizeof(ImgFilter) + sizeof(PrivInfo));

	if(thiz != NULL)
	{
		PrivInfo* info = (PrivInfo*)thiz->priv;
		thiz->run      = img_filter_text_run;
		thiz->destroy  = img_filter_text_destroy;

		thiz->name = "text";
		thiz->param_specs = g_text_param_specs;
		info->args = args != NULL ? g_strdup(args) : NULL;
	}

	return thiz;
}

#ifdef IMG_FILTER_TEXT_TEST
int main(int argc, char* argv[])
{
	ImgFilter* filter = img_filter_text_create("(50, 50)");

	img_filter_text_destroy(filter);

	return 0;
}
#endif/*IMG_FILTER_TEXT_TEST*/

