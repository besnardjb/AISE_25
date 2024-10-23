#include <stdio.h>
#include <stdint.h>


#include "add.h"

void * pointeur()
{
	return (void*)UINT64_MAX;
}


int add(int a, int b)
{
	return a+b;
}
