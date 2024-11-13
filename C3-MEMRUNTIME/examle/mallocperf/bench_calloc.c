#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "cycle.h"

double now_gtod(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);

	return (double)tv.tv_sec + (double)tv.tv_usec * 1e-6;
}


double ticks_per_second()
{
	static ticks __tps = 0;

	if(__tps != 0)
	{
		return __tps;
	}


	fprintf(stderr,"Calibrating timer ...\n");

	ticks tstart = getticks();
	double ts = now_gtod();
	
	sleep(10);
	
	ticks tend = getticks();
	double te = now_gtod();

	fprintf(stderr, "TSTART %g TS %g TEND %g TE %g DTICKS %g DTS %g\n", (double)tstart, ts, (double)tend, te, (double)(tend - tstart), te - ts);

	__tps = ((double)tend - tstart) / (te - ts);

	fprintf(stderr, "TPS is %g\n", __tps);

	return __tps;
}

double now_ticks(void)
{
	return (double)getticks()/ticks_per_second();
}


#define ITER 100

int main(int argc, char ** argv)
{
	ticks_per_second();
	
	size_t i;

	for(i=1; i < 1024*1024*4096llu; i*=2)
	{
		int j;

		double avg_mm = 0;
		double avg_ca = 0;

		for(j = 0 ; j < ITER ; j++)
		{
			double tsmm = now_gtod();
			void * p = malloc(i);
			memset(p, 9, i);
			double temm = now_gtod();
			free(p);


			double tsca = now_gtod();
			void *c = calloc(i, sizeof(char));
			double teca = now_gtod();
			free(c);
		
			avg_mm += temm - tsmm;
			avg_ca += teca - tsca;
		}

		avg_mm /= ITER;
		avg_ca /= ITER;

		printf("%lu %g %g\n", i, avg_mm, avg_ca);

	}

	return 0;
}
