#include <stdlib.h>


int main()
{
	int *alloc = malloc(4*sizeof(int));

	alloc[3] = 1;

	free(alloc);

	return 0;
}
