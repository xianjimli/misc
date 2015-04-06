#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "typedef.h"

typedef enum _TokenType
{
	TOKEN_NONE = 0,
	TOKEN_KEY,
	TOKEN_VALUE,
	TOKEN_COMMENT,
	TOKEN_GROUP_NAME
}TokenType;

typedef void (*OnTokenFunc)(void* ctx, TokenType type, const char* token);

void parse_ini(const char* str, OnTokenFunc on_token, void* ctx)
{
	enum
	{
		STAT_NONE,
		STAT_IN_KEY,
		STAT_IN_VALUE,
		STAT_IN_COMMENT,
		STAT_IN_GROUP_NAME
	}state = STAT_NONE;

	char* p           = NULL;
	char* temp_str    = NULL;
	const char* token = NULL;

	return_if_fail(str != NULL && on_token != NULL);
	temp_str = strdup(str);
	return_if_fail(temp_str != NULL);

	for(p = temp_str; *p != '\0'; p++)
	{
		switch(state)
		{
			case STAT_NONE:
			{
				switch(*p)
				{
					case ' ':
					case '\t':
					case '\n':break;
					case '[': state = STAT_IN_GROUP_NAME;break;
					case '#': state = STAT_IN_COMMENT;break;
					default:  state = STAT_IN_KEY;break;
				}
				token = p;
				break;
			}
			case STAT_IN_GROUP_NAME:
			{
				if(*p == ']' || *p == '#')
				{
					state = *p == '#' ? STAT_IN_COMMENT : STAT_NONE;
					*p = '\0';
					on_token(ctx, TOKEN_GROUP_NAME, token + 1);
					token = p;
				}
				break;
			}
			case STAT_IN_KEY:
			{
				if(*p == '=')
				{
					*p = '\0';
					state = STAT_IN_VALUE;
					on_token(ctx, TOKEN_KEY, token);
					token = p;
				}
				break;
			}
			case STAT_IN_VALUE:
			{
				if(*p == '\n' || *p == '#')
				{
					state = *p == '#' ? STAT_IN_COMMENT : STAT_NONE;
					*p = '\0';
					on_token(ctx, TOKEN_VALUE, token+1);
					token = p;
				}
				break;
			}
			case STAT_IN_COMMENT:
			{
				if(*p == '\n')
				{
					*p = '\0';
					state = STAT_NONE;
					on_token(ctx, TOKEN_COMMENT, token+1);
				}
			}
			default:break;
		}
	}

	switch(state)
	{
		case STAT_IN_GROUP_NAME: 
		{
			on_token(ctx, TOKEN_GROUP_NAME, token+1);
			break;
		}
		case STAT_IN_KEY:
		{
			on_token(ctx, TOKEN_KEY, token);
			break;
		}
		case STAT_IN_VALUE:
		{
			on_token(ctx, TOKEN_VALUE, token+1);
			break;
		}
		case STAT_IN_COMMENT:
		{
			on_token(ctx, TOKEN_COMMENT, token+1);
			break;
		}
		default:break;
	}

	free(temp_str);

	return;
}

void print_token(void* ctx, TokenType type, const char* token)
{
	switch(type)
	{
		case TOKEN_GROUP_NAME:
		{
			printf("[%s]\n", token);
			break;
		}
		case TOKEN_KEY:
		{
			printf("%s", token);
			break;
		}
		case TOKEN_VALUE:
		{
			printf("=%s\n", token);
			break;
		}
		case TOKEN_COMMENT:
		{
			printf("#%s\n", token);
		}
		default:break;
	}

	return;
}

#define STR_INI1 "[group]\nkey=value#comment\n#comment"

int main(int argc, char* argv[])
{
	parse_ini(STR_INI1, print_token, NULL);

	return 0;
}
