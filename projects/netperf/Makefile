CFLAGS=-I./ -g -DLINUX 

netperf: httpclient.c  mysocket.c
	gcc $(CFLAGS) httpclient.c  mysocket.c -lpthread -o netperf

clean:
	rm -f *.o *.so netperf

