#include <stdio.h>
#include <complex.h>
#include <stdlib.h>

#include "ppm.h"

#define MAX_ITER 512

// Define the LUT size
#define LUT_SIZE MAX_ITER

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

void get_color2(int iter, unsigned char *r, unsigned char *g, unsigned char *b, int max_iter) {
	// Ensure iter stays within bounds
	if (iter < 0) iter = 0;
	if (iter > max_iter) iter = max_iter;

	// Normalize iter to a range between 0.0 and 1.0
	float t = (float)iter / (float)max_iter;

	// Red goes from 0 to 1 as iter goes from 0 to max_iter
	*r = (unsigned char)(255 * t);  // Red intensity increases
	// Blue goes from 1 to 0 as iter goes from 0 to max_iter
	*b = (unsigned char)(255 * (1.0 - t));  // Blue intensity decreases
	// Green remains a constant at 0 for a pure red-blue gradient
	*g = 0;  
}




int main() {
	struct ppm_image src_img;
	int width = 8000;
	int height = 6000;

	// Initialisation des images
	if (ppm_image_init(&src_img, width, height) != 0) {
		return -1;
	}

	/* -1 -0.4 0.25 0.25 */
	double startx = -1.5;
	double starty = -.25;
	double wx = .2;
	double wy = .2;

	double qx = wx / (double)width; 
	double qy = wy / (double)height; 

	int y, x;

	#pragma omp parallel for
	for(y= 0; y < height; y++)
	{
		for(x= 0; x < width; x++)
		{
			double tx = startx + x * qx;
			double ty = starty + y * qy;

			double complex c = tx + I * ty;
			double complex z = 0;
			int it = 0;

			while( (cabs(z) < 2.0) && (it < MAX_ITER))
			{
				z = z * z + c;
				it++;
			}

			unsigned char r,g,b;
			get_color(it, &r, &g, &b);

			ppm_image_setpixel(&src_img, x,y, r,g,b);
		
		}

	}

	// Enregistrer l'image résultante
	if (ppm_image_dump(&src_img, "mandel.ppm") != 0) {
		fprintf(stderr, "Erreur lors de l'enregistrement de l'image.\n");
	}

	// Libérer la mémoire
	ppm_image_release(&src_img);

	return 0;
}


