#include <stdio.h>
#include <glib.h>

static void  on_data(gpointer       key,
         gpointer       value,
         gpointer       user_data)
{
	printf("%s: key=%s value=%s\n", __func__, key, value);

	return;
}

int main(int argc, char* argv[])
{
	GHashTable* ht = g_hash_table_new(g_str_hash, g_str_equal);

	g_hash_table_insert(ht, "name", "lixianjing");
	g_hash_table_insert(ht, "gender", "male");
	g_hash_table_insert(ht, "career", "software engineer");

	printf("name=%s\n", g_hash_table_lookup(ht, "name"));
	printf("gender=%s\n", g_hash_table_lookup(ht, "gender"));
	printf("career=%s\n", g_hash_table_lookup(ht, "career"));

	g_hash_table_foreach(ht, on_data, NULL);
	
	g_hash_table_destroy(ht);

	return 0;
}
