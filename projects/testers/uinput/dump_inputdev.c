#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

static void show_event(struct input_event* event)
{
	printf("%d %d %d\n", event->type, event->code, event->value);

	return;
}

int main(int argc, char* argv[])
{
	int grab = 0;
	struct input_event event = {{0}, 0};
	const char* file_name = argc == 2 ? argv[1] : "/dev/input/event4";

	if(argc < 2)
	{
		printf("\nusage: %s device [grab]\nexample:%s /dev/input/event4\n", argv[0], argv[0]);
		printf("-----------------------------------------\n");
		printf("Powered by broncho(www.broncho.cn)\n");
	}

	int fd = open(file_name, O_RDWR);


	if(fd > 0)
	{

		if(argc == 3)
		{
			if(ioctl(fd, EVIOCGRAB, &grab) < 0) 
			{
				return -1;
			}
		}

		while(1)
		{
			int ret = read(fd, &event, sizeof(event));
			if(ret == sizeof(event))
			{
				show_event(&event);
			}
			else
			{
				break;
			}
		}
		close(fd);
	}

	return 0;
}
