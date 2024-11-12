#include <stdio.h>


int main(int argc, char ** argv)
{
	if(argc < 2)
	{
		printf("USAGE %s [FILE]\n", argv[0]); 
		return 1;
	}

	FILE * file = fopen(argv[1], "r");

	if(file == NULL)
	{
		perror("fopen");
		return 1;
	}


	char buff[512];

	int line = 1;

	while(1)
	{
		char * ret = fgets(buff, 512, file);

		if(ret  == NULL)
		{
			if(feof(file))
			{
				break;
			}

			perror("read");
			return 0;
		}

		/* Use buffer */
		printf("%d : %s", line, buff);
		line++;
	}


	fclose(file);

	return 0;
}
