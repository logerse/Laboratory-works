#include "UI.h"

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#define CLS  printf("\E[H\E[J");
#define END_OF_FOO(foo) \
END:\
\
  std::cout << "1. Well, it's work." << std::endl;\
  std::cout << "2. I wanna more polynoms!" << std::endl;\
  switch(GetUserChoice()) {\
    case 1:\
      return;\
    case 2:\
      (foo)();\
      return;\
    default:\
      std::cout << "[X] Beep-boop whaat?" << std::endl;\
      goto END;\
  };


Polynom
UILR13::CreatePolynom(void)
{
  int ord {0};
  int mod {0};
  std::cout << "#--- Creating Polynom ---#" << std::endl;
  std::cout << "[*] Input module: " << std::endl;
  std::cin >> mod;
  std::cout << "[*] Input order: ";
  std::cin >> ord;

  unsigned char  *array = (unsigned char *) malloc(ord+1);

  for(int i=0; i<=ord; i++) {
    std::cout << "x^" << i << ": ";
    std::cin >> array[i];
  };

  Polynom test(mod, ord, array);
  free(array);

  return test;
};


void UILR13::CreatePolynomOption(void)
{
  CLS
  Polynom test = CreatePolynom();
  std::cout << "#--- Result ---#" << std::endl;
  test.Print();

  END_OF_FOO(CreatePolynomOption)
};


#define BEGIN_OF_TEST \
  CLS\
  std::cout << "#--- Creating polynom A ---#" << std::endl;\
  Polynom testFirst = CreatePolynom();\
 \
  CLS\
  std::cout << "#--- Creating polynom B ---#" << std::endl;\
  Polynom testSecond = CreatePolynom();\
\
  CLS\
  std::cout << "#--- Polynom A ---#" << std::endl;\
  testFirst.Print();\
  std::cout << "#--- Polynom B ---#" << std::endl;\
  testSecond.Print();

#define RESULT_OF_TEST \

void 
UILR13::EquatePolynoms(void)
{
  BEGIN_OF_TEST

  std::cout << "" << std::endl;
  std::cout << "#--- A = B ---#" << std::endl;
  testFirst = testSecond;
  
  RESULT_OF_TEST
  testFirst.Print();
  puts("");

  END_OF_FOO(EquatePolynoms)
};


void
UILR13::AdditionPolynoms(void)
{
  BEGIN_OF_TEST

  std::cout << "" << std::endl;
  std::cout << "#--- C = B + A ---#" << std::endl;
  testSecond = testSecond + testFirst;

  RESULT_OF_TEST
  testSecond.Print();
  puts("");

  END_OF_FOO(AdditionPolynoms)
};

/*

void
UILR13::SubtrationPolynoms(void)
{
  BEGIN_OF_TEST

  std::cout << "" << std::endl;
  std::cout << "#--- C = B - A ---#" << std::endl;
  testSecond -= testFirst;

  RESULT_OF_TEST
  testSecond.Print();
  puts("");

  END_OF_FOO(SubtrationPolynoms)
};


void
UILR13::MultiplicationPolynoms(void)
{
  BEGIN_OF_TEST

  std::cout << "" << std::endl;
  std::cout << "#--- C = B * A ---#" << std::endl;
  testSecond *= testFirst;

  RESULT_OF_TEST
  testSecond.Print();
  puts("");

  END_OF_FOO(SubtrationPolynoms)
};


void
UILR13::LogicalOperations(void)
{
  BEGIN_OF_TEST;
  
PRINT_MENU:
  CLS
  std::cout << "" << std::endl;
  std::cout << "#--- Operations ---#" << std::endl;
  std::cout << "1. A == B" << std::endl;
  std::cout << "2. A != B" << std::endl;
  std::cout << "3. A > B" << std::endl;
  std::cout << "4. A >= B" << std::endl;
  std::cout << "5. A < B" << std::endl;
  std::cout << "6. A <= B" << std::endl;
  std::cout << "0. Exit" << std::endl;
 
  switch(GetUserChoice()) {
    case 1:
      CLS
      std::cout << "#--- Result operation == ---#" << std::endl;
      (testFirst == testSecond) ? puts("True") : puts("False");
      break;

    case 2:
      CLS
      std::cout << "#--- Result operation != ---#" << std::endl;
      (testFirst != testSecond) ? puts("True") : puts("False");
      break;

    case 3:
      CLS
      std::cout << "#--- Result operation > ---#" << std::endl;
      (testFirst > testSecond) ? puts("True") : puts("False");
      break;

    case 4:
      CLS
      std::cout << "#--- Result operation >= ---#" << std::endl;
      (testFirst >= testSecond) ? puts("True") : puts("False");
      break;

    case 5:
      CLS
      std::cout << "#--- Result operation < ---#" << std::endl;
      (testFirst < testSecond) ? puts("True") : puts("False");
      break;

    case 6:
      CLS
      std::cout << "#--- Result operation <= ---#" << std::endl;
      (testFirst <= testSecond) ? puts("True") : puts("False");
      break;
   
    case 0:
      return;

    default:
      std::cout << "Incorrect option." << std::endl;
      goto PRINT_MENU;
  };

  std::cout << "#---------------------------#" << std::endl;
  std::cout << "[*] Continue?" << std::endl;
  std::cout << "1. Sure!" << std::endl;
  std::cout << "2. No thx" << std::endl;
  
  switch(GetUserChoice()) {
    case 1:
      goto PRINT_MENU;
    default:
      return;
  };
};

*/
void
UILR13::PrintMenuOptions(void)
{
  std::cout << "1. Create polynom" << std::endl;
  std::cout << "2. Equate polynoms" << std::endl;
  std::cout << "3. Addition polynoms" << std::endl;
  std::cout << "4. Subtration polynoms" << std::endl;
  std::cout << "5. Multiplication polynoms" << std::endl;
  std::cout << "6. Logical operations test" << std::endl;
  std::cout << "0. Exit" << std::endl;
};


void 
UILR13::Start(void)
{
  PrintMenu();
  
  for(;;) {
    switch(GetUserChoice()) {
      case 1:
        CreatePolynomOption();
        break;

      case 2:
        EquatePolynoms();
        break;

      case 3:
        AdditionPolynoms();
        break;

      case 4:
        SubtrationPolynoms();
        break;
/*
      case 5:
        MultiplicationPolynoms();
        break;
     
      case 6:
        LogicalOperations();
        break;
*/
      case 0:
        return;
      default:
        PrintMenu("Incorrect option");
    };

    PrintMenu();
  };
};


#undef END_OF_FOO
