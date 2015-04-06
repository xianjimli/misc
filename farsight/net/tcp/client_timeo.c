#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <sys/select.h>

#define PORT        0x1234
#define HOST        "localhost"

int main(int argc, char* argv[])
{
	int i = 0;
	int data = 0;
	int sock_no = 0;
	fd_set rd_fdset = {0};
	struct timeval timeout = {0};
	struct hostent* hp = NULL;
	struct sockaddr_in addr_server = {0};
	
	if((hp = gethostbyname(HOST)) == NULL)
	{
		perror("gethostbyname");

		return EXIT_FAILURE;
	}

	addr_server.sin_family = PF_INET;
	addr_server.sin_addr = *(struct in_addr*)(hp->h_addr);
	addr_server.sin_port = htons(PORT);

	if((sock_no = socket(PF_INET, SOCK_STREAM, 0)) < 0)
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
		int ret = 0;
		FD_ZERO(&rd_fdset);
		FD_SET(sock_no, &rd_fdset);
		timeout.tv_sec = 3;

		ret = select(sock_no + 1, &rd_fdset, NULL, NULL, &timeout);
		if(ret > 0 && FD_ISSET(sock_no, &rd_fdset))
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
			fprintf(stderr, "select %s\n", ret == 0 ? "timeout" : "error");
		}
	}
	else
	{
		perror("send");
	}

	close(sock_no);

	return 0;
}

