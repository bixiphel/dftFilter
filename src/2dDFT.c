#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "complex.h"
#include "pgm.h"

int main() {
	PGMimage img;
	const double PI = acos(-1.0f);

	readPGM("Knee.pgm", &img);

	// Resize image
	PGMimage resized;
	resized.width = 2*img.width - 1;
	resized.height = 2*img.height - 1;
	resized.max = img.max;
	unsigned char *rData = malloc(resized.width * resized.height);
	
	for (int y = 0; y < img.height; y++) {
        	for (int x = 0; x < img.width; x++) {
            		rData[y * resized.width + x] = img.data[y * img.width + x];
        	}
    	}
	resized.data = rData;
	
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
	double output[img.height][img.width];
	double max = 0.0f;

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
			output[v][x] = c_mag(num);
			if(output[v][x] >= max) {
				max = output[v][x];
			}
		}
	}

	// Converts the resulting 2D DFT back into unsigned chars 
	for(int y = 0; y < img.height; y++) {
		for(int x = 0; x < img.width; x++) {
			// Scales values within the image max using log scaling
			output[y][x] = log(1 + output[y][x]);
			rData[y*img.width + x] = (unsigned char) (output[y][x] / log(1 + max) * img.max);
		}
	}	

	writePGM("output.pgm", &resized);	

	return 0;
}
