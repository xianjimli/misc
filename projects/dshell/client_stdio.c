#include "client_stdio.h"

static int client_stdio_read(Client* thiz, char* buff, size_t length)
{
	fgets(buff, length, stdin);

	return strlen(buff);
}

static int client_stdio_write(Client* thiz,const char* buff, size_t length)
{
	int ret = fwrite(buff, 1, length, stdout);
	fflush(stdout);

	return ret;
}

static void client_stdio_destroy(Client* thiz)
{
	free(thiz);

	return;
}

Client* client_stdio_create(void)
{
	Client* thiz = (Client*)calloc(sizeof(Client), 1);

	if(thiz != NULL)
	{
		thiz->read      = client_stdio_read;
		thiz->write     = client_stdio_write;
		thiz->destroy   = client_stdio_destroy;
	}

	return thiz;
}

