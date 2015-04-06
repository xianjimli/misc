#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>

#define MAX_REQUEST 10
#define PORT 		0x1234

static void* client_handler(void* param)
{
	int data = 0;
	int sock_client = (int)param;
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

	return NULL;
}

int main(int argc, char* argv[])
{
	int i = 0;
	pthread_t tid = 0;
	pthread_attr_t attr = {0};
	int opt_value = 1;
	int sock_client = 0;
	int addrlen = sizeof(struct sockaddr_in);
	struct sockaddr_in addr_server = {0};
	struct sockaddr_in addr_client = {0};
	int sock_listen = socket(PF_INET, SOCK_STREAM, 0);

	if(sock_listen < 0)
	{
		perror("socket");

		return EXIT_FAILURE;
	}

	addr_server.sin_family = PF_INET;
	addr_server.sin_addr.s_addr = INADDR_ANY;
	addr_server.sin_port =htons(PORT);

    setsockopt(sock_listen, SOL_SOCKET, SO_REUSEADDR, &opt_value, sizeof(opt_value));
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
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, 1);
	for(i = 0; i < MAX_REQUEST; i++)
	{
		if((sock_client = accept(sock_listen, (struct sockaddr*)&addr_client, &addrlen)) < 0)
		{
			break;
		}
	
		pthread_create(&tid, NULL, client_handler, (void*)sock_client);
	}
	pthread_attr_destroy(&attr);
	close(sock_listen);

	return 0;
}
