#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>

//////////////////////////////////////////////////
typedef enum _Ret
{
	RET_OK = 0,
	RET_FAIL
}Ret;

typedef struct _FifoRing
{
	int r_cursor;
	int w_cursor;
	size_t length;
	void* data[0];
	
}FifoRing;

#define return_val_if_fail(p, val) if(!(p)) return val;
FifoRing* fifo_ring_create(size_t length)
{
	FifoRing* thiz = NULL;
	
	return_val_if_fail(length > 1, NULL);

	thiz = (FifoRing*)malloc(sizeof(FifoRing) + length * sizeof(void*));

	if(thiz != NULL)
	{
		thiz->r_cursor = 0;
		thiz->w_cursor = 0;
		thiz->length   = length;
	}

	return thiz;
}

Ret fifo_ring_pop(FifoRing* thiz, void** data)
{
	Ret ret = RET_FAIL;
	return_val_if_fail(thiz != NULL && data != NULL, RET_FAIL);

	if(thiz->r_cursor != thiz->w_cursor)
	{
		*data = thiz->data[thiz->r_cursor];
		thiz->r_cursor = (thiz->r_cursor + 1)%thiz->length;

		ret = RET_OK;
	}

	return ret;
}

Ret fifo_ring_push(FifoRing* thiz, void* data)    
{
	int w_cursor = 0;
	Ret ret = RET_FAIL;
	return_val_if_fail(thiz != NULL, RET_FAIL);

	w_cursor = (thiz->w_cursor + 1) % thiz->length;
	
	if(w_cursor != thiz->r_cursor)
	{
		thiz->data[thiz->w_cursor] = data;
		thiz->w_cursor = w_cursor;

		ret = RET_OK;
	}

	return ret;
}

void fifo_ring_destroy(FifoRing* thiz)
{
	if(thiz != NULL)
	{
		free(thiz);
	}

	return;
}

//////////////////////////////////////////////////

#define MAX_REQUEST 10
#define PORT 		0x1234
#define MAX_THREAD  10

typedef struct _ServerInfo
{
	FifoRing* fifo;
	pthread_cond_t cond;
	pthread_mutex_t mutex;
	pthread_t tids[MAX_THREAD];
}ServerInfo;

static void* client_handler(void* param)
{
	int data = 0;
	int sock_client = 0;
	ServerInfo* server_info = (ServerInfo*)param;

	while(1)
	{
		pthread_mutex_lock(&server_info->mutex);
		pthread_cond_wait(&server_info->cond, &server_info->mutex);
		if(fifo_ring_pop(server_info->fifo, (void**)&sock_client) != RET_OK)
		{
		}
		pthread_mutex_unlock(&server_info->mutex);

		if(recv(sock_client, &data, sizeof(data), 0) == sizeof(data))
		{
			printf("client pid=%d\n", data);
			data = pthread_self();
			if(send(sock_client, &data, sizeof(data), 0) != sizeof(data))
			{
				perror("send");
			}
		}
		else
		{
			perror("recv");
		}

		close(sock_client);
	}

	return NULL;
}

int main(int argc, char* argv[])
{
	int i = 0;
	int opt_value = 1;
	int addrlen = sizeof(struct sockaddr_in);
	int sock_client = 0;
	struct sockaddr_in addr_server = {0};
	struct sockaddr_in addr_client = {0};
	int sock_listen = socket(PF_INET, SOCK_STREAM, 0);
	ServerInfo server_info = {0};

	if(sock_listen < 0)
	{
		perror("socket");

		return EXIT_FAILURE;
	}

	addr_server.sin_family = PF_INET;
	addr_server.sin_addr.s_addr = INADDR_ANY;
	addr_server.sin_port =htons(PORT);

    setsockopt(sock_listen, SOL_SOCKET, SO_REUSEADDR, &opt_value,sizeof(opt_value));

	if(bind(sock_listen, (struct sockaddr*)&addr_server, sizeof(addr_server)) < 0)
	{
		perror("bind");

		return EXIT_FAILURE;
	}

	if(listen(sock_listen, 5) < 0)
	{
		perror("listen");

		return EXIT_FAILURE;
	}

	server_info.fifo = fifo_ring_create(256);
	pthread_cond_init(&server_info.cond, NULL);
	pthread_mutex_init(&server_info.mutex, NULL);

	for(i = 0; i < MAX_THREAD; i++)
	{
		pthread_create(&(server_info.tids[i]), NULL, client_handler, &server_info);
	}

	for(i = 0; i < MAX_REQUEST; i++)
	{
		if((sock_client = accept(sock_listen, (struct sockaddr*)&addr_client, &addrlen)) < 0)
		{
			break;
		}
		
		fifo_ring_push(server_info.fifo, (void*)sock_client);
		pthread_cond_signal(&server_info.cond);	
	}
	
	fifo_ring_destroy(server_info.fifo);
	pthread_cond_destroy(&server_info.cond);
	pthread_mutex_destroy(&server_info.mutex);

	close(sock_listen);

	return 0;
}
