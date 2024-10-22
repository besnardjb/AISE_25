all: test

libfoo.so: foo.c
	gcc -shared -fpic $^ -o $@

test: libfoo.so test.c
	gcc test.c -o $@ -lfoo -L. -Wl,-rpath=$(PWD)


