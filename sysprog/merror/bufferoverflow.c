#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
	char str[10];
	int array[10] = {0,1,2,3,4,5,6,7,8,9};
	
	int data = array[10];
	array[10] = data;

	if(argc == 2)
	{
		strcpy(str, argv[1]);
	}

	return 0;
}
