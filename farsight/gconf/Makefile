FLAGS=$(shell pkg-config --cflags --libs gconf-2.0)
all:
	gcc -g -Wall $(FLAGS) demo.c -o demo
	gcc -g -Wall $(FLAGS) getset.c -o getset
	gcc -g -Wall $(FLAGS) notify.c -o notify
clean:
	rm -f demo getset notify
