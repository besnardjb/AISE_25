#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

void  plop(int sig)
{
	printf("SIGNINT :'(\n");
}


int main(int argc, char ** argv)

{
	if( signal(SIGINT, plop) )
	{
		perror("signal");
		return 1;
	}


	while(1)
	{
		sleep(1);
	}


	return 0;
}
