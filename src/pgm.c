#include <stdio.h>
#include <stdlib.h>
#include "pgm.h"

void readPGM(const char *filename, PGMimage *img) {
	// Attempt to open file in read-binary mode
	FILE *fp = fopen(filename, "rb");

	// Verify the file opened; exits program if file cannot be opened.
	if(!fp) {
		printf("Error opening file.\n");
		exit(10);
	}


	// Helper variables to parse file
	int c;			// Stores PGM file format (2 or 5 depending on the file)
	char buf[1024];		// Buffer used to skips any comment lines in hte file 
	
	// Skips comment lines in the file
	while((c = fgetc(fp)) == '#') {
		fgets(buf, sizeof(buf), fp);
	}
	ungetc(c, fp);


	// Get the magic nubmer for the PGM file ("Px", where 'x' is 2 or 5)
	if (fscanf(fp, "P%d\n", &c) != 1) {
		printf ("read error ....");
		fclose(fp);
       		exit(11);
	}
	// Validates the magic number is 2 or 5 (the only formats allowed by the PGM specification)
	if (c != 5 && c != 2) {
		printf ("read error ....");
		fclose(fp);
		exit(12);
	}


	// Skips any more comment lines left in the file
	while ((c=fgetc(fp)) == '#')
		fgets(buf, 1024, fp);
	ungetc(c, fp);

	// Attempts to read the image dimensions 
	if (fscanf(fp, "%d%d%d",&img->width, &img->height, &img->max) != 3) {
		printf("failed to read width/height/max\n");
		fclose(fp);
		exit(13);	
	}
	printf("Width=%d, Height=%d \nMaximum=%d\n",img->width,img->height,img->max);
	
	// Allocates memory for the image if possible	
	img->data = malloc(img->width*img->height);
	getc(fp);
	if(!img->data) {
		printf("Memory allocation failed\n");
		fclose(fp);
		exit(14);
	}
		

	// Processes the file according to the magic number
	if (c==5) {
		// Under PGM specification, 5 corresponds to binary values
		fread(img->data, 1, img->width * img->height, fp);
	} else if(c == 2) {
		// 2 corresponds to ASCII values
		int val;

		for(int i = 0; i < img->width*img->height; i++) {
			fscanf(fp, "%d", &val);
			img->data[i] = val;
		}
	}

	// Close file when finished reading
	fclose(fp);
}

void writePGM(const char *filename, const PGMimage *img);
