#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>


static int cnt_cont = 0;
static int cnt_pipe = 0;


void compteur(int sig)
{
	switch(sig)
	{
		case SIGCONT:
			cnt_cont ++;
			break;
		case SIGPIPE:
			cnt_pipe++;
			break;
	}

	printf("Fils CONT %d PIPE %d\n", cnt_cont, cnt_pipe);
}


void sigintenfant(int sig)
{
	printf("SIGINT Fils CONT %d PIPE %d\n", cnt_cont, cnt_pipe);
	exit(0);
}




static pid_t c = 0;
static int cnt = 0;

void sig(int sig)
{

	if(rand()%2)
	{

		kill(c, SIGCONT);
	}
	else	
	{

		kill(c, SIGPIPE);
	}

	alarm(3);


	cnt++;
	if(cnt == 3)
	{
		kill(c, SIGINT);
		exit(0);
	}
}


void sigint(int sig)
{
	printf("Received a signal!");
	kill(c, SIGINT);
	exit(0);
}




int main(int argc, char **argv)
{

	signal(SIGPIPE, compteur);
	signal(SIGCONT, compteur);

	c = fork();

	if(c == 0)
	{
		signal(SIGINT, sigintenfant);
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
