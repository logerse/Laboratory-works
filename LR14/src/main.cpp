#include "UsualMatrix.h"
#include <iostream>

int main()
{
  int **arrayFirst = new int*[2];
  *arrayFirst = new int[2];
  *(arrayFirst + 1) = new int[2];

  UsualMatrix testFirst(2,2,(const int **)arrayFirst);
  UsualMatrix testSecond(testFirst);

  testFirst = testFirst + testSecond;

  std::cout << testFirst.GetElement(1,1) << std::endl;

  for(int i : {0,1})
    delete arrayFirst[i];

  delete arrayFirst;
};
