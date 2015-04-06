#include <stdio.h>
#include <stdlib.h>
#include <tslib.h>

int main(int argc, char* argv[])
{
	struct tsdev *ts = NULL;
	char*  tsdevice = NULL;
	struct ts_sample samp = {0};
	
	if ((tsdevice = getenv("TSLIB_TSDEVICE")) == NULL) 
	{
		tsdevice = "dev/input/event0";
	}
	ts = ts_open (tsdevice, 0);
	
	if (ts_config(ts)) 
	{
		perror("ts_config");
		exit(1);
	}

	while(1)
	{
		int ret = ts_read(ts, &samp, 1);
		fprintf(stdout, "%ld.%06ld: x=%2d y=%2d p=%4d\n", 
			samp.tv.tv_sec, samp.tv.tv_usec,
			samp.x, samp.y, samp.pressure);
		fflush(stdout);
	}
	ts_close(ts);	

	return 0;
}

