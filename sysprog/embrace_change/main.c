#include <stdio.h>
#include "dlist.h"
#include <assert.h>


static DListRet print_int(void* data)
{
	printf("%d ", (int)data);

	return DLIST_RET_OK;
}

int main(int argc, char* argv[])
{
	int i = 0;
	int n = 100;
	DList* dlist = dlist_create();

	for(i = 0; i < n; i++)
	{
		assert(dlist_append(dlist, (void*)i) == DLIST_RET_OK);
	}
	for(i = 0; i < n; i++)
	{
		assert(dlist_prepend(dlist, (void*)i) == DLIST_RET_OK);
	}

	dlist_print(dlist, print_int);

	dlist_destroy(dlist);

	return 0;
}

