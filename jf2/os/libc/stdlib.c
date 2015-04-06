#include "stdlib.h"

static long int jstrtoul_o(const char *nptr, char **endptr)
{
	long int value = 0;
	const char* p = nptr;

	while(*p >= '0' && *p <= '7')
	{
		value = (value << 3) + (*p - '0');
		p++;
	}

	if(endptr != NULL)
	{
		*endptr = (char*)p;
	}

	return value;
}

static long int jstrtoul_d(const char *nptr, char **endptr)
{
	long int value = 0;
	const char* p = nptr;

	while(*p >= '0' && *p <= '9')
	{
		value = ((value  << 3) + (value << 1)) + (*p - '0');
		p++;
	}

	if(endptr != NULL)
	{
		*endptr = (char*)p;
	}

	return value;
	
}

static long int jstrtoul_h(const char *nptr, char **endptr)
{
	int digit = 0;
	long int value = 0;
	const char* p = nptr;

	while(((*p >= '0') && (*p <= '9')) || ((*p >= 'a') && (*p <= 'f')) || ((*p >= 'A') && (*p <= 'F')))
	{
		if(*p >= '0' && *p <= '9')
		{
			digit = *p - '0';
		}
		else if((*p >= 'a' && *p <= 'f'))
		{
			digit = *p - 'a' + 10;
		}
		else 
		{
			digit = *p -'A' + 10;
		}

		value = (value << 4) + digit;
		p++;
	}

	if(endptr != NULL)
	{
		*endptr = (char*)p;
	}

	return value;
}

unsigned long int jstrtoul(const char *nptr, char **endptr, int base)
{
	if(nptr[0] == '0')
	{
		if(nptr[1] == 'x')
		{
			return jstrtoul_h(nptr+2, endptr);
		}
		else
		{
			return jstrtoul_o(nptr+1, endptr);
		}
	}
	else if(base == 16)
	{
		return jstrtoul_h(nptr, endptr);
	}
	else
	{
		return jstrtoul_d(nptr, endptr);
	}
}

long int jstrtol(const char *nptr, char **endptr, int base)
{
	long int value = 0;
	const char* p = nptr;

	if(nptr == NULL) return 0;

	while(*nptr == ' ' || *nptr == '\t') nptr++;

	p = nptr;
	if(*p == '+' || *p == '-')
	{
		p++;
	}

	value = jstrtoul(p, endptr, base);

	return *nptr == '-' ? -value : value;
}

int jatoi(const char* str)
{
	return jstrtol(str, NULL, 0);
}

static int mod(int a, int b)
{
	if(b == 8)
	{
		return a & 0x07;
	}

	if(b == 16)
	{
		return a & 0x0f;
	}

	if(b == 10)
	{
		return a % 10;
	}
	/*FIXME*/
	return 0;
}

static int div(int a, int b)
{
	if(b == 8)
	{
		return a >> 3;
	}
	
	if(b == 16)
	{
		return a >> 4;
	}

	if(b == 10)
	{
		return b / 10;
	}

	return 0;
}

char *jitoa_ex(int v, char* str, int prefix, int base, int upper)
{
	char a = upper ? 'A' : 'a';
	char c = 0;
	char rnum[32];
	char* d = str;
	char* s = rnum;

	base = base == 0 ? 10 : base;

	if(str == NULL)
	{
		return str;
	}
	
	if(v < 0)
	{
		*d++ = '-'; 
		v = -v;
	}

	if(prefix)
	{
		if(base == 16)
		{
			*d++ = '0';
			*d++ = 'x';
		}
		else if(base == 8)
		{
			*d++ = '0';
		}
	}

	for(; v > 0; s++)
	{
		if((c = mod(v, base)) < 10)
		{
			c += '0';
		}
		else
		{
			c = c - 10 + a;
		}

		*s = c;
		v = div(v, base);
	}
	s--;

	for(; s >= rnum; s--, d++)
	{
		*d = *s;
	}
	*d = '\0';

	return str;
}

char *jitoa(int v, char* str, int base)
{
	return jitoa_ex(v, str, 0, base, 0);
}

void raise(void)
{
}
