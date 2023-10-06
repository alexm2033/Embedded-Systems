#include "stdio.h"
#include "mbed.h"
#include "Complex_C.hpp"


ComplexNumber_C complexAdd(const ComplexNumber_C a, const ComplexNumber_C b) {
    ComplexNumber_C y = a;
    y.real += b.real;
    y.imag += b.imag;
    return y;
}

ComplexNumber_C complexConjugate(const ComplexNumber_C a) {
    ComplexNumber_C y = a;
    y.imag *= -1;
    return y;
}

ComplexNumber_C complexNegate(const ComplexNumber_C a) {
    ComplexNumber_C y = a;
    y.imag *= -1;
    y.real *= -1;
    return y;
}

ComplexNumber_C complexSubtract(const ComplexNumber_C a, ComplexNumber_C b) {
    b = complexNegate(b);
    ComplexNumber_C y = complexAdd(a, b);
    return y;
}

double complexMagnitude(ComplexNumber_C a) {
    double y = sqrt((a.real*a.real)+(a.imag*a.imag));
    return y;
}

ComplexNumber_C complexMultiply(ComplexNumber_C a, ComplexNumber_C b) {
    ComplexNumber_C y = {.real=0, .imag=0};
    y.real = (((a.real*b.real)-(a.imag*b.imag))+((a.real*b.imag)+(a.imag*b.real)));
    return y;
}

ComplexNumber_C complexDivide(ComplexNumber_C a, ComplexNumber_C b) {
    double num1 = (a.imag*b.real)+(a.imag*b.imag);
    double num2 = (a.imag*b.real)-(a.real*b.imag);
    double den  = ((b.real*b.real)+(b.imag*b.imag));
    ComplexNumber_C y = {.real=0, .imag=0};
    y.real = (num1/den);
    y.imag = (num2/den);
    return y;
}


void complexDisplay(const char *strName, const ComplexNumber_C u) {
    printf("%s = %f + j%f\n", strName, u.real, u.imag);
}

void complexConjugateInplace(ComplexNumber_C& u) {
    u.imag *= -1;
}

void complexNegateInplace(ComplexNumber_C& u) {
    u.real *= -1;
    u.imag *= -1;
}