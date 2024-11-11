#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv)
{
	int fd = open("./toto", O_RDWR | O_CREAT,
		         	0600 );

	if( fd < 0)
	{
		perror("open");
	}


	close(fd);

	return 0;
}
