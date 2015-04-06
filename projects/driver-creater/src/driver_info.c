#include <expat.h>
#include <stdio.h>
#include "driver_info.h"

static void on_start (void *userData, const XML_Char *name,	const XML_Char **atts)
{
	DriverInfo* thiz = userData;
	
	thiz->level++;

	if(strcmp(name, "parameter") == 0)
	{
		thiz->param = g_new0(Parameter, 1);
	}

	return;
}

static void on_end (void *userData, const XML_Char *name)
{
	DriverInfo* thiz = userData;

	if(thiz->level == 2)
	{
		char** str = NULL;
		if(strcmp(name, "name") == 0)
		{
			str = &thiz->name;
		}
		else if(strcmp(name, "author") == 0)
		{
			str = &thiz->author;
		}
		else if(strcmp(name, "email") == 0)
		{
			str = &thiz->email;
		}
		else if(strcmp(name, "description") == 0)
		{
			str = &thiz->description;
		}
		else if(strcmp(name, "license") == 0)
		{
			str = &thiz->license;
		}

		if(str != NULL)
		{
			*str = thiz->text;
			thiz->text = NULL;
		}
	}
	
	if(thiz->level == 4 && thiz->param != NULL)
	{
		char** str = NULL;
		if(strcmp(name, "name") == 0)
		{
			str = &thiz->param->name;
		}
		else if(strcmp(name, "variable") == 0)
		{
			str = &thiz->param->variable;
		}
		else if(strcmp(name, "type") == 0)
		{
			str = &thiz->param->type;
		}
		else if(strcmp(name, "permission") == 0)
		{
			str = &thiz->param->permission;
		}
		
		if(str != NULL)
		{
			*str = thiz->text;
			thiz->text = NULL;
		}

	}
	
	if(strcmp(name, "parameter") == 0)
	{
		thiz->parameters = g_list_append(thiz->parameters, thiz->param);
		thiz->param = NULL;
	}

	thiz->level--;

	return;
}

static void on_text(void *userData, const XML_Char *s,	int len)
{
	DriverInfo* thiz = userData;

	if(thiz->text != NULL)
	{
		g_free(thiz->text);
	}
	thiz->text = g_strndup(s, len);

	return;
}

static void driver_info_parse(DriverInfo* thiz, char* buffer, size_t length)
{
	XML_Parser parser = XML_ParserCreate(NULL);
	XML_SetUserData(parser, thiz);
	XML_SetElementHandler(parser, on_start, on_end);
	XML_SetCharacterDataHandler(parser, on_text);
    XML_Parse(parser, buffer, length, TRUE);
	XML_ParserFree(parser);

	return;
}

DriverInfo* driver_info_load(const char* file_name)
{
	char* buffer = NULL;
	size_t length = 0;
	DriverInfo* thiz = NULL;

	if(g_file_get_contents(file_name, &buffer, &length, NULL))
	{
		if((thiz = driver_info_new()) != NULL)
		{
			driver_info_parse(thiz, buffer, length);
		}
		g_free(buffer);
	}

	return thiz;
}

DriverInfo* driver_info_new(void)
{
	DriverInfo* thiz = g_new0(DriverInfo, 1);

	return thiz;
}

static gboolean driver_info_dump_tag(DriverInfo* thiz, FILE* fp, const char* key, const char* value)
{
	if(value != NULL)
	{
		fprintf(fp, "<%s>%s</%s>\n", key, value, key);
	}

	return TRUE;
}

static gboolean driver_info_dump(DriverInfo* thiz, FILE* fp)
{
	fprintf(fp, "<driver>\n");
	driver_info_dump_tag(thiz, fp, "name", thiz->name);
	driver_info_dump_tag(thiz, fp, "author", thiz->author);
	driver_info_dump_tag(thiz, fp, "email", thiz->email);
	driver_info_dump_tag(thiz, fp, "description", thiz->description);
	driver_info_dump_tag(thiz, fp, "license", thiz->license);

	if(thiz->parameters != NULL)
	{
		GList* iter = NULL;
		Parameter* param = NULL;
		fprintf(fp, "<parameters>\n");
		for(iter = thiz->parameters; iter != NULL; iter = g_list_next(iter))
		{
			if((param = (Parameter*)iter->data) != NULL)
			{
				fprintf(fp, "<parameter>\n");
				driver_info_dump_tag(thiz, fp, "name", param->name);
				driver_info_dump_tag(thiz, fp, "variable", param->variable);
				driver_info_dump_tag(thiz, fp, "type", param->type);
				driver_info_dump_tag(thiz, fp, "permission", param->permission);
				fprintf(fp, "</parameter>\n");
			}
			
		}
		fprintf(fp, "</parameters>\n");
	}
	fprintf(fp, "</driver>\n");

	return TRUE;
}

gboolean driver_info_save(DriverInfo* thiz, const char* file_name)
{
	FILE* fp = NULL;
	g_return_val_if_fail(thiz != NULL && file_name != NULL, FALSE);

	if((fp = fopen(file_name, "w+")) != NULL)
	{
		driver_info_dump(thiz, fp);
		fclose(fp);
	}

	return TRUE;
}

void driver_info_destroy(DriverInfo* thiz)
{
	if(thiz != NULL)
	{
		SET_STR(thiz->name, NULL);
		SET_STR(thiz->author, NULL);
		SET_STR(thiz->email, NULL);
		SET_STR(thiz->description, NULL);
		SET_STR(thiz->license, NULL);

		g_free(thiz);
	}
}

#ifdef DRIVER_INFO_TEST
int main(int argc, char* argv[])
{
	DriverInfo* thiz = driver_info_load(argv[1]);
	driver_info_save(thiz, "temp.xml");
	driver_info_destroy(thiz);

	return 0;
}
#endif/*DRIVER_INFO_TEST*/
