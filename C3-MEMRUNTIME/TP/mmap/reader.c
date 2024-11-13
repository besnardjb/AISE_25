       #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
       #include <unistd.h>
       #include <sys/types.h>
       #include <sys/mman.h>
#include <stdio.h>

int main()
{
    int fd = open("./comm.dat", O_CREAT | O_RDWR, 0600);

    volatile int * pint = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_FILE, fd, 0 );

    if(pint == MAP_FAILED)
    {
        perror("mmap");
        return 1;
    }

    while(*pint != 1337)
    {
        usleep(10);
    }

    printf("READER: VALEUR MAJ à 1337");


}