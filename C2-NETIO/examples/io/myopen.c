#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>


int main(int argc, char ** argv)
{
	int fd = open("./lol.dat", O_RDWR | O_CREAT, 0600);
	
	if(fd < 0)
	{
		perror("open");
		return 1;
	}


	close(fd);


	return 0;
}
