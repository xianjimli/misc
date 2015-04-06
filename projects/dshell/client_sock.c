#include "util.h"
#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "client_sock.h"

typedef struct _PrivInfo
{
	int sock;
}PrivInfo;

static int client_sock_read(Client* thiz, char* buff, size_t length)
{
	int ret = 0;
	PrivInfo* info = (PrivInfo*)thiz->priv;
	ret = recv(info->sock, buff, length, 0);

	return ret;
}

static int client_sock_write(Client* thiz,const char* buff, size_t length)
{
	PrivInfo* info = (PrivInfo*)thiz->priv;
	int ret = send(info->sock, buff, length, 0);

	return ret;
}

static void client_sock_destroy(Client* thiz)
{
	if(thiz != NULL)
	{
		PrivInfo* info = (PrivInfo*)thiz->priv;
		close(info->sock);
		free(thiz);
	}

	return;
}

Client* client_sock_create(int sock)
{
	Client* thiz = (Client*)calloc(sizeof(Client) + sizeof(PrivInfo), 1);

	if(thiz != NULL)
	{
		PrivInfo* info = (PrivInfo*)thiz->priv;
		thiz->read = client_sock_read;
		thiz->write     = client_sock_write;
		thiz->destroy   = client_sock_destroy;

		info->sock = sock;
	}

	return thiz;
}

Client* client_sock_connect(const char* host, int port)
{
	int sock = 0;
	struct hostent* hp = NULL;
	struct sockaddr_in addr_server = {0};
	
	if((hp = gethostbyname(host)) == NULL)
	{
		perror("gethostbyname");

		return NULL;
	}

	addr_server.sin_family = PF_INET;
	addr_server.sin_addr = *(struct in_addr*)(hp->h_addr);
	addr_server.sin_port = htons(port);

	if((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket");
		
		return NULL;
	}

	if(connect(sock, (struct sockaddr*)&addr_server, sizeof(addr_server)) < 0)
	{
		perror("connect");
		close(sock);

		return NULL;
	}

	return client_sock_create(sock);
}

Client* client_sock_accept(int port)
{
	int listen_sock =  sock_listen(port);
	
	return client_sock_accept_on_sock(listen_sock);
}

Client* client_sock_accept_on_sock(int listen_sock)
{
	int sock_client = 0;
	int addrlen = sizeof(struct sockaddr_in);
	struct sockaddr_in addr_client = {0};

	if((sock_client = accept(listen_sock, (struct sockaddr*)&addr_client, &addrlen)) < 0)
	{
		perror("accept");
		close(listen_sock);

		return NULL;
	}

	return client_sock_create(sock_client);
}

