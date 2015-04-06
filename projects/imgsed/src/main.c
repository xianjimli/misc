/*
 * File:    main.c
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
#include "img_filter_factory.h"

static void show_filter_usage(void* ctx, const char* name)
{
	int i = 0;
	ImgFilter* filter = img_filter_create(name, NULL);

	if(filter != NULL)
	{
		fprintf(stderr, "%s:\n", name);
		for(i = 0; filter->param_specs != NULL && filter->param_specs[i].type != PARAM_TYPE_NONE; i++)
		{
			fprintf(stderr, "	[%d]: %s -- %s", i, filter->param_specs[i].name, filter->param_specs[i].desc);
			if(filter->param_specs[i].type == PARAM_TYPE_ENUM && filter->param_specs[i].options != NULL)
			{
				int j = 0;
				fprintf(stderr, "(");
				for(j = 0; filter->param_specs[i].options[j] != NULL; j++)
				{
					fprintf(stderr, "%s ", filter->param_specs[i].options[j]);
				}
				fprintf(stderr, ")");
			}
			fprintf(stderr, "\n");
			fprintf(stderr, "	     default: ");
			switch(filter->param_specs[i].type)
			{
				case PARAM_TYPE_STRING:
				{
					fprintf(stderr, "%s", filter->param_specs[i].defval.svalue);
					break;
				}
				case PARAM_TYPE_INT:
				{
					fprintf(stderr, "%d", filter->param_specs[i].defval.ivalue);
					break;
				}
				case PARAM_TYPE_DOUBLE:
				{
					fprintf(stderr, "%lf", filter->param_specs[i].defval.dvalue);
					break;
				}
				case PARAM_TYPE_BOOL:
				{
					fprintf(stderr, "%s", filter->param_specs[i].defval.bvalue ? "true" : "false");
					break;
				}
				default:break;
			}
			fprintf(stderr, "\n");
		}
		img_filter_destroy(filter);
	}

	return;
}

static void show_usage(int argc, char* argv[])
{
	fprintf(stderr, "%s filename -filter filterX[arg1,...] -filter filterX[arg1,...] ...\n", argv[0]);
	fprintf(stderr, "Supported filters:\n");
	fprintf(stderr, "===================================================:\n");
	img_filter_foreach(show_filter_usage, NULL);
	fprintf(stderr, "===================================================:\n");
	fprintf(stderr, "Supported variables:\n");
	fprintf(stderr, "===================================================:\n");
	fprintf(stderr, "%%w: the width of the image\n");
	fprintf(stderr, "%%h: the height of the image\n");
	fprintf(stderr, "%%f: the file name of the image\n");
	fprintf(stderr, "%%y: the year of last change.\n");
	fprintf(stderr, "%%m: the month of last change.\n");
	fprintf(stderr, "%%d: the day of last change.\n");
	fprintf(stderr, "===================================================:\n");
	fprintf(stderr, "Example:\n");
	fprintf(stderr, "	%s myimg.png -filter resize[0.5*%%w,0.5*%%h] -filter save[new%%y-%%m-%%d.png]\n", argv[0]);
	return;
}

#define MAX_FILTERS 64
int main(int argc, char* argv[])
{
	int i = 0;
	int filters_nr = 0;
	char* name = NULL;
	char* args = NULL;
	char* end  = NULL;
	const char* filename = argv[1];
	ImgFilter* filters[MAX_FILTERS] ={0};
	GdkPixbuf* input = NULL;
	GError* error = NULL;

	g_type_init();
	g_thread_init(NULL);

	if(argc < 4 || strcmp(argv[1], "--help") == 0)
	{
		show_usage(argc, argv);

		return 0;
	}

	if((input = gdk_pixbuf_new_from_file(filename, &error)) == NULL)
	{
		fprintf(stderr, "open %s failed: %s\n", filename, error->message);
		g_error_free(error);

		return 0;
	}

	for(i = 2; i < argc; i++)
	{
		if(strcmp(argv[i], "-filter") == 0 && (i + 1) < argc)
		{
			name = strdup(argv[i+1]);
			if((args = strchr(name, '[')) != NULL)
			{
				char* end = strrchr(args, ']');
				*args = '\0';
				args++;
				if(end != NULL)
				{
					*end = '\0';
				}
			}

			if(filters_nr < MAX_FILTERS)
			{
				if((filters[filters_nr] = img_filter_create(name, args)) != NULL)
				{
					filters_nr++;
				}
			}
			free(name);
		}
	}

	GdkPixbuf* output = NULL;
	ImgExtraInfo info = {.filename = filename};
	stat(filename, &(info.fstat));

	for(i = 0; i < filters_nr; i++)
	{
		fprintf(stderr, "running filter %s...\n", filters[i]->name);
		
		SET_EXTRA(input, &info);
		if(img_filter_run(filters[i], input, &output) == RET_STOP || output == NULL)
		{
			break;
		}
		g_object_unref(G_OBJECT(input));

		input = output;
		output = NULL;
	}
	
	for(i = 0; i < filters_nr; i++)
	{
		img_filter_destroy(filters[i]);
		filters[i] = NULL;
	}

	return 0;
}

