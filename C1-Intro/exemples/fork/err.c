#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char ** argv)
{
	if(unlink(argv[1]) < 0)
	{
		perror("unlink argv[1]");
	}

	return 0;
}
