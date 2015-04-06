#include <glib.h>
#include <assert.h>
#include <stdio.h>
#include <gconf/gconf-client.h>


static const char* string_key = "/apps/demo/string";
static const char* float_key = "/apps/demo/float";
static const char* int_key = "/apps/demo/int";

void simple_demo(GConfClient* client)
{
	gconf_client_set_string(client, string_key, "string_value", NULL);
	g_debug("%s=%s", string_key, gconf_client_get_string(client, string_key, NULL));

	gconf_client_set_float(client, float_key, 3.14, NULL);
	g_debug("%s=%f", float_key, gconf_client_get_float(client, float_key, NULL));

	gconf_client_set_int(client, int_key, 123456, NULL);
	g_debug("%s=%d", int_key, gconf_client_get_int(client, int_key, NULL));


	return;
}

int main(int argc, char* argv[])
{
	GConfClient* client = NULL;
	GMainLoop* mainloop = NULL;

	g_type_init();

	client = gconf_client_get_default();

	simple_demo(client);

	mainloop = g_main_loop_new (NULL, FALSE);

	g_main_loop_run (mainloop);
        
	return 0;
}
