#include "polynom.h"
#include <iostream>

int main()
{
  Polynom test{5};
  std::cout << test.order_get() << std::endl;
};
