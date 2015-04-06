/*
 * File:    gat-replayer.c
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   GUI auto tester - replayer.
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
 * 2009-10-06 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include <time.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <linux/input.h>
#include <sys/select.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "uinput.h"

#define XMAX 320
#define YMAX 480

void gat_play(const char* filename)
{
	UInput* uinput = NULL;
	struct input_event ievent;
	struct timeval tv = {0};
	int fd = open(filename, O_RDONLY);

	if(fd < 0)
	{
		printf("open %s failed\n", filename);
		return;
	}

	if((uinput = uinput_create(NULL, XMAX, YMAX)) == NULL)
	{
		close(fd);
		return;
	}

	while(read(fd, &ievent, sizeof(ievent)) == sizeof(ievent))
	{
		int wait_time = 0;
		if(tv.tv_sec == 0)
		{
			tv = ievent.time;
			wait_time = 0;
		}
		else
		{
			wait_time = (ievent.time.tv_sec - tv.tv_sec) * 1000000 + (ievent.time.tv_usec - tv.tv_usec);
		}

		tv = ievent.time;
		usleep(wait_time);
		gettimeofday(&ievent.time, NULL);
		printf("type=%d code=%d value=%d\n", ievent.type, ievent.code, ievent.value);
		uinput_report_event(uinput, &ievent);
	}

	close(fd);
	uinput_destroy(uinput);

	return;
}

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		printf("usage: %s [filename]\n", argv[0]);
		printf("-----------------------------------------\n");
		printf("Powered by broncho(www.broncho.cn)\n");

		return 0;
	}

	gat_play(argv[1]);

	return 0;
}

