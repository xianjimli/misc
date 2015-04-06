all:
	gcc -g helloworld.c -o helloworld
	gcc -g -static helloworld.c -o helloworld_static
	gcc -g helloworld.1.c -o helloworld_1
	gcc -g helloworld.2.c -o helloworld_2
	gcc -g helloworld.3.c -o helloworld_3
	gcc -g helloworld.4.c -o helloworld_4
	gcc -g helloworld.5.c -o helloworld_5
	gcc -g helloworld.8.c -o helloworld_8
	gcc -g helloworld.9.c -o helloworld_9
	gcc -g helloworld.10.c -o helloworld_10
	gcc -g -shared preload.c -o libpreload.so

clean:
	rm -f helloworld_* helloworld *.so

