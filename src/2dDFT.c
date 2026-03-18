#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "complex.h"
#include "pgm.h"

int main(int argc, char** argv) {
	if (argc != 4){
    		printf("Usage: MyProgram <input_ppm> <output_ppm> <cutoff_frequency>\n");
    		printf("       <input_ppm>: PGM file \n");
    		printf("       <output_ppm>: PGM file \n");
		printf("       <cutoff_frequency>: Low-Pass cutoff frequency \n");
    		exit(16);
  	}

	PGMimage img;
	const double PI = acos(-1.0f);
	const Complex i = {0, 1};

	readPGM(argv[1], &img);

	// Resize image
	PGMimage resized;
	resized.width = 2*img.width - 1;
	resized.height = 2*img.height - 1;
	resized.max = img.max;
	unsigned char *rData = malloc(resized.width * resized.height);

	// Zero the rData array
	for(int q = 0; q < resized.width*resized.height; q++) {
		rData[q] = 0;
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
				Complex transform = c_mul(c_exp(c_mul(i, c_rep(-2.0f*PI*u*x/(resized.width)))), c_rep((double)resized.data[y*resized.width + x]));
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
				num = c_add(num, c_mul(temp[y*resized.width + x], c_exp(c_mul(i, c_rep(-2.0f*PI*v*y/(resized.height))))));
			}
			dft2[v*resized.width + x] = num;
		}
	}

	/***** Ideal Low Pass Filtering *****/
	double cutoff = atoi(argv[3])*1.0f;		// Make this a user-defined parameter later
	for(int v = 0; v < resized.height; v++) {
		for(int u = 0; u < resized.width; u++) {
			// Calculate the ideal function
			double D = sqrt(pow(u - resized.width/2, 2) + pow(v - resized.height/2, 2));

			if(D <= cutoff) {
				// Multiply dft2[v*resized.width + x] by 1, which doesn't do anything
			} else {
				// Cuts off any frequencies that are higher than the cutoff
				dft2[v*resized.width + u] = c_rep(0.0f);
			}
		}
	}


	/***** Inverse Transform *****/

	// Pointer similar to temp for the inverse transform's values
	Complex *invTemp = malloc(sizeof(Complex)*resized.width*resized.height);

	// IDFT on the columns 
	for(int x = 0; x < resized.width; x++) {
    		for(int y = 0; y < resized.height; y++) {
        		Complex sum = {0.0, 0.0};
        		for(int v = 0; v < resized.height; v++) {
            			sum = c_add(sum, c_mul(dft2[v*resized.width + x], c_exp(c_mul(i, c_rep(2.0*PI*v*y/resized.height)))));
        		}
        		invTemp[y*resized.width + x] = sum;
    		}
	}

	
	// Inverse DFT on rows and directly store as unsigned char
	for(int y = 0; y < resized.height; y++) {
    		for(int x = 0; x < resized.width; x++) {
        	Complex sum = {0.0, 0.0};
        		for(int u = 0; u < resized.width; u++) {
            			sum = c_add(sum, c_mul(invTemp[y*resized.width + u], c_exp(c_mul(i, c_rep(2.0*PI*u*x/resized.width)))));
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
	writePGM(argv[2], &img);	

	// Free memory and close resources
	free(rData);
	free(temp);
	free(invTemp);
	free(dft2);

	return 0;
}
