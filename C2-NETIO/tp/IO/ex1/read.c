#include <stdio.h>

#include "part.h"


#define NUM_PARTS 100

int main(int argc, char ** argv)
{
    struct Particle parts[NUM_PARTS] = { 0 };

    FILE * fd = fopen("./part.dat", "r");

    if(!fd)
    {
        perror("fopen");
        return 1;
    }

    fread(parts, sizeof(struct Particle), NUM_PARTS, fd);

    int i;
    for(i = 0; i < NUM_PARTS; i++)
    {

        if( parts[i].x != i)
        {
            printf("Erreur IDX %d\n", i);
        }

        if( parts[i].y != i + 1)
        {
            printf("Erreur IDX %d\n", i);
        }
    }




    fclose(fd);

    return 0;
}