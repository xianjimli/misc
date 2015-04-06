#include <stdio.h>
#include <string.h>
#include "typedef.h"

typedef void (*OnTokenFunc)(void* ctx, const char* token);

static int parse_totken(const char* str, const char* separators, OnTokenFunc on_token, void* ctx)
{
	enum
	{
		STAT_NONE = 0,
		STAT_IN_SEPARATOR,
		STAT_IN_TOKEN
	}state = STAT_NONE;

	int count = 0;
	char* p           =  NULL;
	char* temp_str    = NULL;
	const char* token = NULL;

	return_val_if_fail(str != NULL && separators != NULL && on_token != NULL, 0);
	temp_str = strdup(str);
	return_val_if_fail(temp_str != NULL, 0);

	for(p = temp_str; *p != '\0'; p++)
	{
		switch(state)
		{
			case STAT_NONE:
			{
				state = strchr(separators, *p) == NULL ? STAT_IN_TOKEN : STAT_IN_SEPARATOR;
				if(state == STAT_IN_TOKEN)
				{
					token = p;
				}
				break;
			}
			case STAT_IN_SEPARATOR:
			{
				state = strchr(separators, *p) == NULL ? STAT_IN_TOKEN : STAT_IN_SEPARATOR;
				if(state == STAT_IN_TOKEN)
				{
					token = p;
				}
				break;
			}
			case STAT_IN_TOKEN:
			{
				if(strchr(separators, *p) != NULL)
				{
					count++;
					state = STAT_IN_SEPARATOR;
					*p = '\0';
					on_token(ctx, token);
				}
			}
			default:break;
		}
	}

	if(state == STAT_IN_TOKEN)
	{
		count++;
		on_token(ctx, token);
	}

	free(temp_str);

	return count;
}

#define SEPARATORS ",.; \t\n\r"
#include <assert.h>

void dump_token(void* ctx, const char* token)
{
	printf("[%d] %s\n", *(int*)ctx, token);
	*(int*)ctx = *(int*)ctx + 1;

	return;
}

int main(int argc, char* argv[])
{
	int i = 0;
	char cwd[260] = {0};
	getcwd(cwd, sizeof(cwd));
	parse_totken(cwd, "/", dump_token, &i);
	i = 0;
	parse_totken(getenv("PATH"), ":", dump_token, &i);
	return 0;
}
