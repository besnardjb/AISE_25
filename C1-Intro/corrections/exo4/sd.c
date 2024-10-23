#include <stdio.h>
#include <dirent.h>

int main(int argc, char ** argv)
{
	if(argc != 2)
	{
		printf("USAGE %s [DIR]\n", argv[0]);
		return 1;
	}

	struct dirent **dirs;

	int fcount = scandir(argv[1], &dirs, NULL, alphasort);

	if(fcount < 0)
	{
		perror("scandir");
		return 1;
	}

	int i;

	for(i = 0 ; i < fcount; i++)
	{
		printf("%s\n", dirs[i]->d_name);
	}

	return 0;

}
