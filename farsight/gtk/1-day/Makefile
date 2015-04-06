all:
	gcc -g c-inheritance.c -o inheritance_test
	gcc -g c-virtual.c -o virtual_test
	gcc -g foo_object.c main.c $(shell pkg-config --cflags --libs "glib-2.0 gobject-2.0") -o foo_test

clean:
	rm -f *_test
