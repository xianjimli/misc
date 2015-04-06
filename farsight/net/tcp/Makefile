CC=gcc
CFLAGS=-g 

all:
	$(CC) $(CFLAGS) server.c -o server
	$(CC) $(CFLAGS) client.c -o client
	$(CC) $(CFLAGS) client_timeo.c -o client_timeo
	$(CC) $(CFLAGS) server_new_thread.c -lpthread -o server_new_thread
	$(CC) $(CFLAGS) server_thread_pool.c -lpthread -o server_thread_pool
	$(CC) $(CFLAGS) server_thread_pool_2.c -lpthread -o server_thread_pool_2
clean:
	rm -f server client client_timeo server_new_thread server_thread_pool server_thread_pool_2
