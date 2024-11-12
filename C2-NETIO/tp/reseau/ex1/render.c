#include <stdio.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char ** argv)
{
	FILE * f = fopen("./starwars.txt", "r");

	if(f == NULL)
	{
		perror("fopen");
		return 1;
	}

	char buff[1024];
	while(1)
	{

		char * s = fgets(buff, 1024, f);

		if(s == NULL)
		{
			if(feof(f))
			{
				break;
			}

			perror("fgets");
			return 1;
		}

		if( strstr(s, "\033[H"))
		{
			usleep(100000);
		}

		printf("%s", s);
	}



	return 0;
}
