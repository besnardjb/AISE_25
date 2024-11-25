#include <stdio.h>
#include <stdlib.h>

#define NUM_SEGMENTS 5
#define SEGMENT_SIZE 100

int main() {
    int *segments[NUM_SEGMENTS];

    for (int i = 0; i < NUM_SEGMENTS; i++) {
        segments[i] = (int *)malloc(SEGMENT_SIZE * sizeof(int));
        if (segments[i] == NULL) {
            printf("Erreur lors de l'allocation de mémoire pour le segment %d.\n", i);
            for (int j = 0; j < i; j++) {
                free(segments[j]);
            }
            return -1;
        }
    }

    for (int i = 0; i < NUM_SEGMENTS; i++) {
        for (int j = 0; j < SEGMENT_SIZE; j++) {
            segments[i][j] = i + j;
        }
    }

    for (int i = 0; i < NUM_SEGMENTS; i ++) {
        free(segments[i]);
        segments[i] = NULL;
    }

    return 0;
}

