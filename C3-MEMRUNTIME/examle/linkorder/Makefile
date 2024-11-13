CC=gcc

all: liba.so libaa.so libb.so main


liba.so: liba.c
	$(CC) -shared -fpic $^ -o $@ -ldl


libaa.so: libaa.c
	$(CC) -shared -fpic $^ -o $@ -ldl

libb.so: libb.c
	$(CC) -shared -fpic $^ -o $@

main: main.c
	$(CC) $^ -o $@ -L. -lb -Wl,-rpath=$(PWD)
