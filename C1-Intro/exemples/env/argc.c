#include <stdio.h>

int main(int argc, char ** argv[])
{
#if 0
	int i;
	for(i = 0 ; i < argc; i++)
	{
		printf("%s\n", argv[i]);
	}
#else
	while(*argv)
	{
		printf("%s\n", *argv);
		argv++;
	}
#endif
	return 0;
}
