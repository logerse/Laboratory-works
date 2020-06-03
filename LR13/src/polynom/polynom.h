#pragma once

#include "../binpol.h"
#include <exception>

class Polynom {
  private:
    int order;
    int module;
    unsigned char *coefs;

    void PrintCoefficent(const int deg);
  public:
    Polynom(const int mod, const int ord, const unsigned char coef[]);
    Polynom(const Polynom&);
    ~Polynom() { delete this->coefs; };
    
    void Print(void) const;
};

