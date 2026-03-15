#ifndef PGM_H
#define PGM_H

typedef struct {
	int width;
	int height;
	int max;
	unsigned char *data;	
} PGMimage;

void readPGM(const char *filename, PGMimage *img);
void writePGM(const char *filename, const PGMimage *img);

#endif
