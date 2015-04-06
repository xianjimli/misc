CFLAGS=-Wall -g -DHAS_LINUX_UINPUT_H
all:
	gcc $(CFLAGS) gat-recorder.c -o gat-recorder
	gcc $(CFLAGS) gat-replayer.c uinput.c -o gat-replayer
	
clean:
	rm -f gat-recorder gat-replayer *.gat
