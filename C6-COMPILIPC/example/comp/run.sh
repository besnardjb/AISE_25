cpp ./main.c -o ./main.i
/usr/lib/gcc/x86_64-linux-gnu/10/cc1 ./main.i -o main.s
as ./main.s -o main.o
ld -m elf_x86_64 -dynamic-linker /lib64/ld-linux-x86-64.so.2 /usr/lib/x86_64-linux-gnu/crt1.o /usr/lib/x86_64-linux-gnu/crti.o main.o -lc /usr/lib/x86_64-linux-gnu/crtn.o -o ./a.out
