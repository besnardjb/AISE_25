#include <stdio.h>


int main(int argc, char ** argv)
{
	if(argc < 2)
	{
		printf("USAGE %s [FILE]\n", argv[0]); 
		return 1;
	}

	FILE * file = fopen(argv[1], "w");

	if(file == NULL)
	{
		perror("fopen");
		return 1;
	}


	int i;

	for(i = 0 ; i < 1024; i++)
	{
		if( fwrite(&i, sizeof(int), 1, file) == 0)
		{
			perror("fwrite");
			return 1;
		}

	}


	fclose(file);

	return 0;
}
