#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char* argv[])
{

	int version = 0;
	char name[100] = {0};
	char location[100] = {0};
	char idstr[100] = {0};
	struct input_id id;
	const char* file_name = argc == 2 ? argv[1] : "/dev/input/event4";

	if(argc != 2)
	{
		printf("\nusage: %s device [grab]\nexample:%s /dev/input/event4\n", argv[0], argv[0]);
		printf("-----------------------------------------\n");
		printf("Powered by broncho(www.broncho.cn)\n");

		return 0;
	}

	int fd = open(file_name, O_RDWR);
	if(fd > 0)
	{
		/*android did the follow work.*/
		if(ioctl(fd, EVIOCGVERSION, &version)) 
		{
			return -1;
		}

		if(ioctl(fd, EVIOCGID, &id)) {
			return -1;
		}
		name[sizeof(name) - 1] = '\0';
		location[sizeof(location) - 1] = '\0';
		idstr[sizeof(idstr) - 1] = '\0';
		if(ioctl(fd, EVIOCGNAME(sizeof(name) - 1), &name) < 1) 
		{
			name[0] = '\0';
		}

		if(ioctl(fd, EVIOCGPHYS(sizeof(location) - 1), &location) < 1) 
		{
			location[0] = '\0';
		}
		if(ioctl(fd, EVIOCGUNIQ(sizeof(idstr) - 1), &idstr) < 1) 
		{
			idstr[0] = '\0';
		}

		printf("name: %s\nlocation=%s\nidstr=%s\n", name, location, idstr);
		close(fd);
	}

	return 0;
}
