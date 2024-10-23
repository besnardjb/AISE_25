#include <stdio.h>

#include "add.h"

int main(int argc, char ** argv)
{
	int res = add(1,3);


	printf("PTR= %llX\n", pointeur()); 

	printf("1 + 3 = %d\n", res);


	return 0;
}
