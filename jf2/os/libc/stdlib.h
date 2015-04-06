#ifndef STDLIB_H
#define STDLIB_H

#define NULL (void*)0
typedef unsigned int size_t;

#define va_list void*
#define va_end(arg)
#define va_arg(arg, type)    *(type*)arg; arg = (char*)arg + sizeof(type);
#define va_start(arg, start) arg = (va_list)(((char*)&(start)) + sizeof(start))

int jatoi(const char* str);
long int jstrtol(const char *nptr, char **endptr, int base);
unsigned long int jstrtoul(const char *nptr, char **endptr, int base);

char *jitoa(int v, char* str, int base);
char *jitoa_ex(int v, char* str, int prefix, int base, int upper);

#endif/*STDLIB_H*/

