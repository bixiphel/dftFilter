#include "complex.h"
#include <math.h>
#include <stdio.h>

// Mathematical functions
Complex c_add(Complex z1, Complex z2) {
	Complex z = {z1.real + z2.real, z1.imag + z2.imag};
	return z;	
}

Complex c_sub(Complex z1, Complex z2) {
	Complex z = {z1.real - z2.real, z1.imag - z2.imag};
	return z;	
}

Complex c_mul(Complex z1, Complex z2) {
	Complex z = {z1.real*z2.real - z1.imag*z2.imag, z1.real*z2.imag + z1.imag*z2.real}; 
	return z;	
}

Complex c_exp(Complex z1) {
	Complex z = {exp(z1.real)*cos(z1.imag), exp(z1.real)*sin(z1.imag)};
	return z;
}


// Utility functions
Complex c_rep(double x) {
	Complex z = {x, 0};
	return z;	
}

double c_real(Complex z) {
	return z.real;
}

double c_imag(Complex z) {
	return z.imag;
}

void c_print(Complex z1) {
	if(z1.imag > 0) {
		printf("%f + %fi", z1.real, z1.imag);
	} else {
		printf("%f - %fi", z1.real, fabs(z1.imag));
	}
}
