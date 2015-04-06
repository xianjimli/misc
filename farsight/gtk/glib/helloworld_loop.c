#include <glib.h>

int main(int argc, char* argv[])
{

	GMainLoop* loop = g_main_loop_new(NULL, 0);

	g_main_loop_run(loop);

	return 0;
}
