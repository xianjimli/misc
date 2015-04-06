#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _Parent
{
	int var;
}Parent;

typedef struct _Child
{
	Parent parent;
	char name[256];
}Child;

int main(int argc, char* argv[])
{
	Child* c = calloc(1, sizeof(Child));
	strcpy(c->name, "child");
	
	Parent* p = (Parent*)c;
	p->var = 123;

	printf("var=%d name=%s\n", p->var, c->name);

	return 0;
}
