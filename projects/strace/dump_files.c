/*
 * save write/writev/read/readv to files.
 * Author: Li XianJing <xianjimli@hotmail.com>
 *
 **/

#include <stdio.h>

typedef struct _FileFd
{
	int   fd;
	FILE* fp_r;
	FILE* fp_w;
	char name[260];
}FileFd;

#define MAX_FILES 1024
static FileFd files[MAX_FILES];

int strace_add_file(int fd, const char* name, int pid)
{
	int i = 0;
	char logfile[260] = {0};
	const char* basename = strrchr(name, '/');

	if(fd <= 0 || name == NULL || fd >= MAX_FILES)
	{
		return -1;
	}

	if(basename != NULL)
	{
		basename++;
	}
	else
	{
		basename=name;
	}

	i = fd;
	files[i].fd = fd;
	strcpy(files[i].name, name);

	snprintf(logfile, sizeof(logfile), "/data/%s.%d.%d.r", basename, fd, pid);
	files[i].fp_r = fopen(logfile, "wb+");
	
	snprintf(logfile, sizeof(logfile), "/data/%s.%d.%d.w", basename, fd, pid);
	files[i].fp_w = fopen(logfile, "wb+");

	return 0;
}

int strace_remove_file(int fd)
{
	int i = 0;

	if(fd <= 0 || fd >= MAX_FILES)
	{
		return -1;
	}

	i = fd;
	if(files[i].fd > 0)
	{
		files[i].fd = -1;
		if(files[i].fp_r != NULL)
		{
			fclose(files[i].fp_r);
			files[i].fp_r = NULL;
		}

		if(files[i].fp_w != NULL)
		{
			fclose(files[i].fp_w);
			files[i].fp_w = NULL;
		}
	}

	return -1;
}

int strace_dump_write(int fd, void* buff, size_t len)
{
	if(fd <= 0 || fd >= MAX_FILES)
	{
		return -1;
	}

	if(files[fd].fd != fd)
	{
		strace_add_file(fd, "unknown", 0);
	}

	if(files[fd].fp_w != NULL)
	{
		fwrite(buff, len, 1, files[fd].fp_w);
		fflush(files[fd].fp_w);
	}
	else
	{
		printf("%s: files[fd].fp_w is null.\n", __func__);
	}

	return 0;
}

int strace_dump_read(int fd, void* buff, size_t len)
{
	if(fd <= 0 || fd >= MAX_FILES)
	{
		return -1;
	}
	
	if(files[fd].fd != fd)
	{
		strace_add_file(fd, "unknown", 0);
	}

	if(files[fd].fp_r != NULL)
	{
		fwrite(buff, len, 1, files[fd].fp_r);
		fflush(files[fd].fp_r);
	}
	else
	{
		printf("%s: files[fd].fp_r is null.\n", __func__);
	}

	return 0;
}

#ifdef TEST
int main(int argc, char* argv[])
{
	strace_add_file(1, "test1", 1);
	strace_add_file(10, "test10", 1);
	strace_add_file(100, "test100", 1);
	strace_add_file(1000, "test1000", 1);

	strace_dump_write(1, "aaaa", 4);
	strace_dump_write(10, "aaaa", 4);
	strace_dump_write(100, "aaaa", 4);
	strace_dump_write(1000, "aaaa", 4);
	
	strace_dump_read(1, "aaaa", 4);
	strace_dump_read(10, "aaaa", 4);
	strace_dump_read(100, "aaaa", 4);
	strace_dump_read(1000, "aaaa", 4);
	strace_remove_file(1);
	strace_remove_file(10);
	strace_remove_file(100);
	strace_remove_file(1000);

	return 0;
}
#endif
