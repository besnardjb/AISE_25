#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>

void foo()
{
	printf("Here LIB **AA** WILL CAPTURE\n");

	void * next = dlsym(RTLD_NEXT, "foo");

	if(next)
	{
		void (*foo)() = (void (*)())next;
		(foo)();
	}

	printf("LIB **AA**\n");
}
