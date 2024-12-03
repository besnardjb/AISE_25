#include <stdio.h>

#ifdef CONTENT 
static char * MSG = "CONTENT";
#else
static char * MSG = "PAS CONTENT";
#endif

#define H Hello
#define xstr(s) str(s)
#define str(s) #s
#define HELLO xstr(H)

int main(int argc, char ** argv)
{
	printf("%s je suis %s\n", HELLO, MSG);
	return 0;
}
