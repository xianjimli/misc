#include <glib.h>

gboolean idle(gpointer data)
{
	int* n = (int*)data;
	
	g_debug("%s: %d", __func__, *n);

	*n += 1;
	return *n < 100;
}

int main(int argc, char* argv[])
{
	int n = 0;
	GMainLoop* loop = g_main_loop_new(NULL, 0);

	g_idle_add(idle, &n);

	g_main_loop_run(loop);

	return 0;
}
