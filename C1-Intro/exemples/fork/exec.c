#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char ** argv)
{
	int i;

	for(i = 0 ; i < 10 ; i++)
	{

		pid_t pid = fork();

		if(pid == 0)
		{
			char * command[] = {"echo", "toto", NULL};
			execvp(command[0], command);
		}
		else
		{
			printf("Fils %d\n", pid);
		}

	}

	for(i = 0 ; i < 10 ; i++)
	{
		wait(NULL);
	}

	printf("Fin\n");

	return 0;
}
