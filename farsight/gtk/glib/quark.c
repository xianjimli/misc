#include <glib.h>

int main(int argc, char* argv[])
{
	GQuark q = g_quark_from_string("mystring");

	g_debug("%s\n", g_quark_to_string(q));

	return 0;
}
