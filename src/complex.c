#include "complex.h"
#include <math.h>

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
