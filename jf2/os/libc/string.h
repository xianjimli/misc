#ifndef STRING_H
#define STRING_H

#include "stdlib.h"

void*  jmemset(void* s, int c, size_t n);
void*  jmemcpy(void* dest, const void* src, size_t n);
int    jmemcmp(const void* s1, const void* s2, size_t n);
char*  jstrcpy(char* dest, const char* src);
char*  jstrncpy(char* dest, const char* src, size_t n);
int    jstrcmp(const char *s1, const char *s2);
int    jstrncmp(const char *s1, const char *s2, size_t n);
size_t jstrlen(const char *s);

#endif/*STRING_H*/

