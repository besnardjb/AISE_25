#include <stdio.h>

int main(int argc, char **argv)
{
	#pragma omp parallel
	{
		printf("Hello there\n");
	}

	return 0;
}
