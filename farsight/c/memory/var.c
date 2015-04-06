#include <stdio.h>
#include "var.h"

int ecount = 10;
static int scount = 100;

void print_var(void)
{
	int i = 0;
	static int local_count = 1000;

	printf("======================================\n");
	for(i = 0; i < ecount; i++)
	{
		local_count++;
		printf("i=%d ecount=%d scount=%d local_count=%d\n", i, ecount, scount, local_count);
	}

	return;
}
