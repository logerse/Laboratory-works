#pragma once

#include "../binpol.h"
#include <exception>

class Polynom {
  private:
    int order;
    int module;
    unsigned char *coefs;

    void PrintCoefficent(int deg) const;
  public:
    Polynom(const Polynom&);
    Polynom(const int mod, const int ord, const unsigned char coef[]);
    ~Polynom() { delete this->coefs; };
    
    Polynom& operator= (const Polynom&);
    Polynom& operator+ (const Polynom&) const;

    void Print(void) const;
};

