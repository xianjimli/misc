all:
	gcc -g -DPC ctype.c  stdio.c  stdlib.c  string.c  test.c -o test
clean:
	rm -f test
