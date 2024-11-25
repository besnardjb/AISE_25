#include <pthread.h>

pthread_mutex_t l1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t l2 = PTHREAD_MUTEX_INITIALIZER;


void * l1l2(void *dummy)
{
	while(1)
	{
		pthread_mutex_lock(&l1);
		pthread_mutex_lock(&l2);

		pthread_mutex_unlock(&l2);
		pthread_mutex_unlock(&l1);
	}
}


void * l2l1(void *dummy)
{
	int val = *((int *) dummy);
	while(1)
	{
		pthread_mutex_lock(&l2);
		pthread_mutex_lock(&l1);
		printf("Woot %d\n", val);
		pthread_mutex_unlock(&l1);
		pthread_mutex_unlock(&l2);
	}
}


int main()
{
	pthread_t t1, t2;

	int v1 = 1;
	pthread_create(&t1, NULL, l2l1, &v1);
	int v2 = 2;
	pthread_create(&t2, NULL, l2l1, &v2);
	
	void * ret1 = NULL;
	pthread_join(t1, &ret1);
	pthread_join(t2, NULL);
	return 0;
}
