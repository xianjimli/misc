#include <glib.h>
#include <string.h>
#include <stdio.h>

#define DATA "[boot]\nimage1=boot.img\nimage2=kernel.img"


int main(int argc, char* argv[])
{
	GError* error = NULL;
	GKeyFile* keyfile = g_key_file_new();

	g_key_file_set_list_separator(keyfile, '=');
	g_key_file_load_from_data(keyfile, DATA, strlen(DATA), 0, &error);

	printf("%s=%s\n", g_key_file_get_value(keyfile, "boot", "image1", NULL));

	g_key_file_free(keyfile);


	return 0;
}
