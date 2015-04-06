#include <stdio.h>

int gcd(int m, int n)
{
	int r = m % n;

	return r == 0 ? n : gcd(n, r);
}

int gcd_loop(int m, int n)
{
	int r = m % n;
	while(r != 0)
	{
		m = n;
		n = r;
		r = m % n;
	}

	return n;
}

#include <assert.h>
int main(int argc, char* argv[])
{
	assert(gcd(10, 2) == 2);
	assert(gcd(2, 10) == 2);
	assert(gcd(64, 16) == 16);

	assert(gcd_loop(10, 2) == 2);
	return 0;
}
