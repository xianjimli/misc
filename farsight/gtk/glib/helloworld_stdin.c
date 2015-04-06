#include <glib.h>

gboolean timeout(gpointer data)
{
	int* n = (int*)data;
	
	g_debug("%s: %d", __func__, *n);

	*n += 1;
	return *n < 100;
}

gboolean   stdin_data_available(GIOChannel *source,
	GIOCondition condition,
	gpointer data)
{
	GString str = {0};
	g_io_channel_read_line_string(source, &str, NULL, NULL);

	g_debug("You input: %s", str.str);

	g_free(str.str);

	return TRUE;
}

int main(int argc, char* argv[])
{
	int n = 0;
	GMainLoop* loop = g_main_loop_new(NULL, 0);
	GIOChannel* sin = g_io_channel_unix_new(0);

	g_timeout_add(1000, timeout, &n);
	g_io_add_watch(sin, G_IO_IN, stdin_data_available, NULL);

	g_main_loop_run(loop);

	return 0;
}
