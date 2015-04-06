CFLAGS=$(shell pkg-config --cflags --libs gtk+-2.0)
all:
	gcc -g $(CFLAGS) pango_test.c -o pango_test
clean:
	rm -f pango_test

