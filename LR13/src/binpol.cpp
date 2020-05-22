#include "binpol.h"

#ifndef IOSTREAM_H
#define IOSTREAM_H
#include <iostream>
#endif

#ifndef CSTDLIB_H
#define CSTDLIB_H
#include <cstdlib>
#endif

#ifndef CSTDDEF_H
#define CSTDDEF_H
#include <cstddef>
#endif

//---//

inline static bool
onlyOneAndZero(const int nmemb, const char *data)
{
  int i=0;
  for(; i<nmemb; i++)
    if( data[i] != 0 && data[i] != 1 ) break;
  return (i == nmemb);
};

//
/* Example: {1,1,0,1,0,0,0,0,1,1,1,1,0,1,0,1} => {0xd0,0xf5}*/
char *
bitsToBytes(const int nmemb, const char *bit_vector)
{
  char *ptr;
  char *result = (char *) calloc(nmemb / 8 + 1, 1);
  
  ptr = result;
  for(int i=0, buffer = 0; ; i++) {
    if( i == nmemb ) {
       if( nmemb % 8 != 0 )
         *ptr |= buffer;
       break;
    };

    buffer <<= 1;
    buffer |= bit_vector[i];
    
    if( i >= 7 && i % 7 == 0 ) {
      *ptr++ |= buffer;
      buffer = 0;
    };
  };

  return result;
};

//

void
BinPolynom::init(const int order, const char *coef)
{
  if( order < 0 ) {
    coefficents_ = (char *) malloc(1);
    throw IncorrectOrder();
  };

  if( order == 0 || coef == NULL ) {
    order_ = order;
	coefficents_ = (char *) calloc(order / 8 + 1, 1);
	return;
  };
  
  if( onlyOneAndZero(order + 1,coef) ) {
    try {
      order_ = order;
      coefficents_ = bitsToBytes(order + 1, coef);
    }
    catch(...) {
      std::cerr << "[$_$] Bingo! It turns out this catch-block is not useless!" << std::endl;
    };
  } else {
	throw IncorrectCoefs();
  };
};

//---//

BinPolynom BinPolynom::operator= (BinPolynom bp) 
{
  const int ord = bp.order_get();
  const char * const coefs = bp.coef_get(); 

  if(order_ != ord) {
    free(coefficents_);
	order_set(ord);
    coef_set((char*) calloc(ord / 8 + 1,1));
    //coef_set((char *) calloc(ord + 1, 1));
  };

  for(int i=0; i<ord+1; i++)
    coefficents_[i] = coefs[i];
  
  return *this;
};


//---//

BinPolynom::~BinPolynom(void) 
{
  free(coefficents_);
};

BinPolynom::BinPolynom(void)
{
  init(0, NULL);
};

BinPolynom::BinPolynom(const int order)
{
  init(order, NULL);
};

