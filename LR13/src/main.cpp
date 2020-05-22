#ifndef IOSTREAM_H
#define IOSTREAM_H
#include <iostream>
#endif

#include "binpol.h"

int
main()
{
  BinPolynom test;
  char *ptr = test.coef_get();
  std::cout << (ptr[0] == 0) << std::endl;
};
