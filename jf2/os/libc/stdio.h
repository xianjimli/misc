#ifndef STDIO_H
#define STDIO_H

#include "stdlib.h"

void jtrace(const char* func, int line, const char* message);
int jprintf(const char *format, ...);
int jsnprintf(char *str, size_t size, const char *format, ...);

#endif/*STDIO_H*/

