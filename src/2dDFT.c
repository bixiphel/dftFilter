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
            		rData[y * resized.width + x] = (unsigned char)(img.data[y * img.width + x] * pow(-1, x + y));
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

	// Create another buffer to hold the results of the DFT
	Complex *dft2 = malloc(sizeof(Complex) * resized.width * resized.height);

	// Perform the DFT on all columns
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
			dft2[v*resized.width + x] = num;
		}
	}

	// Pointer similar to temp for the inverse transform's values
	Complex *invTemp = malloc(sizeof(Complex)*resized.width*resized.height);

	// IDFT on the columns 
	for(int x = 0; x < resized.width; x++) {
    		for(int y = 0; y < resized.height; y++) {
        		Complex sum = {0.0, 0.0};
        		for(int v = 0; v < resized.height; v++) {
            			double exponent = 2.0 * PI * v * y / resized.height; 
            			Complex i = {0, 1};
            			Complex e = c_exp(c_mul(i, c_rep(exponent)));
            			sum = c_add(sum, c_mul(dft2[v*resized.width + x], e));
        		}
        		invTemp[y*resized.width + x] = sum;
    		}
	}

	
	// Inverse DFT on rows and directly store as unsigned char
	for(int y = 0; y < resized.height; y++) {
    		for(int x = 0; x < resized.width; x++) {
        	Complex sum = {0.0, 0.0};
        		for(int u = 0; u < resized.width; u++) {
            			double exponent = 2.0 * PI * u * x / resized.width; // note + sign
            			Complex i = {0, 1};
            			Complex e = c_exp(c_mul(i, c_rep(exponent)));
            			sum = c_add(sum, c_mul(invTemp[y*resized.width + u], e));
        		}

        		// Normalize and undo centering
        		double val = sum.real / (resized.width * resized.height);
        		val *= pow(-1, x + y);

        		// Clamp and convert to unsigned char
        		if(val < 0) val = 0;
        		if(val > resized.max) val = resized.max;
        		rData[y*resized.width + x] = (unsigned char) val;
    		}
	}

	// Move the modified data back into the resized image's data
	resized.data = rData;


	// "Crop" the image back to the original dimensions, rewriting the original buffer with the transformed data
	for (int y = 0; y < img.height; y++) {
        	for (int x = 0; x < img.width; x++) {
        		img.data[y*img.width + x] = resized.data[y*resized.width + x];
		}
    	}

	// Write to the output
	writePGM("output.pgm", &img);	

	// Free memory and close resources
	free(rData);
	free(temp);
	free(invTemp);
	free(dft2);

	return 0;
}
