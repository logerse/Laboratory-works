#include "polynom.h"
#include <iostream>
#include <cmath>


Polynom::Polynom(const int mod, const int ord, const char coef[])
 : order {ord}, module {mod}, coefs{new char [ord + 1]}
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
  : order {polynom.order}, module {polynom.module}, coefs {new char[order+1]} 
{
  for(int i=0; i<=order; i++)
    coefs[i] = polynom.coefs[i];
};


Polynom::Polynom(const int mod, const int ord)
  : order {ord}, module {mod}, coefs {new char[ord+1]}
{
  for(int i=0; i<=ord; i++)
    coefs[i] = 0;
};


//--- Functions ---//


Polynom&
Polynom::MultOnMonom(const int deg, const int coef)
const
{
  int index = this->order;
  Polynom& result = *(new Polynom(this->module, this->order + deg));
  for(int i=this->order+deg; index >= 0 && i >= 0 ; i--) {
    result.coefs[i] = (this->coefs[index--] * coef) % result.module;
  };
  return result;
};


void
Polynom::PrintCoefficent(int deg)
const
{
  if(deg > order) return;

  if(coefs[deg] != 1)
    std::cout << (int) std::abs(coefs[deg]); 
};


void
Polynom::Print(void)
const
{
  for(int i=order; i>= 0; i--) {
    if( coefs[i] ) {
      if( i == order ) {
	if(coefs[i] < 0) std::cout << "-";
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
        std::cout << ((coefs[i] > 0) ? " + ": " - ");
        PrintCoefficent(i);
        std::cout << "x^" << i;
      }
      else if (i == 1){
        std::cout << ((coefs[i] > 0) ? " + ": " - ");
        PrintCoefficent(i);
        std::cout << "x";
      }
      else if (i == 0) {
        std::cout << ((coefs[i] > 0) ? " + " : " - ") ;
	std::cout << (int) std::abs(coefs[i]);
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

  coefs = new char[order+1];
  for(int i=0; i<=order; i++)
    coefs[i] = polynom.coefs[i];
  
  return (*this);
};


Polynom&
Polynom::operator+ (const Polynom& polynom)
const
{
  Polynom& maxPolynom = (Polynom&) ((polynom.order >= this->order) ? polynom : (*this));
  Polynom& minPolynom = (Polynom&) ((polynom.order < this->order) ? polynom : (*this));
  Polynom& result = (*(new Polynom( maxPolynom )));

  for(int i=0; i <= minPolynom.order; i++) {
    result.coefs[i] = (maxPolynom.coefs[i] + minPolynom.coefs[i]) % this->module;
  };

  result.module = this->module;

  return result;
};


Polynom&
Polynom::operator- (const Polynom& polynom)
const
{
  Polynom& maxPolynom {(Polynom&) ((polynom.order >= this->order) ? polynom : (*this))};
  Polynom& minPolynom {(Polynom&) ((polynom.order < this->order) ? polynom : (*this))};

  Polynom& result { *(new Polynom( maxPolynom )) };

  for(int i=0; i <= minPolynom.order; i++)
    result.coefs[i] = (maxPolynom.coefs[i] - minPolynom.coefs[i]) % this->module;

  result.module = this->module;

  return result;
};


Polynom&
Polynom::operator* (const Polynom& polynom)
const
{
  Polynom& result { *(new Polynom(this->module, this->order + polynom.order)) };

  for(int i {polynom.order}; i >= 0; i--) {
     if(polynom.coefs[i])
	result += this->MultOnMonom(i, polynom.coefs[i]);
  };

  return result;
};
