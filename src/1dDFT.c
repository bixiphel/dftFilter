#include <stdio.h>
#include <math.h>
#include "complex.h"
#include "pgm.h"

int main() {
	PGMimage img;
	const double PI = acos(-1.0f);

	readPGM("Knee.pgm", &img);

	// Performs a 1D dft on the first row
	for(int k = 0; k <= img.max; k++) {
		Complex num = {0.0f, 0.0f};

		for(int m = 0; m <= img.max; m++) {
			double exponent = 0.0f;
			exponent = -2.0f*PI*k*m/(img.max);

			Complex i = {0, 1};
			Complex power = c_mul(i, c_rep(exponent));
			Complex e = c_exp(power);
			Complex transform = c_mul(e, c_rep(img.data[m]));
			num = c_add(num, transform);
		}
		printf("X_%d = ", k);
		c_print(num);
		printf("\n");
	}
	return 0;
	
}
