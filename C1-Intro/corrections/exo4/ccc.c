#include <stdio.h>
#include <unistd.h>


int main(int argc, char ** argv)
{
	char buff[100];

	getcwd(buff, 100);

	printf("%s\n", buff);

	return 0;
}
