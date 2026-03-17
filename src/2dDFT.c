#include <stdio.h>
#include <math.h>
#include "complex.h"
#include "pgm.h"

int main() {
	PGMimage img;
	const double PI = acos(-1.0f);

	readPGM("Knee.pgm", &img);

	Complex temp[img.height][img.width];

	// Perform the DFT on all rows 
	for(int y = 0; y < img.height; y++) {
		for(int k = 0; k < img.width; k++) {
			Complex num = {0.0f, 0.0f};

			for(int x = 0; x < img.width; x++) {
				double exponent = -2.0f*PI*k*x/(img.width);
				Complex i = {0, 1};
				Complex power = c_mul(i, c_rep(exponent));
				Complex e = c_exp(power);
				Complex transform = c_mul(e, c_rep(img.data[y*img.width + x]));
				num = c_add(num, transform);
			}

			temp[y][k] = num;
		}
	}

	// Perform the DFT on all columns
	Complex output[img.height][img.width];
	
	for(int x = 0; x < img.width; x++) {
		for(int v = 0; v < img.height; v++) {
			Complex num = {0.0f, 0.0f};

			for(int y = 0; y < img.height; y++) {
				double exponent = -2.0f*PI*v*y/(img.width);
				Complex i = {0, 1};
				Complex power = c_mul(i, c_rep(exponent));
				Complex e = c_exp(power);
				
				num = c_add(num, c_mul(temp[y][x], e));
			}
			output[v][x] = num;
			printf("%d %d | ", x, v);
			c_print(num);
			printf("\n");
		}
	}

	return 0;
}
