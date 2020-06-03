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
  : order {AA.order}, module {AA.module}, coefs {new unsigned char {order+1}} 
{
  for(int i=0; i<=order; i++)
    coefs[i] = AA.coefs[i];
};


//--- Functions ---//


void
Polynom::PrintCoefficent(const int deg)
{
  if(deg > order) return;
  
  std::cout << coefs[deg]; 
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
        };
        else if (i==0){
          PrintCoefficent(i);
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
        std::cout << " + ";
        PrintCoefficent(i);
      }
    }
  };
};
