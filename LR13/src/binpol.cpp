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
         buffer <<= 8 - (nmemb % 8);
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

//

inline static int
findCluster(const int nmemb, const char * data)
{
  int cluster=0;
  for(; data[cluster] != 0 && cluster < (nmemb / 8 + 2); cluster++);
  return cluster;
};

void
BinPolynom::refreshOrder(void)
{
  const int cluster=findCluster(order_, coefficents_);

  if(cluster == 0) {
    order_ = 0;
    return;
  };

  int newOrder = cluster * 8;
  unsigned char clusterContent = coefficents_[cluster - 1];
  
  while(clusterContent % 2 == 0) {
    newOrder -= 1;
    clusterContent >>= 1;
  };

  order_ = newOrder - 1;
};

//---//

BinPolynom& BinPolynom::operator= (BinPolynom& bp)
{
  const int ord = bp.order_get();
  const char * const coefs = bp.coef_get(); 

  if(order_ != ord) {
    order_ = ord;
    coefficents_ = (char*) calloc(ord / 8 + 1, 1);
  };

  for(int i=0; i<ord / 8 +1; i++)
    coefficents_[i] = coefs[i];
  
  return *this;
};

BinPolynom& BinPolynom::operator+ (BinPolynom& bp) const
{
  const int ord = bp.order_;
  const char * const coefs = bp.coefficents_; 
  
  const int newOrder = (order_ >= ord) ? order_ : ord;
  BinPolynom *resultPolynom = new BinPolynom(newOrder); // BUG: memory floating

  for(int i=0; i<=newOrder; i++){
    if(i <= order_ && i <= ord)
      resultPolynom->coefficents_[i] = coefficents_[i] ^ bp.coefficents_[i];
    else if(i <= order_)
      resultPolynom->coefficents_[i] ^= coefficents_[i];
    else if(i <= ord) 
      resultPolynom->coefficents_[i] ^= bp.coefficents_[i];
  };

  resultPolynom->refreshOrder();

  return *resultPolynom;
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

