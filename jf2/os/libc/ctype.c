#include "ctype.h"

int isalnum(int c)
{
	return isalpha(c) || isdigit(c);
}

int isalpha(int c)
{
	return islower(c) || isupper(c);
}

int isascii(int c)
{
	return c > 0 && c < 127;
}

int isblank(int c)
{
	return c < 32;
}

int iscntrl(int c)
{
	return 0;
}

int isdigit(int c)
{
	return c >= '0' && c <= '9';
}

int isgraph(int c)
{
	return 0;
}

int islower(int c)
{
	return c >= 'a' && c <= 'z';
}

int isprint(int c)
{
	return c >= 32 && c < 127;
}

int ispunct(int c)
{
	return 0;
}

int isspace(int c)
{
	return c == ' ' || c == '\t';
}

int isupper(int c)
{
	return c >= 'A' && c <= 'Z';
}

int isxdigit(int c)
{
	return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}

