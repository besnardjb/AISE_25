#include <stdio.h>
#include <time.h>


int main(int argc, char ** argv)
{
	time_t t = time(NULL);
	printf("%s (%ld)\n", ctime(&t), t);
	return 0;
}
