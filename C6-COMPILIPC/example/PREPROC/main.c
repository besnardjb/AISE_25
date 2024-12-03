#include <stdio.h>

#ifdef CONTENT 
static char * MSG = "CONTENT";
#else
static char * MSG = "PAS CONTENT";
#endif

#ifdef CRASH
	#error "Aie"
#endif

#warning "What is this ?"

#define H Hello
#define xstr(s) str(s)
#define str(s) #s
#define HELLO xstr(H)

#define TOTO 5

char* foo()
{
	return xstr(TOTO);
}

#undef TOTO

char* foo2()
{
	return xstr(TOTO);
}



int main(int argc, char ** argv)
{
	printf("%s je suis %s %s %s\n", HELLO, MSG, foo(), foo2());
	return 0;
}
