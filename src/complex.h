#ifndef COMPLEX_H
#define COMPLEX_H

typedef struct {
	double real;
	double imag;
} Complex;

// Mathematical functions
Complex c_add(Complex z1, Complex z2);
Complex c_sub(Complex z1, Complex z2);
Complex c_mul(Complex z1, Complex z2);
Complex c_exp(Complex z1);

// Utility functions
Complex c_rep(double x);
double c_real(Complex z);
double c_imag(Complex z);
void c_print(Complex z1);

#endif
