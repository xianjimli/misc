#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>

#define MAX_REQUEST 10
#define PORT 		0x1234

int main(int argc, char* argv[])
{
	int i = 0;
	int data = 0;
	int addrlen = sizeof(struct sockaddr_un);
	int sock_client = 0;
	struct sockaddr_un addr_server = {0};
	struct sockaddr_un addr_client = {0};
	int sock_listen = socket(PF_LOCAL, SOCK_STREAM, 0);

	if(sock_listen < 0)
	{
		perror("socket");

		return EXIT_FAILURE;
	}

	unlink("/tmp/demo_sock");
	addr_server.sun_family = PF_LOCAL;
	strncpy (addr_server.sun_path, "/tmp/demo_sock", sizeof (addr_server.sun_path));
	addr_server.sun_path[sizeof (addr_server.sun_path) - 1] = '\0';

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

	for(i = 0; i < MAX_REQUEST; i++)
	{
		if((sock_client = accept(sock_listen, (struct sockaddr*)&addr_client, &addrlen)) < 0)
		{
			break;
		}
		
		if(recv(sock_client, &data, sizeof(data), 0) != sizeof(data))
		{
			break;
		}

		printf("[%d] client pid=%d\n", i, data);
		data = getpid();

		if(send(sock_client, &data, sizeof(data), 0) != sizeof(data))
		{
			break;
		}
		close(sock_client);
	}
	close(sock_listen);

	return 0;
}
