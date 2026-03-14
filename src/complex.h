#ifndef COMPLEX_H
#define COMPLEX_H

typedef struct {
	double real;
	double imag;
} Complex;

Complex c_add(Complex a, Complex b);
Complex c_mul(Complex a, Complex b);

#endif
