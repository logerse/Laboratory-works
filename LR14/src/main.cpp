#include "UsualMatrix.h"
#include <iostream>

int main()
{
  int **arrayFirst = new int*[2];
  
  for(int i=0; i<2; i++) {
    arrayFirst[i] = new int[2];
    for(int j=0; j<2; j++)
      arrayFirst[i][j] = 1;
  };

  UsualMatrix testFirst(2,2,(const int **)arrayFirst);
  UsualMatrix testSecond(testFirst);

  testFirst = testSecond;

  std::cout << testFirst.GetElement(1,1) << std::endl;

  for(int i : {0,1})
    delete arrayFirst[i];

  delete arrayFirst;
};
