#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv, char ** envp)
{
	int i;
#if 0
	while(*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
#endif

	printf("LOL = %s\n", getenv("LOL"));
	
	return 0;
}
