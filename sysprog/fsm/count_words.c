#include <stdio.h>
#include <string.h>
#include "typedef.h"

static int count_words(const char* str, const char* separators)
{
	enum
	{
		STAT_NONE = 0,
		STAT_IN_SEPARATOR,
		STAT_IN_WORD
	}state = STAT_NONE;

	int count = 0;
	const char* p = str;

	return_val_if_fail(str != NULL && separators != NULL, 0);

	for(p = str; *p != '\0'; p++)
	{
		switch(state)
		{
			case STAT_NONE:
			{
				state = strchr(separators, *p) == NULL ? STAT_IN_WORD : STAT_IN_SEPARATOR;
				break;
			}
			case STAT_IN_SEPARATOR:
			{
				state = strchr(separators, *p) == NULL ? STAT_IN_WORD : STAT_IN_SEPARATOR;
				break;
			}
			case STAT_IN_WORD:
			{
				if(strchr(separators, *p) != NULL)
				{
					count++;
					state = STAT_IN_SEPARATOR;
				}
			}
			default:break;
		}
	}

	if(state == STAT_IN_WORD)
	{
		count++;
	}

	return count;
}

#define SEPARATORS ",.; \t\n\r"
#include <assert.h>

int main(int argc, char* argv[])
{
	assert(count_words("", SEPARATORS) == 0);
	assert(count_words("it", SEPARATORS) == 1);
	assert(count_words("it is ", SEPARATORS) == 2);
	assert(count_words("it is cool!", SEPARATORS) == 3);
	assert(count_words("it   is cool!", SEPARATORS) == 3);
	assert(count_words("it is cool!\na words counter.", SEPARATORS) == 6);

	return 0;
}
