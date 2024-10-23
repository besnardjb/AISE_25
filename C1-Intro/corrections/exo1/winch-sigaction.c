#include <stdio.h>
#include <signal.h>


#include <sys/ioctl.h>
#include <string.h>


void toto(int sig)
{
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);

	printf("REDIM %d x %d\n", w.ws_row, w.ws_col);
}


int main(int argc, char ** argv)
{
	signal(SIGWINCH, toto);

	struct sigaction act;
	memset(&act, 0, sizeof(struct sigaction));

	act.sa_handler = toto;

	sigaction(SIGWINCH, &act, NULL);

	while(1){}

	return 0;
}
