#include <stdio.h>
#include <unistd.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	int i = 0;
	int fd = 0;
	struct iovec vectors[5] = {0};
	for(i = 0; i < 5; i++)
	{
		vectors[i].iov_base = malloc(100);
		memset(vectors[i].iov_base, 'a'+i, 100);
		vectors[i].iov_len = 100;
	}

	fd = open("./t.txt", O_CREAT|O_RDWR, 0666);
	if(fd > 0)
	{
		writev(fd, vectors, 5);
		lseek(fd, 0, 0);
		readv(fd, vectors, 5);
		close(fd);
	}
	
	for(i = 0; i < 5; i++)
	{
		free(vectors[i].iov_base);
	}
	return 0;
}
