#include <stdlib.h>

struct t
{
	int a;
	int b;
	int c;
	struct t *next;
};


int bar(int i)
{
	struct t myst1 = {
		.a = 8,
		.b = 7,
		.c = 99,
		.next = NULL
	};

	struct t myst = {
		.a = 8,
		.b = i,
		.c = 99,
		.next = &myst1
	};
	int a = 9;
	int *pa = &a;
	int *boom = NULL;	
}


int foo()
{
	int i;
	for(i = 0 ; i < 99; i++)
	bar(i);
}

int main()
{
	foo();
	return 0;
}
