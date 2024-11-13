#include <stdio.h>

void foo()
{
	int i = 0;
	while(1)
	{
		i++;
	}

}

int main()
{
	#pragma omp parallel
	foo();
	return 0;
}
