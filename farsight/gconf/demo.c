#include <glib.h>
#include <assert.h>
#include <stdio.h>
#include <gconf/gconf-client.h>


static const char* string_key = "/apps/demo/string";
static const char* float_key = "/apps/demo/float";
static const char* int_key = "/apps/demo/int";
static const char* bool_key = "/apps/demo/bool";

static const char* list_string_key = "/apps/demo/list_string";
static const char* list_int_key = "/apps/demo/list_int";
static const char* list_bool_key = "/apps/demo/list_bool";

void stress_test(GConfClient* client)
{
	int i = 0;
	int j = 0;
	char key[255] = {0};

	time_t begin = time(0);
	for(i = 0; i < 100; i++)
	{
		for(j = 0; j < 10; j++)
		{
			sprintf(key, "/apps/demo%d/int%d", i, j);
			gconf_client_set_int(client, key, i * j, NULL);
			assert(gconf_client_get_int(client, key, NULL) == (i * j));
		}
	}

	g_debug("%s: cost %lds", __func__, time(0) - begin);

	return;
}

void simple_demo(GConfClient* client)
{
	gconf_client_set_string(client, string_key, "string_value", NULL);
	g_debug("%s=%s", string_key, gconf_client_get_string(client, string_key, NULL));

	gconf_client_set_float(client, float_key, 3.14, NULL);
	g_debug("%s=%f", float_key, gconf_client_get_float(client, float_key, NULL));

	gconf_client_set_int(client, int_key, 123456, NULL);
	g_debug("%s=%d", int_key, gconf_client_get_int(client, int_key, NULL));

	gconf_client_set_bool(client, bool_key, TRUE, NULL);
	g_debug("%s=%d", bool_key, gconf_client_get_bool(client, bool_key, NULL));

	GSList* list_int = g_slist_append(NULL, (gpointer)100); 
	list_int = g_slist_append(list_int, (gpointer)200);
	gconf_client_set_list(client, list_int_key, GCONF_VALUE_INT, list_int, NULL);
	g_slist_free(list_int);

	GSList* list_string = g_slist_append(NULL, "aaa");
	list_string=g_slist_append(list_string, "bbb");
	gconf_client_set_list(client, list_string_key, GCONF_VALUE_STRING, list_string, NULL);
	g_slist_free(list_string);

	GSList* list_bool = g_slist_append(NULL, (gpointer)TRUE);
	list_bool =  g_slist_append(list_bool, FALSE);
	gconf_client_set_list(client, list_bool_key, GCONF_VALUE_BOOL, list_bool, NULL);
	g_slist_free(list_bool);

	return;
}

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

	return;
}

#define STR_GCONF_DAEMON_PATH     "xml:readwrite:/usr/local/share/gconf"
#define STR_GCONF_USER_SHARE_PATH "xml:readwrite:/home/share/.gconf"
#define STR_GCONF_USER_PATH       "xml:readwrite:~/.gconf"

void custom_client_demo(const char* path)
{
	GError* error = NULL;
	GConfEngine* engine = gconf_engine_get_for_address(path, &error);
	
	g_debug("custom_client_demo(%s)", path);
	if(engine != NULL)
	{
		GConfClient* client = gconf_client_get_for_engine(engine);
		if(client != NULL)
		{
			simple_demo(client);
			notify_demo(client);
		}
		else
		{
			g_debug("gconf_client_get_for_engine(%s) failed", path);	
		}
	}
	else
	{
		if(error != NULL)
		{
			g_debug("gconf_engine_get_for_address(%s): %s", path, error->message);
		}
		else
		{
			g_debug("gconf_engine_get_for_address(%s) failed", path);
		}
	}

	return;
}

static gboolean timeout_quit(gpointer user_data)
{
	g_debug("%s", __func__);
	g_main_loop_quit(user_data);

	return FALSE;
}

int main(int argc, char* argv[])
{
	GConfClient* client = NULL;
	GMainLoop* mainloop = NULL;

	g_type_init();

	custom_client_demo(STR_GCONF_DAEMON_PATH);
	custom_client_demo(STR_GCONF_USER_SHARE_PATH);

	client = gconf_client_get_default();

	simple_demo(client);
	notify_demo(client);
	stress_test(client);

	mainloop = g_main_loop_new (NULL, FALSE);

	g_timeout_add(10000, timeout_quit, mainloop);

	g_main_loop_run (mainloop);
        
	return 0;
}
