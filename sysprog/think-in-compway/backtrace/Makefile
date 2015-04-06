CFLAGS=-g -Wall
all:
	gcc34 $(CFLAGS) bt.c -o bt34
	gcc $(CFLAGS) -DNEW_GCC  bt.c -o bt
	gcc $(CFLAGS) bt_std.c -o bt_std

clean:
	rm -f bt bt34 bt_std bt_so *.so

so:
	gcc -shared $(CFLAGS) -DNEW_GCC bt_so.c -o libbt_so.so
	gcc $(CFLAGS) -L./ -lbt_so bt_main.c -o bt_so

