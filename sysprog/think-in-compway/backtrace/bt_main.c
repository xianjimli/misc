#include <stdio.h>

extern void test(void);

int main(int argc, char* argv[])
{
	test();
	getchar();

	return 0;
}
