#include <stdio.h>

#include "part.h"



int main(int argc, char ** argv)
{
    struct Particle parts[NUM_PARTS] = { 0 };

    int i;

    for(i = 0; i < NUM_PARTS; i++)
    {
        parts[i].x = i;
        parts[i].y = i + 1;
        parts[i].z = 0;
    }

    FILE * fd = fopen("./part.dat", "w");

    if(!fd)
    {
        perror("fopen");
        return 1;
    }

//    fwrite(parts, sizeof(struct Particle), NUM_PARTS, fd);

    fprintf(fd, "[");
    for(i = 0; i < NUM_PARTS; i++)
    {
        fprintf(fd, "{\"x\": %d, \"y\": %d, \"z\":%d}%s", parts[i].x, parts[i].y, parts[i].z, (i < (NUM_PARTS - 1))?(","):(""));
    }
    fprintf(fd, "]");


    fclose(fd);

    return 0;
}