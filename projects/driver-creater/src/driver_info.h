#ifndef DRIVER_H
#define DRIVER_H

#include <glib.h>

typedef struct _Parameter
{
	char* name;
	char* variable;
	char* type;
	char* permission;
}Parameter;

typedef enum _DriverType
{
	DRIVER_TYPE_CHAR = 1,
}DriverType;

typedef struct _DriverInfo
{
	char* name;
	char* author;
	char* email;
	char* description;
	char* license;

	GList* parameters;
	
	DriverType type;	

	/*for parser*/
	char* text;
	int level;
	Parameter* param;

}DriverInfo;

#define SET_STR(var, val) if((var) != NULL) {g_free(var); var = val;}

DriverInfo* driver_info_load(const char* file_name);
DriverInfo* driver_info_new(void);

gboolean driver_info_save(DriverInfo* thiz, const char* file_name);
void driver_info_destroy(DriverInfo* thiz);

#endif/*DRIVER_H*/

