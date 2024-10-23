#include <stdio.h>
#include <signal.h>


#include <sys/ioctl.h>



void toto(int sig)
{
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);

	printf("REDIM %d x %d\n", w.ws_row, w.ws_col);
}


int main(int argc, char ** argv)
{
	signal(SIGWINCH, toto);

	while(1){}

	return 0;
}
