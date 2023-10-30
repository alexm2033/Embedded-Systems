#include "DoubleNumber.hpp"
#include "ComplexNumber.hpp"
#include <type_traits>

int main()
{
    //Constructor Function overloading 
    ComplexNumber c0(1.0, 2.0);
    DoubleNumber  d0(3.0);
    ComplexNumber c1;
    DoubleNumber  d1;
    
    //This uses the operator= function
    d1 = 5.0;

    //Write the value as a string
    cout << d1.asString() << endl;

    //Now overrides the default =
    c1 = c0;

    //Now overrides the parent asString
    cout << c1.asString() << endl;

    //Challenge - try and understand this ;)
    cout << c1.asDoubleNumber().asString() << endl;

    //TODO - write an overloaded + operator
    DoubleNumber sum1 = c0 + c1 + d0 + d1;
    cout << sum1 << endl;

    cout<<"c0 = "<<c0.asString()<<" c1 = "<<c1.asString()<<endl;
    ComplexNumber sum2 = c0 + c1;
    cout<<"c0 + c1 = "<<sum2.asString()<<endl;

    while (true) {

    }
}

