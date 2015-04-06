#include <stdio.h>
#include "dlist.h"
#include <assert.h>

static int cmp_int(void* data, void* ctx)
{
	return (int)data - (int)ctx;
}

static DListRet print_int(void* data)
{
	printf("%d ", (int)data);

	return DLIST_RET_OK;
}

void test1(void)
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

	dlist_print(dlist, print_int);

	dlist_destroy(dlist);

	return;
}

void test2(void)
{
	int data = 0;
	DList* dlist = dlist_create();

	dlist_insert(dlist, 0, (void*)1);
	assert(dlist_get_by_index(dlist, 0, (void**)&data) == DLIST_RET_OK && data == 1);
	dlist_insert(dlist, 0, (void*)2);
	assert(dlist_get_by_index(dlist, 0, (void**)&data) == DLIST_RET_OK && data == 2);
	dlist_insert(dlist, 0, (void*)3);
	assert(dlist_get_by_index(dlist, 0, (void**)&data) == DLIST_RET_OK && data == 3);
	dlist_insert(dlist, 1, (void*)4);
	assert(dlist_get_by_index(dlist, 1, (void**)&data) == DLIST_RET_OK && data == 4);
	dlist_insert(dlist, 4, (void*)5);
	assert(dlist_get_by_index(dlist, 4, (void**)&data) == DLIST_RET_OK && data == 5);
	printf("\n");
	dlist_print(dlist, print_int);
	printf("\n");

	dlist_destroy(dlist);

	return;
}

int main(int argc, char* argv[])
{
	test1();
	test2();

	return 0;
}
