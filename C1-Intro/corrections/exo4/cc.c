#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>



int main(int argc, char ** argv)
{
	int fd = STDIN_FILENO;
	
	if(argc == 2)
	{
		fd = open(argv[1], O_RDONLY);

		if(fd < 0)
		{
			perror("open");
			return 1;
		}

	}

	char buff[400];
	ssize_t cnt;

	while( (cnt = read(fd, buff, 400)) != 0 )
	{

		if(cnt < 0)
		{
			perror("read");
			return 1;
		}

		int i;

		printf("%ld\n", cnt);

#if 0
		for(i = 0; i < cnt; i++)
		{
			printf("%c", buff[i]);
		}
#else
		write(STDOUT_FILENO, buff, cnt);
#endif

	}


	return 0;
}
