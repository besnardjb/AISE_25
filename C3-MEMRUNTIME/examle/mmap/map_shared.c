#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>

#include <sys/wait.h>
#include <string.h>

int main(int argc, char ** argv)
{
	int * mem = (int*) mmap(NULL, 4096*10, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

	if(mem == MAP_FAILED)
	{
		perror("mmap");
		return 1;
	}

	mem[0] = 1337;

	pid_t child = fork();

	if(child == 0)
	{
		printf("Chez enfant %d\n", mem[0]);

		mem[0] = 1111;

		printf("Chez enfant %d MODIF\n", mem[0]);

	}
	else
	{
	//	wait(NULL);
		while(1)
		{
			printf("Chez parent %d\n", mem[0]);
			usleep(10);
		}
	}


	munmap(mem, 4096*10);

	return 0;
}
