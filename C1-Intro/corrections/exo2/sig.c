#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>


static int cnt = 0;

void compteur(int sig)
{
	cnt=cnt+1;
	printf("Fils CNT = %d\n", cnt);
}



static pid_t c = 0;


void sig(int sig)
{
	

	kill(c, SIGUSR1);
	alarm(3);
}


void sigint(int sig)
{
	printf("Received a signal!");
	kill(c, SIGINT);
	exit(0);
}




int main(int argc, char **argv)
{

	signal(SIGUSR1, compteur);

	c = fork();

	if(c == 0)
	{
		signal(SIGALRM, SIG_IGN);
		//CHILD
		while(1){}
	}
	else
	{
		//PARENT
		signal(SIGINT, sigint);
		printf("PARENT child is %d\n", c);
		signal(SIGALRM, sig);
		alarm(3);
		wait(NULL);
	}


	return 0;
}
