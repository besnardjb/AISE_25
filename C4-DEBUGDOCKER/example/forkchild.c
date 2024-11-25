#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	pid_t c = fork();

	if( c == 0)
	{
		abort();
	}
	else
	{
		wait(NULL);
	}

}
