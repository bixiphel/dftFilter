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

	// Zero the rData array
	for(int i = 0; i < resized.width*resized.height; i++) {
		rData[i] = 0;
	}

	// Put the original image data in the top-left corner and "center" it
	for (int y = 0; y < img.height; y++) {
        	for (int x = 0; x < img.width; x++) {
            		rData[y * resized.width + x] = img.data[y * img.width + x] * pow(-1, x + y);
        	}
    	}
	resized.data = rData;
	
	// Stores the image data as complex numbers
	Complex *temp = malloc(sizeof(Complex)*resized.width*resized.height);

	// Perform the DFT on all rows 
	for(int y = 0; y < resized.height; y++) {
		for(int u = 0; u < resized.width; u++) {
			Complex num = {0.0f, 0.0f};

			for(int x = 0; x < resized.width; x++) {
				double exponent = -2.0f*PI*u*x/(resized.width);
				Complex i = {0, 1};
				Complex power = c_mul(i, c_rep(exponent));
				Complex e = c_exp(power);
				Complex transform = c_mul(e, c_rep((double)resized.data[y*resized.width + x]));
				num = c_add(num, transform);
			}

			temp[y*resized.width + u] = num;
		}
	}

	// Perform the DFT on all columns
	double *output = malloc(sizeof(double)*resized.width*resized.height);
	double max = 0.0f;

	for(int x = 0; x < resized.width; x++) {
		for(int v = 0; v < resized.height; v++) {
			Complex num = {0.0f, 0.0f};

			for(int y = 0; y < resized.height; y++) {
				double exponent = -2.0f*PI*v*y/(resized.height);
				Complex i = {0, 1};
				Complex power = c_mul(i, c_rep(exponent));
				Complex e = c_exp(power);
				
				num = c_add(num, c_mul(temp[y*resized.width + x], e));
			}
			output[v*resized.width + x] = c_mag(num);
			
			if(output[v*resized.width + x] >= max) {
				max = output[v*resized.width + x];
			}
		}
	}

	// Converts the resulting 2D DFT back into unsigned chars 
	for(int y = 0; y < resized.height; y++) {
		for(int x = 0; x < resized.width; x++) {
			// Scales values within the image max using log scaling
			output[y*resized.width + x] = log(1 + output[y*resized.width + x]);
			rData[y*resized.width + x] = (unsigned char) (output[y*resized.width + x] / log(1 + max) * resized.max);
		}
	}	

	// Write to the output
	writePGM("output.pgm", &resized);	

	// Free memory and close resources
	free(rData);
	free(temp);
	free(output);

	return 0;
}
