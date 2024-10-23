#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>



int main(int argc, char ** argv)
{
	if(argc != 2)
	{
		printf("PAS CONTENT\n");
		return 1;
	}

	int fdout = open(argv[1], O_WRONLY | O_CREAT, 0600);

	if(fdout < 0)
	{
		perror("open");
		return 1;
	}


	char buff[400];
	ssize_t cnt;

	while( (cnt = read(STDIN_FILENO, buff, 400)) != 0 )
	{

		if(cnt < 0)
		{
			perror("read");
			return 1;
		}

		int i;

		write(STDOUT_FILENO, buff, cnt);
		write(fdout, buff, cnt);

	}

	close(fdout);

	return 0;
}
