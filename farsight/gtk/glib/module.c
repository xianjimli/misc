#include <assert.h>
#include <glib.h>
#include <gmodule.h>

typedef int (*StrCmp)(const char* str1, const char* str2);

int main(int argc, char* argv[])
{
	GModule*  m = g_module_open("/lib/libc.so.6", 0);

	if(m != NULL)
	{
		StrCmp str_cmp = NULL;
		if(g_module_symbol(m, "strcmp", (gpointer*)&str_cmp))
		{
			g_debug("strcmp=%p\n", str_cmp);
		}

		g_module_close(m);
	}
	else
	{
		g_debug("%s\n", g_module_error());
	}

	return 0;
}
