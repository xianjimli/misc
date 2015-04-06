#include <rrac_lib.h>
#ifndef _RRAC_TEST_DATA_H
#define _RRAC_TEST_DATA_H

#define RRAC_TYPES_NR 4

static inline AsmRet rrac_test_data_init_types(RracRawObjectType types[RRAC_TYPES_NR])
{
	memset(types, 0x00, sizeof(RracRawObjectType) * RRAC_TYPES_NR);
	const char* name = "Ink";
	wstr_from_ascii(types[0].name1, name, strlen(name));
	wstr_from_ascii(types[0].name2, name, strlen(name));
	types[0].id = 10000;
	types[0].count = 1;
	types[0].total_size = 5530;
	types[0].file_time.low = 944217088;
	types[0].file_time.high = 29748172;


	name = "Favorite";
	wstr_from_ascii(types[1].name1, name, strlen(name));
	wstr_from_ascii(types[1].name2, name, strlen(name));
	types[1].id = 10001;
	types[1].count = 39;
	types[1].total_size = 58274;
	types[1].file_time.low = 944217088;
	types[1].file_time.high = 29748172;
	
	name = "Media";
	wstr_from_ascii(types[2].name1, name, strlen(name));
	wstr_from_ascii(types[2].name2, name, strlen(name));
	types[2].id = 10002;
	types[2].count = 1;
	types[2].total_size = 100;
	types[2].file_time.low = 944217088;
	types[2].file_time.high = 29748172;

	name="File";
	wstr_from_ascii(types[3].name1, name, strlen(name));
	wstr_from_ascii(types[3].name2, name, strlen(name));
	types[3].id = 10003;
	types[3].count = 89;
	types[3].total_size = 20909832;
	types[3].file_time.low = 944217088;
	types[3].file_time.high = 29748172;

	return ASM_RET_OK;
}

static inline RracRawObjectTypes* rrac_test_data_get_types(void)
{
	static RracRawObjectType types[RRAC_TYPES_NR] = {0};
	if(types[0].id == 0)
	{
		rrac_test_data_init_types(types);
	}

	RracRawObjectTypes* all_types = (RracRawObjectTypes*)malloc(sizeof(RracRawObjectTypes) 
		+ sizeof(RracRawObjectType) * RRAC_TYPES_NR);
	all_types->nr = RRAC_TYPES_NR;
	memcpy(all_types->types, types, sizeof(RracRawObjectType) * RRAC_TYPES_NR);

	return all_types;
}

static inline RracObject* rrac_test_data_get_object(unsigned int type, unsigned int id, unsigned int data_length, unsigned char data_fill)
{
	RracObject* object = ASM_ALLOC(RracObject, data_length);
	object->type = type;
	object->id = id;
	object->length = data_length;
	memset(object->data, data_fill, data_length);

	return object;
}

#endif/*_RRAC_TEST_DATA_H*/

