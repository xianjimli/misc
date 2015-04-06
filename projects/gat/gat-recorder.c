/*
 * File:    gat-recorder.c
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   GUI auto tester - recorder.
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

#define MAX_FDS 16
static int input_nr = 0;
static int input_fds[MAX_FDS] = {0};

static void open_devices(void)
{
	char filename[260] = {0};
	struct dirent* iter = NULL;
	DIR* dir = opendir("/dev/input");

	while((iter = readdir(dir)) != NULL)
	{
		if(iter->d_name[0] == '.') continue;
		if(!(iter->d_type & DT_CHR)) continue;

		snprintf(filename, sizeof(filename), "/dev/input/%s", iter->d_name);
		input_fds[input_nr] = open(filename, O_RDONLY);
		if(input_fds[input_nr] > 0)
		{
			input_nr++;
			printf("add device %s\n", filename);
		}
		else
		{
			printf("open device %s failed.\n", filename);
		}
	}

	closedir(dir);

	return;
}

static void close_devices(void)
{
	while(input_nr > 0)
	{
		close(input_fds[input_nr]);
		input_fds[input_nr] = -1;
		input_nr--;
	}

	return;
}

static void gat_record(const char* prefix)
{
	int i = 0;
	int mfd = 0;
	int ret = 0;
	fd_set fdset;
	FILE* fp = NULL;
	time_t start = time(0);
	int wait_time = 30000;
	struct timeval tv = {0};
	struct input_event ievent;
	char filename[260] = {0};
	struct tm* t = localtime(&start);

	if(input_nr == 0)
	{
		return;
	}

	snprintf(filename, sizeof(filename), "%s-%02d-%02d-%02d.gat",
		prefix, t->tm_hour, t->tm_min, t->tm_sec);

	if((fp = fopen(filename, "wb+")) == NULL)
	{
		printf("open output file %s failed.\n", filename);

		return;
	}

	
	FD_ZERO(&fdset);
	for(i = 0; i < input_nr; i++)
	{
		FD_SET(input_fds[i], &fdset);
		if(mfd < input_fds[i]) 
		{
			mfd = input_fds[i];
		}
	}
	
	while(1)
	{
		tv.tv_sec = wait_time/1000;
		tv.tv_usec = (wait_time%1000) * 1000;
		ret = select(mfd + 1, &fdset, NULL, NULL, &tv);
		
		if(ret == 0) continue;
		if(ret < 0) break;

		for(i = 0; i < input_nr; i++)
		{
			if(FD_ISSET(input_fds[i], &fdset))
			{
				ret = read(input_fds[i], &ievent, sizeof(ievent));
				gettimeofday(&ievent.time, NULL);
				assert(ret == sizeof(ievent));
				fwrite(&ievent, sizeof(ievent), 1, fp);
				fflush(fp);
				printf(".");
			}
		}
	}

	fclose(fp);

	return;
}

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		printf("usage: %s [filename prefix]\n", argv[0]);
		printf("-----------------------------------------\n");
		printf("Powered by broncho(www.broncho.cn)\n");

		return 0;
	}
	open_devices();
	gat_record(argv[1]);
	close_devices();

	return 0;
}

