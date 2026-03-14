#include "complex.h"

Complex c_add(Complex a, Complex b) {
	Complex z = {a.real + b.real, a.imag + b.imag};
	return z;	
}

Complex c_sub(Complex a, Complex b) {
	Complex z = {a.real - b.real, a.imag - b.imag};
	return z;	
}

Complex c_mul(Complex a, Complex b) {
	Complex z = {a.real*b.real - a.imag*b.imag, a.real*b.imag + a.imag*b.real}; 
	return z;	
}
