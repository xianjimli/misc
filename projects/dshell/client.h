
#include "typedef.h"

#ifndef DSH_CLIENT_H
#define DSH_CLIENT_H

struct _Client;
typedef struct _Client Client;

typedef int  (*ClientReadFunc)(Client* thiz, char* buff, size_t length);
typedef int  (*ClientWriteFunc)(Client* thiz,const char* buff, size_t length);
typedef void (*ClientDestroyFunc)(Client* thiz);

struct _Client
{
	ClientReadFunc     read;
	ClientWriteFunc    write;
	ClientDestroyFunc  destroy;

	char priv[0];
};

static inline int client_read(Client* thiz, char* buff, size_t length)
{
	return_val_if_fail(thiz != NULL && thiz->read != NULL, -1)

	return thiz->read(thiz, buff, length);
}

static inline int client_write(Client* thiz,const char* buff, size_t length)
{
	return_val_if_fail(thiz != NULL && thiz->write != NULL, -1);

	return thiz->write(thiz, buff, length);
}

static inline void client_destroy(Client* thiz)
{
	return_if_fail(thiz != NULL && thiz->destroy != NULL);

	thiz->destroy(thiz);

	return;
}

#endif/*DSH_CLIENT_H*/


