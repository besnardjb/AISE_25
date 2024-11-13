#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char ** argv)
{
	int fd = open("./tst", O_RDWR);

	if(fd < 0 )
	{
		perror("open");
		return 1;
	}

	struct stat st;
	fstat(fd, &st);

	printf("Size is %ld\n", st.st_size);


	int * mem = (int*) mmap(NULL, st.st_size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_FILE, fd, 0);

	if(mem == MAP_FAILED)
	{
		perror("mmap");
		return 1;
	}

	close(fd);

	mem[0] = 0xDEADBEEF;


	munmap(mem, st.st_size);

	return 0;
}
