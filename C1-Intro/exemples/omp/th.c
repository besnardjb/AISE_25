#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define THREAD_NUM 128

void * foo(void * p)
{
	int v = *((int *)p);
	printf("Thread %d\n", v);
	return NULL;
}

int main(int argc, char **argv)
{
	pthread_t th[THREAD_NUM];
	int * tab = malloc(THREAD_NUM * sizeof(int));
	int i;

	for(i = 0 ; i < THREAD_NUM ; i ++)
	{
		tab[i] = i;
		pthread_create(&th[i], NULL, foo, &tab[i]);
	}

	
	for(i = 0 ; i < THREAD_NUM ; i ++)
	{
		pthread_join(th[i], NULL);
	}

	return 0;
}
