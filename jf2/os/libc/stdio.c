#include "stdio.h"
#include "string.h"
#include <syscall.h>

typedef int (*PrintSaveFunc)(void* ctx, const char* str, size_t len);

int jvprintf(PrintSaveFunc save, void* ctx, const char *format, va_list arg)
{
	char  num[32];
	const char* p = format;

	if(save == NULL || format == NULL)
	{
		return 0;
	}

	for(p = format; *p != '\0'; p++)
	{
		if(*p == '%')
		{
			switch(p[1])
			{
				case 's':
				{
					const char* str = va_arg(arg, const char*);
					if(str == NULL)
					{
						str = "(null)";
					}
					save(ctx, str, jstrlen(str));

					break;
				}
				case 'd':
				{
					int value = va_arg(arg, int);
					jitoa(value, num, 10);
					save(ctx, num, jstrlen(num));
					break;
				}
				case 'x':
				{
					int value = va_arg(arg, int);
					jitoa(value, num, 16);
					jtrace(__func__, __LINE__, num);
					save(ctx, num, jstrlen(num));
					break;
				}
				case 'X':
				{
					int value = va_arg(arg, int);
					jitoa_ex(value, num, 0, 16, 1);
					save(ctx, num, jstrlen(num));
					break;
				}
				case 'p':
				{
					int value = va_arg(arg, int);
					jitoa_ex(value, num, 1, 16, 0);
					save(ctx, num, jstrlen(num));
					break;
				}
				default:
				{
					save(ctx, p, 1);
					break;
				}
			}
			p++;
		}
		else
		{
			save(ctx, p, 1);
		}
	}
	va_end();

	return 0;
}

typedef struct _StrSaveInfo
{
	char*  buff;
	char*  cursor;
	size_t avail_length;
}StrSaveInfo;

static int str_save(void* ctx, const char* str, size_t len)
{
	StrSaveInfo* info = (StrSaveInfo*)ctx;

	if(info != NULL && str != NULL && len != 0)
	{
		len = len < info->avail_length ? len : info->avail_length;
		jstrncpy(info->cursor, str, len);
		info->cursor += len;
		info->avail_length -= len;
	}

	return 0;
}

int jsnprintf(char *str, size_t size, const char *format, ...)
{
	va_list arg = NULL;
	va_start(arg, format);

	StrSaveInfo info = {.buff = str, .cursor = str, .avail_length = size};

	jvprintf(str_save, &info, format, arg);

	return size - info.avail_length;
}

int jprintf(const char *format, ...)
{
	va_list arg = NULL;
	char str[512];
	va_start(arg, format);

	StrSaveInfo info = {.buff = str, .cursor = str, .avail_length = sizeof(str)};

	jmemset(str, 0x00, sizeof(str));
	jvprintf(str_save, &info, format, arg);
	jtrace(__func__, __LINE__, str);

	return sizeof(str) - info.avail_length;
}

void jtrace(const char* func, int line, const char* message)
{
#ifndef PC
	syscall(SYS_TRACE, (jword_t)func, line, (jword_t)message);
#endif
	return;
}
