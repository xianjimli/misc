#include <glib.h>
#include <assert.h>
#include <stdio.h>
#include <gconf/gconf-client.h>


static const char* string_key = "/apps/demo/string";

static void on_notify(GConfClient* client,
                                      guint cnxn_id,
                                      GConfEntry *entry,
                                      gpointer user_data)
{
	g_debug("%s: %s=%s", __func__, entry->key, gconf_value_get_string(entry->value));

	return;
}

void notify_demo(GConfClient* client)
{
	gconf_client_add_dir(client, "/apps/demo", GCONF_CLIENT_PRELOAD_NONE, NULL);

	gconf_client_notify_add(client, string_key, on_notify, NULL, NULL, NULL);
	gconf_client_set_string(client, string_key, "string_new_value", NULL);
	gconf_client_set_string(client, string_key, "string_new_value1", NULL);

	return;
}

int main(int argc, char* argv[])
{
	GConfClient* client = NULL;
	GMainLoop* mainloop = NULL;

	g_type_init();

	client = gconf_client_get_default();

	notify_demo(client);

	mainloop = g_main_loop_new (NULL, FALSE);

	g_main_loop_run (mainloop);
        
	return 0;
}
