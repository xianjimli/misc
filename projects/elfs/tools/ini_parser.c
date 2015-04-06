/*
 * File:    ini_parser.c
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   ini config parser.
 *
 * Copyright (c) 2009  Li XianJing <xianjimli@hotmail.com>
 *
 * Licensed under the Academic Free License version 2.1
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * History:
 * ================================================================
 * 2009-05-06 Li XianJing <xianjimli@hotmail.com> created
 *
 */
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ini_util.h"
#include "ini_parser.h"

typedef enum _IniStat
{
	STAT_NONE = 0,
	STAT_GROUP,
	STAT_KEY,
	STAT_VALUE,
	STAT_COMMENT
}IniStat;

static IniGroups* ini_parse_internal(char* buffer, char comment_char, char delim_char)
{
	char* p = buffer;
	char* group_start = NULL;
	char* key_start   = NULL;
	char* value_start = NULL;
	IniStat state = STAT_NONE;
	IniGroup*  current_group = NULL;
	IniGroups* groups = ini_groups_create();

	return_val_if_fail(groups != NULL, NULL);

	for(p = buffer; *p != '\0'; p++)
	{
		switch(state)
		{
			case STAT_NONE:
			{
				if(*p == '[')
				{
					state = STAT_GROUP;
					group_start = p + 1;
				}
				else if(*p == comment_char)
				{
					state = STAT_COMMENT;
				}
				else if(!isspace(*p))
				{
					state = STAT_KEY;
					key_start = p;
				}
				break;
			}
			case STAT_GROUP:
			{
				if(*p == ']')
				{
					*p = '\0';
					strtrim(group_start);
					ini_groups_append(groups, group_start);
					current_group = ini_groups_find(groups, group_start);

					state = STAT_NONE;
				}
				break;
			}
			case STAT_COMMENT:
			{
				if(*p == '\n')
				{
					state = STAT_NONE;
					break;
				}
				break;
			}
			case STAT_KEY:
			{
				if(*p == delim_char || (delim_char == ' ' && *p == '\t'))
				{
					*p = '\0';
					state = STAT_VALUE;
					value_start = p+1;
				}
				break;
			}
			case STAT_VALUE:
			{
				if(*p == '\n' || *p == '\r')
				{
					*p = '\0';
					if(current_group == NULL)
					{
						ini_groups_append(groups, DEFAULT_GROUP);
						current_group = ini_groups_find(groups, DEFAULT_GROUP);
					}
					strtrim(key_start);
					strtrim(value_start);
					ini_pairs_append(current_group->pairs, key_start, value_start);
					state = STAT_NONE;
				}
				break;
			}
			default:break;
		}
	}

	switch(state)
	{
		case STAT_GROUP:
		{
			strtrim(group_start);
			ini_groups_append(groups, group_start);
			current_group = ini_groups_find(groups, group_start);
			break;
		}
		case STAT_VALUE:
		{
			if(current_group == NULL)
			{
				ini_groups_append(groups, DEFAULT_GROUP);
				current_group = ini_groups_find(groups, DEFAULT_GROUP);
			}
			strtrim(key_start);
			strtrim(value_start);
			ini_pairs_append(current_group->pairs, key_start, value_start);
			break;
		}
		default:break;
	}

	return groups;
}

IniGroups* ini_parse(const char* file_name, char comment_char, char delim_char)
{
	FILE* fp = NULL;
	struct stat st = {0};
	char* buffer = NULL;
	IniGroups* groups = NULL;
	return_val_if_fail(file_name != NULL, NULL);
	return_val_if_fail(stat(file_name, &st) == 0, NULL);
	fp = fopen(file_name, "r");
	return_val_if_fail(fp != NULL, NULL);
	buffer = (char*)malloc(st.st_size + 1);

	if(buffer == NULL)
	{
		fclose(fp);

		return NULL;
	}
	fread(buffer, 1, st.st_size, fp);
	buffer[st.st_size] = '\0';

	groups = ini_parse_internal(buffer, comment_char, delim_char);
	free(buffer);

	return groups;
}

#ifdef INI_PARSER_TEST
#include <assert.h>
void parser_test1(void)
{
	IniPair* pair = NULL;
	IniGroup* group = NULL;
	char* buffer = strdup("[lixianjing]\nname=lixianjing\ngender=male\n[zhangshan]\nname=zhangshan\ngender=male\nage=100");
	IniGroups* groups = ini_parse_internal(buffer, '#', '=');
	free(buffer);
	ini_groups_save(groups, stdout, '=');
	assert(ini_groups_size(groups) == 2);
	assert((group = ini_groups_find(groups, "lixianjing")) != NULL);
	assert(strcmp(group->name, "lixianjing") == 0);
	assert((pair = ini_pairs_find(group->pairs, "name")) != NULL);
	assert(strcmp(pair->value, "lixianjing") == 0);

	ini_groups_destroy(groups);

	return;
}

void parser_test2(const char* file_name, char comment, char delim)
{
	IniGroups* groups = ini_parse(file_name, comment, delim);
	ini_groups_save(groups, stdout, delim);
	ini_groups_destroy(groups);

	return;
}

int main(int argc, char* argv[])
{
	parser_test1();
	parser_test2("/etc/scim/config", '#', '=');
	parser_test2("/etc/login.defs", '#', ' ');
	parser_test2("/etc/sysconfig/init", '#', '=');
	parser_test2("/etc/sysconfig/clock", '#', '=');

	return 0;
}
#endif/*INI_PARSER_TEST*/

