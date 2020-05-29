#include "UI.h"
#include "matrix.h"
#include <iostream>
#include <cstdlib>

void UserInterface::PrintMenu(void)
{
  printf("\E[H");
  printf("\E[J");
  std::cout <<  "#------ MENU -------#" <<  std::endl;
  std::cout <<  "1. Exit." <<  std::endl;
  std::cout <<  "2. Create." <<  std::endl;
  std::cout <<  "3. Equate." <<  std::endl;
  std::cout <<  "4. Addition." <<  std::endl;
  std::cout <<  "5. Subtraction." <<  std::endl;
  std::cout <<  "6. Multiplication." <<  std::endl;
  std::cout <<  "7. Division." <<  std::endl;
  std::cout <<  "#-------------------#" <<  std::endl;
};


void UserInterface::PrintMenu(const  char* err)
{
  PrintMenu();
  std::cout << "[*] Error: " << err << std::endl;
  std::cout <<  "#-------------------#" <<  std::endl;
};


int UserInterface::GetUserChoice(void)
{
  int result = 0;
  std::cout << ">>> ";
  std::cin >> result;
  return result;
};


SqrMatrix createMatrix(void)
{
      int size = 0;
      std::cout << "[*] Input size of matrix: " << std::endl;
      std::cin >> size;
      double **array = (double **) malloc(size * 8);
      std::cout << "[*] Input array:" << std::endl; 

      for(int i=0; i < size; i++)
        for(int j=0; j<size; j++) {
          if(j == 0) array[i] = (double *) malloc(size * sizeof(double));
          std::cin >> array[i][j];
        };

      SqrMatrix MATRIX(array, size);

      for(int i=0; i < size; i++)
         free(array[i]);

      free(array);

      return MATRIX;
};


void UserInterface::CreateMatrix(void)
{
  int size = 0;

  printf("\E[H");
  printf("\E[J");
  std::cout << "[*] Matrix will initializated via only SIZE or ARRAY and SIZE?" << std::endl;
  std::cout << "1. Only size." << std::endl;
  std::cout << "2. Size and array." << std::endl;
  std::cout << "3. Exit." << std::endl;
  
  switch(GetUserChoice()) {
    case 1: {
      std::cout << "[*] Input size of matrix: " << std::endl;
      std::cin >> size;
      SqrMatrix MATRIX(size);
      std::cout << "[*] Result:" << std::endl;
      MATRIX.print();

      std::cout << "[*] What to do?" << std::endl;
      std::cout << "1. Get determinant." << std::endl;
      std::cout << "2. Transpose." << std::endl;
      std::cout << "3. Reverse." << std::endl;
      std::cout << "4. Get rang." << std::endl;

      switch(GetUserChoice()) {
        case 1:
	      std::cout << "[*] Determinant is " << MATRIX.get_determinant() << std::endl;
	      break;
	    case 2:
	      std::cout << "[*] Result of transpose:" << std::endl;
	      MATRIX.transpose();
	      MATRIX.print();
	      break;
	    case 3:
	      std::cout << "[*] Result of reverse:" << std::endl;
	      (MATRIX.reverse()).print();
          break;
        case 4:
          std::cout << "[*] Rang is " << MATRIX.calcRang() << std::endl;
          break;
        default:
          std::cout << "[X] Invalid option." << std::endl;
      };
      }
      break;
    case 2:{
      SqrMatrix MATRIX = createMatrix();
      std::cout << "[*] Result:" << std::endl;
      MATRIX.print();
      std::cout << "[*] What to do?" << std::endl;
      std::cout << "1. Get determinant." << std::endl;
      std::cout << "2. Transpose." << std::endl;
      std::cout << "3. Reverse." << std::endl;
      std::cout << "4. Get rang." << std::endl;

      switch(GetUserChoice()) {
        case 1:
	  std::cout << "[*] Determinant is " << MATRIX.get_determinant() << std::endl;
	  break;
	case 2:
	  std::cout << "[*] Result of transpose:" << std::endl;
	  MATRIX.transpose();
	  MATRIX.print();
	  break;
	case 3:
	  std::cout << "[*] Result of reverse:" << std::endl;
	  (MATRIX.reverse()).print();
        case 4:
          std::cout << "[*] Rang is " << MATRIX.calcRang() << std::endl;
          break;
        default:
          std::cout << "[X] Invalid option." << std::endl;
      };
 
      }
      break;
    case 3:
      return;
    default:
      std::cout << "[X] Incorrect option." << std::endl;
      return;
  };

END:

  std::cout << "1. Well, it's work." << std::endl;
  std::cout << "2. I wanna more matrix!" << std::endl;

  switch(GetUserChoice()) {
    case 1:
      return;
    case 2:
      CreateMatrix();
      return;
    default:
      std::cout << "[X] Beep-boop whaat?" << std::endl;
      goto END;
  };
};


void UserInterface::EquateMatrix(void)
{
      std::cout << "#--- MATRIX A ---#" <<  std::endl;
      SqrMatrix MATRIX_A = createMatrix();
      std::cout << "#--- MATRIX B ---#" <<  std::endl;
      SqrMatrix MATRIX_B = createMatrix();

      printf("\E[H");
      printf("\E[J");

      std::cout << "[*] Matrix A:" << std::endl;
      MATRIX_A.print();
     
      std::cout << "[*] Matrix B:" << std::endl;
      MATRIX_B.print();

      std::cout << std::endl;
   
      MATRIX_A = MATRIX_B; 

      std::cout << "#--- Result ---#" << std::endl;

      std::cout << "[*] Matrix A:" << std::endl;
      MATRIX_A.print();
     
      std::cout << "[*] Matrix B:" << std::endl;
      MATRIX_B.print();

 END:

  std::cout << "1. Well, it's work." << std::endl;
  std::cout << "2. I wanna more matrix!" << std::endl;

  switch(GetUserChoice()) {
    case 1:
      return;
    case 2:
      EquateMatrix();
      return;
    default:
      std::cout << "[X] Beep-boop whaat?" << std::endl;
      goto END;
  };
};


void UserInterface::AdditionMatrix(void) 
{
  std::cout << "#--- MATRIX A ---#" <<  std::endl;
  SqrMatrix MATRIX_A = createMatrix();
  std::cout << "#--- MATRIX B ---#" <<  std::endl;
  SqrMatrix MATRIX_B = createMatrix();
  
  printf("\E[H");
  printf("\E[J");
  std::cout << "[*] C = A + B" << std::endl;
  std::cout << "#--- Result ---#" << std::endl;
  std::cout << "[*] Matrix C:" << std::endl;
  (MATRIX_A + MATRIX_B).print();

 END:

  std::cout << "1. Well, it's work." << std::endl;
  std::cout << "2. I wanna more matrix!" << std::endl;

  switch(GetUserChoice()) {
    case 1:
      return;
    case 2:
      AdditionMatrix();
      return;
    default:
      std::cout << "[X] Beep-boop whaat?" << std::endl;
      goto END;
  };
};


void UserInterface::SubtractionMatrix(void)
{
  printf("\E[H");
  printf("\E[J");
  std::cout << "#--- MATRIX A ---#" <<  std::endl;
  SqrMatrix MATRIX_A = createMatrix();
  std::cout << "#--- MATRIX B ---#" <<  std::endl;
  SqrMatrix MATRIX_B = createMatrix();
  
  printf("\E[H");
  printf("\E[J");
  std::cout << "[*] C = A - B" << std::endl;
  std::cout << "#--- Result ---#" << std::endl;
  std::cout << "[*] Matrix C:" << std::endl;
  (MATRIX_A - MATRIX_B).print();

 END:

  std::cout << "1. Well, it's work." << std::endl;
  std::cout << "2. I wanna more matrix!" << std::endl;

  switch(GetUserChoice()) {
    case 1:
      return;
    case 2:
      SubtractionMatrix();
      return;
    default:
      std::cout << "[X] Beep-boop whaat?" << std::endl;
      goto END;
  };

};


void UserInterface::MultiplicationMatrix(void)
{
   printf("\E[H");
   printf("\E[J");
 
   std::cout << "[*] Multiplication matrix on:" << std::endl;
   std::cout << "1. Scalar." << std::endl;
   std::cout << "2. Matrix." << std::endl;

   switch(GetUserChoice()) {
     case 1:
       {
         double scalar = 0;
         std::cout << "[*] Input scalar:" << std::endl;
         std::cin >> scalar;

         SqrMatrix MATRIX = createMatrix();

         std::cout << "#--- Result ---#" << std::endl;
         (MATRIX * scalar).print();
       }
       break;
      case 2:
        {
          std::cout << "#--- MATRIX A ---#" <<  std::endl;
          SqrMatrix MATRIX_A = createMatrix();
          std::cout << "#--- MATRIX B ---#" <<  std::endl;
          SqrMatrix MATRIX_B = createMatrix();
   
          printf("\E[H");
          printf("\E[J");
          std::cout << "[*] C = A * B" << std::endl;
          std::cout << "#--- Result ---#" << std::endl;
          std::cout << "[*] Matrix C:" << std::endl;
          (MATRIX_A * MATRIX_B).print();
        }
        break;
      default:
        std::cout << "[X] Incorrect option." << std::endl;
   };
 END:

  std::cout << "1. Well, it's work." << std::endl;
  std::cout << "2. I wanna more matrix!" << std::endl;

  switch(GetUserChoice()) {
    case 1:
      return;
    case 2:
      MultiplicationMatrix();
      return;
    default:
      std::cout << "[X] Beep-boop whaat?" << std::endl;
      goto END;
  };
};


void UserInterface::DivisionMatrix(void) 
{
   printf("\E[H");
   printf("\E[J");
 
   std::cout << "[*] Division matrix on:" << std::endl;
   std::cout << "1. Scalar." << std::endl;
   std::cout << "2. Matrix." << std::endl;

   switch(GetUserChoice()) {
     case 1:
       {
         double scalar = 0;
         std::cout << "[*] Input scalar:" << std::endl;
         std::cin >> scalar;

         SqrMatrix MATRIX = createMatrix();

         std::cout << "#--- Result ---#" << std::endl;
         (MATRIX / scalar).print();
       }
       break;
      case 2:
        {
          std::cout << "#--- MATRIX A ---#" <<  std::endl;
          SqrMatrix MATRIX_A = createMatrix();
          std::cout << "#--- MATRIX B ---#" <<  std::endl;
          SqrMatrix MATRIX_B = createMatrix();
   
          printf("\E[H");
          printf("\E[J");
          std::cout << "[*] C = A / B" << std::endl;
          std::cout << "#--- Result ---#" << std::endl;
          std::cout << "[*] Matrix C:" << std::endl;
          (MATRIX_A / MATRIX_B).print();
        }
        break;
      default:
        std::cout << "[X] Incorrect option." << std::endl;
   };
 END:

  std::cout << "1. Well, it's work." << std::endl;
  std::cout << "2. I wanna more matrix!" << std::endl;

  switch(GetUserChoice()) {
    case 1:
      return;
    case 2:
      DivisionMatrix();
      return;
    default:
      std::cout << "[X] Beep-boop whaat?" << std::endl;
      goto END;
  };
};


void UserInterface::Start(void)
{
  PrintMenu();
  for(;;) {
    switch(GetUserChoice()) {
      case 1:
        return;
      case 2:
        CreateMatrix();
        break;
      case 3:
        EquateMatrix();
        break;
      case 4:
        AdditionMatrix();
        break;
      case 5:
        SubtractionMatrix();
        break;
      case 6:
        MultiplicationMatrix();
        break;
      case 7:
        DivisionMatrix();
        break;
      default:
        PrintMenu("[X] Incorrect option.");
        continue;
    };
    PrintMenu();
  };
};
