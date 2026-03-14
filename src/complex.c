#include "complex.h"

Complex c_add(Complex a, Complex b) {
	Complex z = {a.real + b.real, a.imag + b.imag};
	return z;	
}
