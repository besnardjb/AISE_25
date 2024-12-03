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

#if __STDC__
#warning "STDC=1"
#else
#warning "STDC=0"
#endif


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


#define log(...) do{\
			char buff[128];\  
			snprintf (buff, 128, __VA_ARGS__);\
			fprintf(stderr, "%s:%d >>> %s", __FILE__, __LINE__, buff);\
		}while(0)


int main(int argc, char ** argv)
{
	log("%s je suis %s %s %s\n", HELLO, MSG, foo(), foo2());

	printf("%s : %d\n", __FILE__, __LINE__);
	printf("%s %s\n", __DATE__, __TIME__);

	return 0;
}
