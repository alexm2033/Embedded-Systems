#include "mbed.h"
#include "Complex_C.hpp"


// TASK - write and test complexConjugate, complexNegate, complexSubtract, complexMagnitude, complexMultiply and complexDivide

int main() {
    printf("\n\nTASK312\n");

    //Create instance of a complex number
    ComplexNumber_C p = {2.0, 3.0};
    ComplexNumber_C q = {1.0, 1.0};
    complexDisplay("p", p);
    complexDisplay("q", q);
 
    ComplexNumber_C sum = complexAdd(p, q);
    complexDisplay("p+q", sum);

    ComplexNumber_C con = complexConjugate(p);
    complexDisplay("conjugate p", con);

    ComplexNumber_C neg =complexNegate(p);
    complexDisplay("p negated", neg);

    double mag = complexMagnitude(p);
    printf("magnitude p %f\n", mag);

    ComplexNumber_C sub = complexSubtract(p, q);
    complexDisplay("p-q", sub);

    ComplexNumber_C mult = complexMultiply(p, q);
    complexDisplay("p*q", mult);

    ComplexNumber_C div = complexDivide(p, q);
    complexDisplay("p/q", div);

    complexNegateInplace(p);
    complexDisplay("p negated", p);

    complexConjugateInplace(q);
    complexDisplay("the complex conjugate of q", q);
    
        
    while (true) {
    }
}
