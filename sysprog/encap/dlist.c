#include "dlist.h"

typedef struct _DList
{
	struct _DList* next;
	struct _DList* prev;

	int value;
};

DList* dlist_create(void)
{
	return NULL;
}

DList* dlist_node_create(DList* prev, DList* next, int value)
{
}

DList* dlist_insert(DList* thiz, int index, int value)
{
	if(thiz 
}

DList* dlist_delete(DList* thiz, int index);
void   dlist_destroy(DList* thiz);

#endif/*DLIST_H*/
