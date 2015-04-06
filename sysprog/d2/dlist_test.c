#include <stdio.h>
#include "dlist.h"
#include <assert.h>

static int cmp_int(void* data, void* ctx)
{
	return (int)data - (int)ctx;
}

static DListRet print_int(void* data, void* ctx)
{
	printf("%d ", (int)data);

	return DLIST_RET_OK;
}

int main(int argc, char* argv[])
{
	int i = 0;
	int n = 100;
	int data = 0;
	DList* dlist = dlist_create();

	for(i = 0; i < n; i++)
	{
		assert(dlist_append(dlist, (void*)i) == DLIST_RET_OK);
		assert(dlist_get_by_index(dlist, i, (void**)&data) == DLIST_RET_OK);
		assert(data == i);
		assert(dlist_set_by_index(dlist, i, (void*)(2*i)) == DLIST_RET_OK);
		assert(dlist_get_by_index(dlist, i, (void**)&data) == DLIST_RET_OK);
		assert(data == 2*i);
		assert(dlist_length(dlist) == (i + 1));
		assert(dlist_set_by_index(dlist, i, (void*)i) == DLIST_RET_OK);
		assert(dlist_find(dlist, cmp_int, (void*)i) == i);
	}

	for(i = 0; i < n; i++)
	{
		assert(dlist_get_by_index(dlist, 0, (void**)&data) == DLIST_RET_OK);
		assert(data == (i));
		assert(dlist_length(dlist) == (n-i));
		assert(dlist_delete(dlist, 0) == DLIST_RET_OK);
	}
	
	assert(dlist_length(dlist) == 0);

	for(i = 0; i < n; i++)
	{
		assert(dlist_prepend(dlist, (void*)i) == DLIST_RET_OK);
		assert(dlist_get_by_index(dlist, 0, (void**)&data) == DLIST_RET_OK);
		assert(data == i);
		assert(dlist_set_by_index(dlist, 0, (void*)(2*i)) == DLIST_RET_OK);
		assert(dlist_get_by_index(dlist, 0, (void**)&data) == DLIST_RET_OK);
		assert(data == 2*i);
		assert(dlist_length(dlist) == (i + 1));
		assert(dlist_set_by_index(dlist, 0, (void*)i) == DLIST_RET_OK);
	}

	dlist_foreach(dlist, print_int, NULL);

	dlist_destroy(dlist);

	return 0;
}

