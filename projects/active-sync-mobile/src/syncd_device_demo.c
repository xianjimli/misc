#include <rapi_device_default.h>
#include <rrac_device_default.h>

RapiDevice* rapi_device_demo_create(void)
{
	return rapi_device_default_create();
}

RracDevice* rrac_device_demo_create(void)
{
	return rrac_device_default_create();
}


