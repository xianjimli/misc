/*
 * demo.c
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

#include <stdio.h>
#include "lrc.h"

int main(int argc, char* argv[])
{
	Lrc* thiz = NULL;
	LrcIdTagIter id_iter = {0};
	LrcTimeTagIter time_iter = {0};
	const char* key = NULL;

	if(argc != 2)
	{
		printf("usage: %s lrcfile\n", argv[0]);
		return -1;
	}
	
	thiz = lrc_new_from_file(argv[1]);
	if(thiz != NULL)
	{
		id_iter = lrc_get_id_tags(thiz);
		while(lrc_id_tag_iter_has_next(&id_iter))
		{
			id_iter = lrc_id_tag_iter_next(&id_iter);
		}
		while(lrc_id_tag_iter_has_prev(&id_iter))
		{
			id_iter = lrc_id_tag_iter_prev(&id_iter);
		}
		
		while(!lrc_id_tag_iter_is_null(&id_iter))
		{
			LrcIdTagIter iter1 = {0};
			printf("[%s:%s]\n", lrc_id_tag_iter_get_key(&id_iter),
					lrc_id_tag_iter_get_value(&id_iter));
	
#if 1
			//FIXME: crash
			key = lrc_id_tag_iter_get_key(&id_iter);
			iter1 = lrc_get_id_tag_get_by_key(thiz, key);

			LRC_ASSERT(lrc_id_tag_iter_get_value(&iter1) == lrc_id_tag_iter_get_value(&id_iter));
			
#endif			
			id_iter = lrc_id_tag_iter_next(&id_iter);
		}

		time_iter = lrc_get_time_tags(thiz);
		while(lrc_time_tag_iter_has_next(&time_iter))
		{
			time_iter = lrc_time_tag_iter_next(&time_iter);
		}
		while(lrc_time_tag_iter_has_prev(&time_iter))
		{
			time_iter = lrc_time_tag_iter_prev(&time_iter);
		}

		while(!lrc_time_tag_iter_is_null(&time_iter))
		{
			LrcTimeTagIter iter = {0};
			size_t start_time = lrc_time_tag_iter_get_start_time(&time_iter);
			
			printf("[%d:%02d.%02d] %s\n", start_time/6000, (start_time%6000)/100, (start_time%6000)%100,
				lrc_time_tag_iter_get_lrc(&time_iter));

			iter = lrc_get_time_tag_by_time(thiz, start_time + 1);
		
			LRC_ASSERT(!lrc_time_tag_iter_is_null(&iter));
			LRC_ASSERT(lrc_time_tag_iter_get_lrc(&time_iter) == lrc_time_tag_iter_get_lrc(&iter));

			time_iter = lrc_time_tag_iter_next(&time_iter);
		}
	
		lrc_save(thiz, "jim.lrc");
		
		lrc_destroy(thiz);
	}
	
	return 0;
}
