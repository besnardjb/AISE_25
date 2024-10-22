CC=gcc
CFLAGS=-Wall -Wextra


all: th omp

omp: omp.c
	$(CC) $(CFLAGS) -fopenmp $^ -o $@ 

th: th.c
	$(CC) $(CFLAGS) $^ -o $@ -lpthread

clean:
	rm -f ./th ./omp
