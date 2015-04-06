#include <string.h>
#include <stdio.h>
#include <glib.h>

int main(int argc, char* argv[])
{
	const char* p = NULL;
	int read_len  = 0;
	int write_len = 0;
	const char* utf8="中国";
	GError* error = NULL;

	char* locale = g_convert(utf8, strlen(utf8), 
		"GB2312", "UTF-8", &read_len, &write_len, &error);

	if(locale != NULL)
	{
		for(p = utf8; *p != '\0'; p++) printf("%02x ", (int)p[0] & 0xff);
		printf("\n");
		for(p = locale; *p != '\0'; p++) printf("%02x ", (int)p[0] & 0xff);
		printf("\n");
		g_free(locale);
	}
	else
	{
		g_debug("%s\n", error->message);
		g_error_free(error);
	}

	return 0;
}
