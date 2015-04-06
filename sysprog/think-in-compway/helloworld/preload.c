#include <stdio.h>
#include <ctype.h>

int puts(const char *s)
{
	const char* p = s;
	while(*p != '\0') 
	{
		putc(toupper(*p), stdout);
		p++;
	}

	return 0;
}
