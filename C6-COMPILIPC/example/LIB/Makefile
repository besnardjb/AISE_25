CC=gcc

all: static_man static_man dynamic dynamic_man dynamic_rpath

libtoto.so: lib.c
	$(CC) -shared -fpic $^ -o $@

libtoto.a: lib.c
	gcc -c $^ -o lib.o
	ar rcs ./libtoto.a lib.o

static: main.c libtoto.a
	$(CC) -static main.c -L. -ltoto -o $@

dynamic: main.c libtoto.so
	$(CC) main.c -L. -ltoto -o $@

dynamic_run:
	LD_LIBRARY_PATH=$(PWD) ./dynamic

dynamic_rpath: main.c libtoto.so
	$(CC) main.c -L. -ltoto -o $@ -Wl,-rpath=$(PWD)

# Bof
dynamic_man: main.c libtoto.so
	$(CC) main.c ./libtoto.so -o $@

# Bof
static_man: main.c libtoto.a
	$(CC) main.c libtoto.a -o $@

clean:
	rm -fr static_man static_man dynamic dynamic_man dynamic_rpath
