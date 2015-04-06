#include <stdio.h>

__attribute ((constructor)) void hello_init(void)
{
	printf("%s\n", __func__);

	return;
}

__attribute ((destructor)) void hello_fini(void)
{
	printf("%s\n", __func__);

	return;
}

int main(int argc, char* argv[], char* env[])
{
	printf("Hello World!\n");

	return 0;
}
