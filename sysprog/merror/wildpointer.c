#include <stdlib.h>
#include <string.h>

#define SAFE_FREE(p) {free(p); p=NULL;}

int main(int argc, char* argv[])
{
	char* str = (char*)malloc(100);
	strcpy(str, "aaa");
	SAFE_FREE(str);

	return 0;
}
