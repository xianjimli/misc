#include "ini_config.h"

int main(int argc, char* argv[])
{
	IniConfig* ini = ini_config_create("/etc/sysconfig/clock");
	if(ini != NULL)
	{
		printf("current ZONE is %s\n", ini_config_get(ini, DEFAULT_GROUP, "ZONE"));
		ini_config_destroy(ini);
	}

	return 0;
}
