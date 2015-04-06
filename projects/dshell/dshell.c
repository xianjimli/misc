#include "client_stdio.h"
#include <sys/ioctl.h>
#include <sys/types.h>
#include <signal.h>

void replace_lr(char* str)
{
	char* p = str;
	while(*p != '\0')
	{
		if(*p == '\r') *p = '\n';
		p++;
	}
}

void ignore_handler(int sig)
{
}

void dshell_run(Client* client, const char* sh)
{
    int shell_to_app[2] = {0};
    int app_to_shell[2] = {0};

	return_if_fail(client != NULL && sh != NULL);

    pipe(shell_to_app);
    pipe(app_to_shell);

	signal(SIGPIPE, ignore_handler);

	int pid = fork();
    if(pid == 0)
    {
        close(shell_to_app[1]);
        close(app_to_shell[0]);

        dup2(shell_to_app[0], STDIN_FILENO);
        dup2(app_to_shell[1], STDOUT_FILENO);

        execl(sh, sh, NULL);
    }
    else
    {
		int err = 0;
		int arg = 1;
		int need_quit = 0;
		int waitfor_shell_data = 0;
    	FILE* in = fdopen(app_to_shell[0], "r");
    	FILE* out = fdopen(shell_to_app[1], "w");
		err = ioctl(app_to_shell[0], FIONBIO, &arg);
        char message[1024] = {0};
        close(shell_to_app[0]);
        close(app_to_shell[1]);

		while(!need_quit)
		{
			int got_data = 0;
			while((got_data = (fgets(message, sizeof(message), in) != NULL)) || waitfor_shell_data > 0)
			{
				if(got_data && client_write(client, message, strlen(message)) <= 0)
				{
					need_quit = 1;
					break;
				}

				if(!got_data)
				{
					sleep(1);
				}
				waitfor_shell_data--;
			}

			if(need_quit) break;

    	    waitfor_shell_data = 0;
    	    strcpy(message, "\n[dshell]#");
    	    client_write(client, message, strlen(message));
    	    memset(message, 0x00, sizeof(message));
			
			if(client_read(client, message, sizeof(message)) > 0)
			{
				replace_lr(message);
	        	if(fputs(message, out) <= 0 || ferror(out))
	        	{
					need_quit = 1;
					printf("%s:%d\n", __func__, __LINE__);
	        		break;
	        	}
    	    	
    	    	fflush(out);
    	    	waitfor_shell_data = 3;
			}
    	}

		kill(pid, SIGTERM);
		fclose(in);
		fclose(out);
    }
	client_destroy(client);
	
	printf("%s exit\n", __func__);
    return;
}

#include "client_sock.h"

void show_usage(int argc, char* argv[])
{
	printf("usage: \n");
	printf("\t%s stdio\n", argv[0]);
	printf("\t%s listen:port\n", argv[0]);
	printf("\t%s connect:server:port\n", argv[0]);

	return;
}

int main(int argc, char* argv[])
{
	Client* client = NULL;
	const char* shell = getenv("SHELL") != NULL ? getenv("SHELL") : "/bin/bash";
	
	if(argc < 2)
	{
		show_usage(argc, argv);
		exit(0);
	}

	if(strncmp(argv[1], "stdio", 5) == 0)
	{
		client = client_stdio_create();
		dshell_run(client, shell);
	}
	else if(strncmp(argv[1], "connect", 6) == 0)
	{
		int port = 0;
		char host[64] = {0};
		sscanf(argv[1], "connect:%[^:]:%d", host, &port);
		printf("connect: %s %d\n", host, port);
		client = client_sock_connect(host, port);
		dshell_run(client, shell);
	}
	else if(strncmp(argv[1], "listen", 6) == 0)
	{
		int sock = 0;
		int port = 0;
		sscanf(argv[1], "listen:%d", &port);
		printf("listen: %d\n", port);	
		sock = sock_listen(port);
		while(1)
		{
			client = client_sock_accept_on_sock(sock);
			if(client == NULL) break;
			dshell_run(client, shell);
		}
		close(sock);
	}

	return 0;
}
