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

    ftruncate(fd, sizeof(int));    

    volatile int * pint = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_FILE, fd, 0 );

    *pint = 0;

    if(pint == MAP_FAILED)
    {
        perror("mmap");
        return 1;
    }


    sleep(10);


    printf("WRITER VALEUR MAJ à 1337");
    *pint = 1337;



}