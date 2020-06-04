#pragma once

#include "../binpol.h"
#include <exception>
#include <memory>

class Polynom {
  private:
    int order;
    int module;
    char *coefs;

    void PrintCoefficent(const int deg) const;
    Polynom& MultOnMonom(const int deg, const int coef) const;
  public:
    Polynom(const Polynom&);
    Polynom(const int mod, const int order);
    Polynom(const int mod, const int ord, const char coef[]);
    ~Polynom() { delete this->coefs; };
    
    Polynom& operator= (const Polynom&);
    Polynom& operator+ (const Polynom&) const;
    Polynom& operator- (const Polynom&) const;
    Polynom& operator* (const Polynom&) const;
    Polynom& operator+= (const Polynom& polynom) { return (*this = *this + polynom); };
    Polynom& operator-= (const Polynom& polynom) { return (*this = *this - polynom); };
    Polynom& operator*= (const Polynom& polynom) { return (*this = *this * polynom); };


    void Print(void) const;
};

