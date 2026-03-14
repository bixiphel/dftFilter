#ifndef COMPLEX_H
#define COMPLEX_H

typedef struct {
	double real;
	double imag;
} Complex;

Complex c_add(Complex z1, Complex z2);
Complex c_sub(Complex z1, Complex z2);
Complex c_mul(Complex z1, Complex z2);
Complex c_exp(Complex z1);

#endif
