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


	char buff[32];

	while(1)
	{
		ssize_t ret = fread(buff, sizeof(char), 32, file);

		if(ret == 0)
		{
			break;
		}

		if(ret < 0)
		{
			if(feof(file))
			{
				break;
			}

			perror("read");
			return 0;
		}

		/* Use buffer */
		int i;

		for( i = 0; i < ret; i++)
		{
			printf("%c", buff[i]);
		}

	}


	fclose(file);

	return 0;
}
