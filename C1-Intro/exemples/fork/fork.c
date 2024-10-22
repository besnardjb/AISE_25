#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc, char ** argv)
{
	printf("Debut @  %d\n", __LINE__);

	int val = 1337;
	
	pid_t pid = fork();


	printf("Debut apres  @  %d\n", __LINE__);

	if(pid == 0)
	{
		printf("Fils @  %d\n", __LINE__);
		printf("Fils VAL =  %d\n", val);
	}
	else
	{
		printf("Parent @  %d PID : %d\n", __LINE__, pid);
		printf("Parent VAL =  %d\n", val);
		val = 10;
		printf("Parent VAL (apres modif) =  %d\n", val);

	}

	printf("Fin VAL =  %d\n", val);

	printf("WOOT ici  %d\n", __LINE__);


	return 0;
}
