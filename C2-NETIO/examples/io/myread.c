#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>


int main(int argc, char ** argv)
{
	if(argc < 2)
	{
		fprintf(stderr,"Usage %s [FICHIER]\n", argv[0]);
		return 1;
	}


	int fd = open(argv[1], O_RDWR | O_CREAT, 0600);
	
	if(fd < 0)
	{
		perror("open");
		return 1;
	}


	char buff[32];
	ssize_t ret = 0;

	while(1)
	{
		ret = read(fd, buff, 32);
		
		printf("=== RET = %ld ==\n", ret);

		if(ret == 0)
		{
			/* EOF */
			break;
		}

		if(ret < 0)
		{
			perror("read");
			return 1;
		}

		int i;


		for(i = 0 ; i < ret; i++)
		{
			printf("%c", buff[i]);
		}

	}


	close(fd);


	return 0;
}
