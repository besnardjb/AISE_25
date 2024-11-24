#include <stdio.h>
#include <complex.h>
#include <stdlib.h>

#include "ppm.h"

#define MAX_ITER 256

// Define the LUT size
#define LUT_SIZE 256

// Function to initialize a static LUT with random colors
unsigned char (*get_color_lut(void))[3] {
    static unsigned char lut[LUT_SIZE][3]; // Static LUT, initialized once
    static int initialized = 0;

    if (!initialized) {
        srand(42); // Seed the random number generator for consistent results
        for (int i = 0; i < LUT_SIZE; i++) {
            lut[i][0] = rand() % 256; // Random Red
            lut[i][1] = rand() % 256; // Random Green
            lut[i][2] = rand() % 256; // Random Blue
        }
        initialized = 1;
    }

    return lut;
}

// Get a color from the static LUT
void get_color(int iter, unsigned char *r, unsigned char *g, unsigned char *b) {
    unsigned char (*lut)[3] = get_color_lut();
    int index = iter % LUT_SIZE; // Wrap around if iteration > LUT_SIZE
    *r = lut[index][0];
    *g = lut[index][1];
    *b = lut[index][2];
}



int main() {
    struct ppm_image src_img;
    int width = 8000;
    int height = 6000;

    // Initialisation des images
    if (ppm_image_init(&src_img, width, height) != 0) {
        return -1;
    }

   double qx = 3.0 / (double)width; 
   double qy = 2.0 / (double)height; 


   // MANDELBROT vas en x de -2 a 1 et en Y de -1 a 1




    // Enregistrer l'image résultante
    if (ppm_image_dump(&src_img, "mandel.ppm") != 0) {
        fprintf(stderr, "Erreur lors de l'enregistrement de l'image.\n");
    }

    // Libérer la mémoire
    ppm_image_release(&src_img);

    return 0;
}


