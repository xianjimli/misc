#include <stdlib.h>

void *jmemset(void *s, int c, size_t n)
{
	if(s != NULL)
	{
		size_t i = 0;

		for(i = 0; i < n; i++)
		{
			((char*)s)[i] = (char)c;
		}
	}

	return s;
}

void *jmemcpy(void *dest, const void *src, size_t n)
{
	if(dest != NULL && src != NULL)
	{
		size_t i = 0;
		for(i = 0; i < n; i++)
		{
			((char*)dest)[i] = ((char*)src)[i];
		}
	}

	return dest;
}

int jmemcmp(const void *s1, const void *s2, size_t n)
{
	size_t i = 0;
	if(s1 == NULL) return -1;
	if(s2 == NULL) return 1;
	if(s1 == s2) return 0;

	for(i = 0; i < n; i++)
	{
		if(((char*)s1)[i] != ((char*)s2)[i])
		{
			return ((char*)s1)[i] - ((char*)s2)[i];
		}
	}

	return ((char*)s1)[i] - ((char*)s2)[i];
}

char *jstrcpy(char *dest, const char *src)
{
	char* d = dest;
	const char* s = src;
	
	if(dest == NULL || src == NULL)
	{
		return dest;
	}

	for(; *s; s++, d++)
	{
		*d = *s;
	}
	*d = '\0';

	return dest;
}

char* jstrncpy(char* dest, const char* src, size_t n)
{
	char* d = dest;
	const char* s = src;
	size_t i = 0;

	if(dest == NULL || src == NULL || n == 0)
	{
		return dest;
	}

	for(; *s && i < n; s++, d++, i++)
	{
		*d = *s;
	}
	
	*d = '\0';
	for(; i < n; i++)
	{
		*d = '\0';
	}

	return dest;
}

int jstrcmp(const char *s1, const char *s2)
{
	if(s1 == NULL || s2 == NULL)
	{
		return s1 - s2;
	}

	for(; *s1 != '\0' && *s2 != '\0'; s1++, s2++)
	{
		if(*s1 != *s2)
		{
			return *s1 - *s2;
		}
	}

	return *s1 - *s2;
}

int jstrncmp(const char *s1, const char *s2, size_t n)
{
	if(s1 == NULL || s2 == NULL)
	{
		return s1 - s2;
	}

	for(; *s1 != '\0' && *s2 != '\0' && n > 0; s1++, s2++, n--)
	{
		if(*s1 != *s2)
		{
			return *s1 - *s2;
		}
	}

	return *s1 - *s2;
}

size_t jstrlen(const char *s)
{
	size_t n = 0;

	if(s == NULL || *s == '\0')
	{
		return 0;
	}

	while(s[n]) n++;

	return n;
}

