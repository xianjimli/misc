#ifndef DLIST_H
#define DLIST_H

typedef struct _DList;
typedef struct _DList DList;

DList* dlist_create(void);
DList* dlist_insert(DList* thiz, int index, int value);
DList* dlist_delete(DList* thiz, int index);
void   dlist_destroy(DList* thiz);

#endif/*DLIST_H*/
