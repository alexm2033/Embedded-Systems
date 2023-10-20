//
//  ComplexNumber.hpp
//  Complex
//
//  Created by Nicholas Outram on 21/09/2017.
//  Copyright © 2017 Nicholas Outram. All rights reserved.
//

#ifndef ComplexNumber_hpp
#define ComplexNumber_hpp

#include <stdio.h>
#include <iostream>
using namespace std;

class ComplexNumber {
private:
    double real;
    double imag;
    
public:
    //Default constructor
    ComplexNumber() {
        this->real = 0.0;
        this->imag = 0.0;
    }
    
    //Constructor 2 - default of second parameter is 1 if not specified
    ComplexNumber(const double r, const double i=0.0) {
        this->real = r;
        this->imag = i;
    }
    
    //Copy constructors
    ComplexNumber(const ComplexNumber& c) {
        this->imag = c.imag;
        this->real = c.real;
    }

    //Destructor
    ~ComplexNumber() {
        cout << "Bye'ee" << endl;
    }
    
    //Read-only accessors
    double getReal() {
        return this->real;
    }

    double getImag() {
        return this->imag;
    }

    //Conjugate - verb, so perform in place
    void conjugate() {
        this->imag *= -1.0;
    }
    
    //Conjugated - adjective, so return new copy
    ComplexNumber conjugated() {
        return ComplexNumber(this->real, -1.0*this->imag);
    }

    void negate() {
        this->real *= -1.0;
        this->imag *= -1.0;
    }

    ComplexNumber negated() {
        return ComplexNumber(-1.0*this->real, -1.0*this->imag);
    }

    void subtract(const ComplexNumber& c) {
        this->real -= c.real;
        this->imag -= c.imag;
    }

    ComplexNumber subtractFrom(const ComplexNumber& c) {
        //return ComplexNumber(this->real - c.real, this->imag - c.imag);
        return ComplexNumber(c.real - this->real, c.imag - this->imag);
    }

    void multiply(ComplexNumber& c) {
        double x = this->real;
        double y = this->imag;
        cout<<"x="<<x<<endl;
        cout<<"y="<<y<<endl;
        cout<<"c.real ="<<c.real<<endl;
        cout<<"c.imag ="<<c.imag<<endl;
        this->real = ((x*c.real)-(y*c.imag));
        this->imag = ((x*c.imag)+(y*c.real));
    }

    ComplexNumber multiplyWith(const ComplexNumber& c) {
        double a = this->real;
        double b = this-> imag;
        double x = (a*c.real)-(b*c.imag);
        double y = (a*c.imag)+(b*c.real);
        return ComplexNumber(real=x, imag=y);
    }

    void divide(ComplexNumber& c) {
        this->real = ((this->real*c.real)+(this->imag*c.imag))/((c.real*c.real)+(c.imag*c.imag));
        this->imag = ((this->imag*c.real)-(this->real*c.imag))/((c.real*c.real)+(c.imag*c.imag));
    }

    ComplexNumber divideWith(ComplexNumber& c) {
        double x = ((this->real*c.real)+(this->imag*c.imag))/((c.real*c.real)+(c.imag*c.imag));
        double y = ((this->imag*c.real)-(this->real*c.imag))/((c.real*c.real)+(c.imag*c.imag));
        return ComplexNumber(this->real=x, this->imag=y);
    }


    //Add in place
    void add(const ComplexNumber& c) {
        this->real += c.real;
        this->imag += c.imag;
    }
    
    //Add
    ComplexNumber addedTo(const ComplexNumber& c) {
        return ComplexNumber(this->real+c.real, this->imag+c.imag);
    }
    
    //Display
    void display() {
        cout << this->real << " + " << this->imag << "j" << endl;
    }
    
};


#endif /* ComplexNumber_hpp */
