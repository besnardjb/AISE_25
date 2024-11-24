#include <stdio.h>
#include <stdlib.h>

void process_data(int *data, int size) {
    for (int i = 0; i <= size; i++) { 
        data[i] *= 2;
    }
}

void process_data2(int *data, int size) {
    for (int i = 0; i < size + 50; i++) { 
        data[i] *= 2;
    }
}

void process_data3(int *data, int size) {
    for (int i = 0; i < size * 1000; i++) { 
        data[i] *= 2;
    }
}


int main() {
    int size = 4096;
    int *data = (int *)malloc(size * sizeof(int));

    if (data == NULL) {
        printf("Erreur lors de l'allocation de mémoire.\n");
        return -1;
    }

    // Remplissage du tableau
    for (int i = 0; i < size; i++) {
        data[i] = i;
    }

    // Appel de la fonction avec une taille incorrecte
    process_data(data, size);
    process_data2(data, size);
    process_data3(data, size);


    // Libération de la mémoire
    free(data);

    return 0;
}
