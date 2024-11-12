#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>


int main(int argc, char ** argv)
{
	int oldmask = umask(0000);

	int fd = open("./lol.umask", O_RDWR | O_CREAT, 0777);
	
	umask(oldmask);

	if(fd < 0)
	{
		perror("open");
		return 1;
	}


	close(fd);


	return 0;
}
