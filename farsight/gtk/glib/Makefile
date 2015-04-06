FLAGS=-g $(shell pkg-config --cflags --libs glib-2.0 gmodule-2.0)
all:
	gcc $(FLAGS) helloworld.c -o helloworld_test
	gcc $(FLAGS) helloworld_loop.c -o helloworld_loop_test
	gcc $(FLAGS) helloworld_timer.c -o helloworld_timer_test
	gcc $(FLAGS) helloworld_idle.c -o helloworld_idle_test
	gcc $(FLAGS) helloworld_stdin.c -o helloworld_stdin_test
	gcc $(FLAGS) list.c -o list_test
	gcc $(FLAGS) hash.c -o hash_test
	gcc $(FLAGS) conv.c -o conv_test
	gcc $(FLAGS) quark.c -o quark_test
	gcc $(FLAGS) keyfile.c -o keyfile_test
	gcc $(FLAGS) module.c -o module_test
clean:
	rm -f *test
