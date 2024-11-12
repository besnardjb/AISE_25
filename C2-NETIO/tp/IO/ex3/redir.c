#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char ** argv)
{

	int out = open("out.log", O_CREAT | O_WRONLY, 0600);

	if(out < 0 )
	{
		perror("open");
		return 1;
	}


	dup2(out, STDOUT_FILENO);

	int i;

	for(i = 0 ; i < 4096; i++)
	{
		printf(" Hello %d\n", i);
	}


	return 0;
}
