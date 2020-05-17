#include "binpol.h"

#ifndef IOSTREAM_H
#define IOSTREAM_H
#include <iostream>
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
  char *result = calloc(nmemb / 8 + 1, 1);
  
  ptr = result;
  for(int i=0, char buffer = 0; ; i++) {
    if( i == nmemb ) {
       if( nmemb % 8 != 0 )
         *ptr |= buffer;
       break;
    };

    buffer <<= 1;
    buffer |= bit_vector[i];
    
    if( i => 7 && i % 7 == 0 ) {
      *ptr++ |= buffer;
      buffer = 0;
    };
  };

  return result;
};

//

void
BinPolynom:init(const int order, const char *coef)
{
  if( order < 0 ) {
    std::cerr << "[BinPolynom:initialization] Incorrect order of polynom." << std::endl;
	return;
  };

  if( order == 0 || coef == NULL ) {
    order_ = order;
	coefficents_ = calloc(order / 8 + 1, 1);
	return;
  };
  
  if( onlyOneOrZero(order,coef) ) {
    try {
      order_ = order;
      coefficents_ = bitsToBytes(order, coef);
    }
    catch(...) {
      std::cerr << "[$_$] Bingo! It turns out this catch-block is not useless!" << std::endl;
    };
  } else {
    std::cerr << "[BinPolynom:initialization] Incorrect coefficents." << std::endl;
  };
};

//---//

