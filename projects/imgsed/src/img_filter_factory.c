/*
 * File:    img_filter_factory.c
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
#include "img_filter_clip.h"
#include "img_filter_save.h" 
#include "img_filter_resize.h"
#include "img_filter_rotate.h"  
#include "img_filter_text.h"
#include "img_filter_factory.h"

typedef struct _FilterCreator
{
	const char* name;
	ImgFilter* (*create)(const char* args);
}FilterCreator;

static FilterCreator filter_creators[] =
{
	{"clip",   img_filter_clip_create}, 
	{"resize",   img_filter_resize_create}, 
	{"rotate", img_filter_rotate_create}, 
	{"text",   img_filter_text_create}, 
	{"save",   img_filter_save_create}, 
};

ImgFilter* img_filter_create(const char* name, const char* args)
{
	int i = 0;
	g_return_val_if_fail(name != NULL, NULL);

	for(i = 0; i < sizeof(filter_creators)/sizeof(filter_creators[0]); i++)
	{
		if(strcmp(filter_creators[i].name, name) == 0)
		{
			return filter_creators[i].create(args);
		}
	}

	return NULL;
}

void img_filter_foreach(VisitFilterFunc visit, void* ctx)
{
	int i = 0;
	g_return_if_fail(visit != NULL);

	for(i = 0; i < sizeof(filter_creators)/sizeof(filter_creators[0]); i++)
	{
		visit(ctx, filter_creators[i].name);
	}

	return;
}

#ifdef IMG_FILTER_FACTORY_TEST
int main(int argc, char* argv[])
{
	
	return 0;
}
#endif/*IMG_FILTER_FACTORY_TEST*/

