CC=gcc
CFLAGS=-Wall 

all : main

libmystring.so: mystring.c
	$(CC) $(CFLAGS) -shared -fpic $^ -o $@

main : libmystring.so main.c
	$(CC) $(CFLAGS) main.c -L. -lmystring -Wl,-rpath=$(PWD) -o $@

clean:
	rm -fr libmystring.so main