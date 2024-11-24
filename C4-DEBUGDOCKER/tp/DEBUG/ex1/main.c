#include <stdio.h>

#include "ppm.h"

// Fonction pour dessiner un carré dans une image PPM
void draw_square(struct ppm_image *im, int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b) {
    int x, y;
    for (y = y1; y <= y2; y++) {
        for (x = x1; x <= x2; x++) {
            ppm_image_setpixel(im, x, y, r, g, b);
        }
    }
}


// Fonction pour appliquer une convolution avec un laplacien pour la détection de contours
void apply_laplacian(struct ppm_image *src, struct ppm_image *dest) {
    int x, y;
    for (y = 0; y < src->height; y++) {
        for (x = 0; x < src->width; x++) {
            // Calcul de la somme des différences de luminosité autour du pixel
            int sum_r = -4 * src->px[y * src->width + x].r +
                        src->px[(y - 1) * src->width + x].r +
                        src->px[(y + 1) * src->width + x].r +
                        src->px[y * src->width + x - 1].r +
                        src->px[y * src->width + x + 1].r;

            int sum_g = -4 * src->px[y * src->width + x].g +
                        src->px[(y - 1) * src->width + x].g +
                        src->px[(y + 1) * src->width + x].g +
                        src->px[y * src->width + x - 1].g +
                        src->px[y * src->width + x + 1].g;

            int sum_b = -4 * src->px[y * src->width + x].b +
                        src->px[(y - 1) * src->width + x].b +
                        src->px[(y + 1) * src->width + x].b +
                        src->px[y * src->width + x - 1].b +
                        src->px[y * src->width + x + 1].b;

            // Normalisation des valeurs
            unsigned char val_r = (unsigned char)(sum_r < 0 ? 0 : (sum_r > 255 ? 255 : sum_r));
            unsigned char val_g = (unsigned char)(sum_g < 0 ? 0 : (sum_g > 255 ? 255 : sum_g));
            unsigned char val_b = (unsigned char)(sum_b < 0 ? 0 : (sum_b > 255 ? 255 : sum_b));

            // Assignation du pixel résultat
            ppm_image_setpixel(dest, x, y, val_r, val_g, val_b);
        }
    }
}

int main() {
    struct ppm_image src_img, dest_img;
    int width = 800;
    int height = 600;

    // Initialisation des images
    if (ppm_image_init(&src_img, width, height) != 0) {
        return -1;
    }
    if (ppm_image_init(&dest_img, width, height) != 0) {
        ppm_image_release(&src_img);
        return -1;
    }

    int i,j;
 
    // Draw some cool figures
    for (i = 0; i < width; ++i) {
        for (j = 0; j < height; ++j) {
            ppm_image_setpixel( &src_img, i, j, i%255, j%255, (i+j)%255);
        }
    }
 
    for (i = 0; i < height; ++i) {
        ppm_image_setpixel( &src_img, i, i, 255, 0, 0 );
    }

    // Dessiner un carré rouge sur l'image source
    draw_square(&src_img, 200, 200, 600, 400, 255, 0, 0);

    // Enregistrer l'image résultante
    if (ppm_image_dump(&src_img, "carre.ppm") != 0) {
        fprintf(stderr, "Erreur lors de l'enregistrement de l'image.\n");
    }



    // Appliquer une convolution avec un laplacien pour détecter les contours
    apply_laplacian(&src_img, &dest_img);

    // Enregistrer l'image résultante
    if (ppm_image_dump(&dest_img, "contours.ppm") != 0) {
        fprintf(stderr, "Erreur lors de l'enregistrement de l'image.\n");
    }

    // Libérer la mémoire
    ppm_image_release(&src_img);
    ppm_image_release(&dest_img);

    return 0;
}


