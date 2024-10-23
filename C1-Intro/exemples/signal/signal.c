#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

void  plop(int sig)
{
	printf("SEGV :'(\n");
}


int main(int argc, char ** argv)

{
	if( signal(SIGSEGV, plop) )
	{
		perror("signal");
		return 1;
	}


	char * lol = NULL;

	*lol = 9;


	while(1)
	{
		sleep(1);
	}


	return 0;
}
