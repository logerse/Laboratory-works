#include "polynom.h"
#include <iostream>


Polynom::Polynom(const int mod, const int ord, const unsigned char coef[])
 : order {ord}, module {mod}, coefs{new unsigned char [ord + 1]}
{
  try {
    for(int i=0; i<=this->order; i++)
      this->coefs[i] = coef[i] % this->module;
  }
  catch(...) {
    throw IncorrectOrder();
  }
};


Polynom::Polynom(const Polynom& polynom)
  : order {polynom.order}, module {polynom.module}, coefs {new unsigned char[order+1]} 
{
  for(int i=0; i<=order; i++)
    coefs[i] = polynom.coefs[i];
};


//--- Functions ---//


void
Polynom::PrintCoefficent(int deg)
const
{
  if(deg > order) return;

  if(coefs[deg] != 1)
    std::cout << (int) coefs[deg]; 
};


void
Polynom::Print(void)
const
{
  for(int i=order; i>= 0; i--) {
    if( coefs[i] ) {
      if( i == order ) {
        if(i != 0 && i != 1) {
          PrintCoefficent(i);
          std::cout << "x^" << i;
        }
        else if (i==0){
          PrintCoefficent(i);
	  puts("");
        }
        else if (i==1){
          PrintCoefficent(i);
          std::cout << "x";
        }
      }
      else if(i > 1){
        std::cout << " + ";
        PrintCoefficent(i);
        std::cout << "x^" << i;
      }
      else if (i == 1){
        std::cout << " + ";
        PrintCoefficent(i);
        std::cout << "x";
      }
      else if (i == 0) {
        std::cout << " + " << (int) coefs[i];
      }
    }
  };

  std::cout << " (mod " << module << ")" << std::endl;
};


//--- Operators ---//


Polynom&
Polynom::operator= (const Polynom& polynom)
{
  order = polynom.order;
  module = polynom.module;
  delete coefs;

  coefs = new unsigned char[order+1];
  for(int i=0; i<=order; i++)
    coefs[i] = polynom.coefs[i];
  
  return (*this);
};


Polynom&
Polynom::operator+ (const Polynom& AA)
const
{
  Polynom& maxPolynom = (AA.order >= this->order) ? &AA : this;
  Polynom& minPolynom = (AA.order < this->order) ? &AA : this;
  Polynom& result = new Polynom( maxPolynom );

  for(int i=0; i <= minPolynom.order; i++) {
    result.coefs[i] = (maxPolynom.coefs[i] + minPolynom.coefs[i]) % this->module;
  };

  result.module = this->module;

  return result;
};
