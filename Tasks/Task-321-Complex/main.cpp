#include "mbed.h"
#include "ComplexNumber.hpp"

// main() runs in its own thread in the OS
int main()
{
    ComplexNumber c1(2.0,3.0);
    ComplexNumber c2(1.0,-1.0);
    ComplexNumber c1_copy = c1;
    c1.add(c2);   //c1 = c1 + c2
    c1.display();
    c1_copy.display();
    
    ComplexNumber c3 = c1.addedTo(c2);
    c3.display();
    c3.conjugate();
    c3.display();
    c3.negate();
    c3.display();
    ComplexNumber c4 = c3.negated();
    c4.display();

    ComplexNumber c5(2.0,3.0);
    ComplexNumber c6(3.0,-2.0);
    ComplexNumber c7 = c5.subtractFrom(c6);
    c6.subtract(c5);
    c7.display();
    c6.display();

    ComplexNumber c8(2.0,3.0);
    ComplexNumber c9(3.0,2.0);
    ComplexNumber c10 = c8.multiplyWith(c9);
    cout<<"****"<<endl;
    c8.display();
    c9.display();
    c10.display();
    cout<<"****"<<endl;
    c9.multiply(c8);
    c9.display();
    c10.display();


    //Create new scope
    {
        ComplexNumber test(1.0);
        test.display();
    }
    //test is now out of scope and should be destroyed

    while (true);
}

