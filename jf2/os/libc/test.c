#include "assert.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

void jatoi_test(void)
{
	char* endptr = NULL;
	assert(jatoi("0x100") == 0x100);
	assert(jatoi("0100") == 0100);
	assert(jatoi("100") == 100);

	assert(jatoi("+0x100") == 0x100);
	assert(jatoi("+0100") == 0100);
	assert(jatoi("+100") == 100);
	
	assert(jatoi("-0x100") == -0x100);
	assert(jatoi("-0100") == -0100);
	assert(jatoi("-100") == -100);
	
	assert(jatoi("   0x100") == 0x100);
	assert(jatoi("  0100") == 0100);
	assert(jatoi("	100") == 100);
	
	assert(jatoi("   0x100x") == 0x100);
	assert(jatoi("  0100x") == 0100);
	assert(jatoi("	100x") == 100);
	
	assert(jatoi("   0x100h") == 0x100);
	assert(jatoi("  01008") == 0100);
	assert(jatoi("	100a") == 100);
	
	assert(jstrtol("   0x100h", &endptr, 0) == 0x100 && *endptr == 'h');
	assert(jstrtol("  01008", &endptr, 0) == 0100 && *endptr == '8');
	assert(jstrtol("	100a", &endptr, 0) == 100 && *endptr == 'a');

	return;
}

void jitoa_test(void)
{
	char num[32];

	assert(jstrcmp(jitoa(-100, num, 10), "-100") == 0);
	assert(jstrcmp(jitoa(1234, num, 10), "1234") == 0);
	assert(jstrcmp(jitoa(10, num, 10), "10") == 0);
	
	assert(jstrcmp(jitoa(-100, num, 0), "-100") == 0);
	assert(jstrcmp(jitoa(1234, num, 0), "1234") == 0);
	assert(jstrcmp(jitoa(10, num, 0), "10") == 0);
	
	assert(jstrcmp(jitoa(-0x100, num, 16), "-100") == 0);
	assert(jstrcmp(jitoa(0x1234, num, 16), "1234") == 0);
	assert(jstrcmp(jitoa(0x10, num, 16), "10") == 0);

	assert(jstrcmp(jitoa(-0100, num, 8), "-100") == 0);
	assert(jstrcmp(jitoa(01234, num, 8), "1234") == 0);
	assert(jstrcmp(jitoa(010, num, 8), "10") == 0);
	
	assert(jstrcmp(jitoa_ex(-0xabc, num, 1, 16, 0), "-0xabc") == 0);
	assert(jstrcmp(jitoa_ex(0xabc, num, 1, 16, 1), "0xABC") == 0);

	return;
}

void str_test(void)
{
	char str[1024];
	assert(jstrcmp(jstrcpy(str, ""), "") == 0);
	assert(jstrcmp(jstrcpy(str, "1"), "1") == 0);
	assert(jstrcmp(jstrcpy(str, "123"), "123") == 0);
	
	jmemset(str, 0x00, sizeof(str));
	assert(jstrcmp(jstrncpy(str, "12345", 1), "1") == 0);

	jmemset(str, 0x00, sizeof(str));
	assert(jstrcmp(jstrncpy(str, "12345", 3), "123") == 0);
	assert(jstrncmp(jstrncpy(str, "12345", 3), "123", 1) == 0);
	assert(jstrncmp(jstrncpy(str, "12345", 3), "123", 2) == 0);
	assert(jstrncmp(jstrncpy(str, "12345", 3), "123", 3) == 0);

	return;
}

void mem_test(void)
{
	char str[1024];
	jmemset(str, 0x00, sizeof(str));
	assert(jmemcmp(jmemset(str, 'a', 5), "aaaaa", 5) == 0);
	assert(jmemcmp(jmemcpy(str, "bbbbb", 5), "bbbbb", 5) == 0);
	assert(jmemcmp(jmemcpy(str, "bbbbb", 1), "bbbbb", 5) == 0);
	assert(jmemcmp(jmemcpy(str, "bbbbb", 4), "bbbbb", 5) == 0);
	assert(jmemcmp(jmemcpy(str, "bbbbb", 6), "bbbbb", 5) == 0);
	assert(jmemcmp(jmemcpy(str, "bbbbb", 5), "bbbbb", 1) == 0);
	assert(jmemcmp(jmemcpy(str, "bbbbb", 5), "bbbbb", 4) == 0);

	return;
}

void print_test(void)
{
	char str[1024];
	char str1[10];
	jsnprintf(str, sizeof(str), "%s%d0x%x", "aaa", 123, 0xabc);
	assert(jstrcmp(str, "aaa1230xabc") == 0);
	
	jsnprintf(str, sizeof(str), "%s%d0x%X", "aaa", 123, 0xabc);
	assert(jstrcmp(str, "aaa1230xABC") == 0);
	
	jsnprintf(str, sizeof(str), "%s%d%p", "aaa", 123, 0xabc);
	assert(jstrcmp(str, "aaa1230xabc") == 0);
	
	assert(jsnprintf(str1, sizeof(str1), "%s%d%p", "aaa", 123, 0xabc) == 10);
	assert(jstrncmp(str1, "aaa1230xabc", sizeof(str1)-1) == 0);

	return;
}

void test_all(void)
{
//	print_test();
//	jitoa_test();
//	jatoi_test();
	str_test();
	mem_test();

	return;
}

int main(int argc, char* argv[])
{
	test_all();

	return 0;
}

