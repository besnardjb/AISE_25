#include <stdlib.h>

struct t
{
	int a;
	int b;
	int c;
	struct t *next;
};


int bar()
{
	struct t myst1 = {
		.a = 8,
		.b = 7,
		.c = 99,
		.next = NULL
	};

	struct t myst = {
		.a = 8,
		.b = 7,
		.c = 99,
		.next = &myst1
	};
	int a = 9;
	int *pa = &a;
	int *boom = NULL;
	*boom = 10;
	
}


int foo()
{
	bar();
}

int main()
{
	foo();
	return 0;
}
