#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int g_count;

int main(int argc, char* argv[])
{
	int a;
	char* str = (char*)malloc(100);

	printf("a=%d str=%s\n", a, str);

	return 0;
}
