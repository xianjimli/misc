#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>
#include <string.h>

int main(int argc, char* argv[])
{
	int i = 0;
	int data = 0;
	int sock_no = 0;
	struct sockaddr_un addr_server = {0};
	
	addr_server.sun_family = PF_LOCAL;
	strncpy (addr_server.sun_path, "/tmp/demo_sock", sizeof (addr_server.sun_path));
	addr_server.sun_path[sizeof (addr_server.sun_path) - 1] = '\0';

	if((sock_no = socket(PF_LOCAL, SOCK_STREAM, 0)) < 0)
	{
		perror("socket");
		
		return EXIT_FAILURE;
	}

	if(connect(sock_no, (struct sockaddr*)&addr_server, sizeof(addr_server)) < 0)
	{
		perror("connect");
		close(sock_no);

		return EXIT_FAILURE;
	}

	data = getpid();

	if(send(sock_no, &data, sizeof(data), 0) == sizeof(data))
	{
		if(recv(sock_no, &data, sizeof(data), 0) == sizeof(data))
		{
			printf("[%d] server pid=%u\n", i, data);
		}
		else
		{
			perror("recv");
		}
	}
	else
	{
		perror("send");
	}

	close(sock_no);

	return 0;
}

