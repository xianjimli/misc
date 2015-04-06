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
typedef struct _WorkThread
{
	FifoRing* fifo;
	pthread_t tid;
	pthread_cond_t cond;
	pthread_mutex_t mutex;
}WorkThread;

#define MAX_REQUEST 10
#define PORT 		0x1234
#define MAX_THREAD  10

static void* client_handler(void* param)
{
	int data = 0;
	int sock_client = 0;
	WorkThread* thread = (WorkThread*)param;

	while(1)
	{
		if(fifo_ring_pop(thread->fifo, (void**)&sock_client) != RET_OK)
		{
			pthread_cond_wait(&thread->cond, &thread->mutex);
			continue;
		}

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
	int cursor = 0;
	int opt_value = 1;
	int addrlen = sizeof(struct sockaddr_in);
	int sock_client = 0;
	struct sockaddr_in addr_server = {0};
	struct sockaddr_in addr_client = {0};
	int sock_listen = socket(PF_INET, SOCK_STREAM, 0);
	WorkThread threads[MAX_THREAD] = {0};

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

	for(i = 0; i < MAX_THREAD; i++)
	{
		threads[i].fifo = fifo_ring_create(32);
		pthread_cond_init(&threads[i].cond, NULL);
		pthread_mutex_init(&threads[i].mutex, NULL);
		pthread_create(&(threads[i].tid), NULL, client_handler, threads+i);
	}

	for(i = 0; i < MAX_REQUEST; i++)
	{
		if((sock_client = accept(sock_listen, (struct sockaddr*)&addr_client, &addrlen)) < 0)
		{
			break;
		}
		
		fifo_ring_push(threads[cursor].fifo, (void*)sock_client);
		pthread_cond_signal(&threads[i].cond);	
		cursor = (cursor + 1)%MAX_THREAD;
	}
	
	for(i = 0; i < MAX_THREAD; i++)
	{
		fifo_ring_destroy(threads[i].fifo);
		pthread_cond_destroy(&threads[i].cond);
	}
	close(sock_listen);

	return 0;
}
