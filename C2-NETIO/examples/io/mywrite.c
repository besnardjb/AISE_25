#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


/* 0 OK -1 PB */
int safe_write(int fd, void * buffer, size_t size)
{
	size_t written = 0;

	while( (size - written) > 0)
	{

		ssize_t ret = write(fd, buffer + written, size - written);

		if( ret < 0)
		{
			perror("write");
			return 1;
		}

		written += ret;

	}

	return 0;
}


int main(int argc, char ** argv)
{
	if(argc < 3)
	{
		fprintf(stderr,"Usage %s [FICHIER] [MB]\n", argv[0]);
		return 1;
	}

	int to_write_mb = atoi(argv[2]);

	int fd = open(argv[1], O_RDWR | O_CREAT, 0600);

	if(fd < 0)
	{
		perror("open");
		return 1;
	}

	size_t size = to_write_mb * 1024 * 1024;

	char* large_buff = malloc(size);

	if(large_buff == NULL)
	{
		perror("malloc");
		close(fd);
		return 1;
	}

	size_t i = 0;
	for(i = 0; i < size; i++)
	{
		large_buff[i] = 'a' + i % 26;
	}


	safe_write(fd, large_buff, size);

	free(large_buff);
	large_buff = NULL;

	close(fd);


	return 0;
}
