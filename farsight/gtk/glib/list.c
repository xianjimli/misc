#include <stdio.h>
#include <glib.h>

int main(int argc, char* argv[])
{
	GList* list = g_list_alloc();

	list = g_list_append(list, (gpointer)100);
	list = g_list_prepend(list, (gpointer)200);
	list = g_list_insert(list, (gpointer)300, 1);

	GList* iter = g_list_first(list);
	for(; iter != NULL; iter = g_list_next(iter))
	{
		printf("%d ", iter->data);
	}

	g_list_free(list);

	return 0;
}
