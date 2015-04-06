/*
 * File:    img_filter_params.c
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
#include <glib.h>
#include "expr.h"
#include "img_filter_params.h"

struct _ImgFilterParams
{
	GHashTable* hash_table;
};

static const char* get_next_param(const char* params, char* param, size_t len)
{
	int i = 0;
	const char* p = params;

	for(i = 0; i < len && *p != '\0' && *p != ','; p++, i++)
	{
		param[i] = *p;
	}
	param[i] = '\0';

	return *p == ',' ? p+1 : NULL;
}

static char* img_filter_params_preprocess(GdkPixbuf* pixbuf, const char* params)
{
	char* str = NULL;
	const char* src = params;
	GString*  new_params = g_string_new("");
	ImgExtraInfo* info = GET_EXTRA(pixbuf);
	struct tm* ctm = localtime(&(info->fstat.st_mtime));

	for(;*src != '\0'; src++)
	{
		if(*src == '%')
		{
			switch(src[1])
			{
				case '%':
				{
					g_string_append_c(new_params, *src);
					break;
				}
				case 'w':
				{
					g_string_append_printf(new_params, "%d", gdk_pixbuf_get_width(pixbuf));
					break;
				}
				case 'h':
				{
					g_string_append_printf(new_params, "%d", gdk_pixbuf_get_height(pixbuf));
					break;
				}
				case 'f':
				{
					char* filename = NULL;
					char* p = strrchr(info->filename, '/');
					if(p != NULL)
					{
						filename = strdup(p + 1);
					}
					else
					{
						filename = strdup(info->filename);
					}

					if((p = strrchr(filename, '.')) != NULL)
					{
						*p = '\0';
					}

					g_string_append(new_params, filename);

					free(filename);
					break;
				}
				case 'F':
				{
					g_string_append(new_params, info->filename);
					break;
				}
				case 'y':
				{
					g_string_append_printf(new_params, "%d", ctm->tm_year + 1900);
					break;
				}
				case 'm':
				{
					g_string_append_printf(new_params, "%02d", ctm->tm_mon);
					break;
				}
				case 'd':
				{
					g_string_append_printf(new_params, "%02d", ctm->tm_mday);
					break;
				}
				default:
				{
					g_string_append_c(new_params, src[0]);
					g_string_append_c(new_params, src[1]);
					break;
				}
			}
			src++;
		}
		else
		{
			g_string_append_c(new_params, *src);
		}
	}

	str = new_params->str;
	new_params->str = NULL;
	g_string_free(new_params, FALSE);

	return str;
}

ImgFilterParams* img_filter_params_create(const FilterParamSpec* specs, GdkPixbuf* pixbuf, const char* params)
{
	int i = 0;
	char param[512] = {0};
	char* new_params = NULL;
	ImgFilterParams* thiz = NULL;
	g_return_val_if_fail(specs != NULL && params != NULL && pixbuf != NULL, NULL);

	thiz = g_new0(ImgFilterParams, 1);
	g_return_val_if_fail(thiz != NULL, NULL);

	new_params = img_filter_params_preprocess(pixbuf, params);
	g_return_val_if_fail(new_params != NULL, NULL);

	params = new_params;
	thiz->hash_table = g_hash_table_new(g_str_hash, g_str_equal);
	for(i = 0; specs[i].type != PARAM_TYPE_NONE && params != NULL; i++)
	{
		params = get_next_param(params, param, sizeof(param));
		
		if(param[0] == '\0') continue;
		
		GValue* value = g_new0(GValue, 1);
		switch(specs[i].type)
		{
			case PARAM_TYPE_INT:
			{
				int ivalue = (int)expr_eval(param);
				g_value_init(value, G_TYPE_INT);
				g_value_set_int(value, ivalue);
				break;
			}
			case PARAM_TYPE_DOUBLE:
			{
				double dvalue = expr_eval(param);
				g_value_init(value, G_TYPE_DOUBLE);
				g_value_set_double(value, dvalue);
				break;
			}
			case PARAM_TYPE_STRING:
			{
				g_value_init(value, G_TYPE_STRING);
				g_value_set_string(value, param);
				break;
			}
			case PARAM_TYPE_BOOL:
			{
				g_value_init(value, G_TYPE_BOOLEAN);
				g_value_set_boolean(value, strcmp(param, "true") == 0);
				break;
			}
		}
		g_hash_table_insert(thiz->hash_table, strdup(specs[i].name), value);
	}
	g_free(new_params);

	return thiz;
}

gboolean img_filter_params_get_bool(ImgFilterParams* thiz, const char* param, gboolean defval)
{
	GValue* val = NULL;
	g_return_val_if_fail(thiz != NULL && param != NULL, defval);

	val = g_hash_table_lookup(thiz->hash_table, param);

	return val != NULL ? g_value_get_boolean(val) : defval;
}

int    img_filter_params_get_int(ImgFilterParams* thiz, const char* param, int defval)
{
	GValue* val = NULL;
	g_return_val_if_fail(thiz != NULL && param != NULL, defval);

	val = g_hash_table_lookup(thiz->hash_table, param);

	return val != NULL ? g_value_get_int(val) : defval;
}
double img_filter_params_get_double(ImgFilterParams* thiz,const char* param, double defval)
{
	GValue* val = NULL;
	g_return_val_if_fail(thiz != NULL && param != NULL, defval);

	val = g_hash_table_lookup(thiz->hash_table, param);

	return val != NULL ? g_value_get_double(val) : defval;
}

const char* img_filter_params_get_string(ImgFilterParams* thiz, const char* param)
{
	GValue* val = NULL;
	g_return_val_if_fail(thiz != NULL && param != NULL, NULL);

	val = g_hash_table_lookup(thiz->hash_table, param);

	return val != NULL ? g_value_get_string(val) : NULL;
}

void img_filter_params_destroy(ImgFilterParams* thiz)
{
	if(thiz != NULL)
	{
		g_hash_table_destroy(thiz->hash_table);
		g_free(thiz);
	}

	return;
}

#ifdef IMG_FILTER_PARAMS_TEST
#include <assert.h>

static FilterParamSpec param_specs[] =
{
	{PARAM_TYPE_DOUBLE, "wscale", "width(>1)/width zoom scale.", NULL},
	{PARAM_TYPE_DOUBLE, "hscale", "height(>1)/width zoom scale.", NULL},
	{PARAM_TYPE_NONE}
};

void test(const char* args, double expect_wscale, double expect_hscale)
{
	GError* error = NULL;
	GdkPixbuf* input = NULL;
	const char* filename = "Screenshot.png";
	if((input = gdk_pixbuf_new_from_file(filename, &error)) == NULL)
	{
		fprintf(stderr, "open  %s\n", filename, error->message);
		g_error_free(error);

		return;
	}
	ImgExtraInfo info = {.filename = filename};
	stat(filename, &(info.fstat));
	SET_EXTRA(input, &info);

	ImgFilterParams* thiz = img_filter_params_create(param_specs, input, args);
	double wscale = img_filter_params_get_double(thiz, "wscale", 0);
	double hscale = img_filter_params_get_double(thiz, "hscale", 0);
	assert(wscale == expect_wscale);
	assert(hscale == expect_hscale);
	img_filter_params_destroy(thiz);
	g_object_unref(G_OBJECT(input));

	return;
}

int main(int argc, char* argv[])
{
	g_type_init();

	test("400,200", 400, 200);
	test("0.5,0.5", 0.5, 0.5);
	test("0.5,", 0.5, 0);
	test("%w,%h", 1440, 900);

	return 0;
}
#endif/*IMG_FILTER_PARAMS_TEST*/

