#include "UI.h"

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef STRING
#define STRING
#include <string>
#endif

#define CLS  printf("\E[H\E[J");

#define __SIZE__ 1000

void 
UILR14::GenerateSparseMatrices(void)
{
  SM_a = new SparseMatrix(__SIZE__,__SIZE__);
  SM_b = new SparseMatrix(__SIZE__,__SIZE__);

  int v;
  for(int i=0; i<__SIZE__; i++)
    for(int j=0; j<__SIZE__; j++) {
      v = (random() * (random() % 5)) % 1000;
      if(v) SM_a->data.PushBack(i, j, v);
      v = (random() * (random() % 5)) % 1000;
      if(v) SM_b->data.PushBack(i, j, v);
    };
    
  ActionsWithMatrices();
};


void 
UILR14::GenerateUsualMatrices(void)
{
  UM_a = new UsualMatrix(__SIZE__,__SIZE__);
  UM_b = new UsualMatrix(__SIZE__,__SIZE__);

  for(int i=0; i<__SIZE__; i++)
    for(int j=0; j<__SIZE__; j++) {
      UM_a->SetElement(i, j, (random()) % 1000);
      UM_b->SetElement(i, j, (random()) % 1000);
    };

  ActionsWithMatrices();
};


void
UILR14::ShowMatrices(void)
{
  std::string name;
  switch(flag) {
    case 0b1100:
      name = "SparseA.png";
      SM_a->SaveAsPng(name);

      name = "SparseB.png";
      SM_b->SaveAsPng(name);
      break;

    case 0b0011:
      name = "UsualA.png";
      UM_a->SaveAsPng(name);

      name = "UsualB.png";
      UM_b->SaveAsPng(name);
      break;
  };
};


void
UILR14::PrintActionsMenu(void)
{
  CLS;
  std::cout << "#--- Action with matrices ---#" << std::endl;
  std::cout << "1. Addition" << std::endl;
  std::cout << "2. Multiplication" << std::endl;
  std::cout << "3. Show matrices" << std::endl;
  std::cout << "0. Exit" << std::endl;
};


void
UILR14::PrintActionsMenu(const char *err) 
{
  PrintActionsMenu();
  std::cout << "#----------------------------#" << std::endl;
  std::cout << "[X] Error: " << err << std::endl;
  std::cout << "#----------------------------#" << std::endl;
};


void
UILR14::AddMatrices(void) 
{
  std::string name = "result.png";
  SparseMatrix result_sparse {10,10};
  UsualMatrix result_usual {10,10};
  if(flag) {
    switch(flag) {
      case 0b1100:
        result_sparse = *SM_a + *SM_b;
	result_sparse.SaveAsPng(name);
	break;

      case 0b0011:
	result_usual =  *UM_a + *UM_b;
	result_usual.SaveAsPng(name);
	break;
    };
  }  
};


void
UILR14::MultMatrices(void)
{
  std::string name = "result.png";
  SparseMatrix result_sparse {10,10};
  UsualMatrix result_usual {10,10};
  if(flag) {
    switch(flag) {
      case 0b1100:
        result_sparse = *SM_a * *SM_b;
	result_sparse.SaveAsPng(name);
	break;

      case 0b0011:
	result_usual =  *UM_a * *UM_b;
	result_usual.SaveAsPng(name);
	break;
    };
  } 
};


void
UILR14::ActionsWithMatrices(void)
{
  PrintActionsMenu();
  for(;;) {

    switch(GetUserChoice()) {
      case 0:
	return;
      case 1:
	AddMatrices();
        break;

      case 2:
	MultMatrices();
        break;

      case 3:
	ShowMatrices();
	break;

      default:
	PrintActionsMenu("Incorrect option.");
	continue;
    };
    
    PrintActionsMenu();
  };
};


void
UILR14::PrintMenuOptions(void)
{
  std::cout << "1. Sparse matrices" << std::endl;
  std::cout << "2. Usual matrices" << std::endl;
  std::cout << "0. Exit" << std::endl;
};


void 
UILR14::Start(void)
{
  srand(time(NULL));

  PrintMenu();
  
  for(;;) {
    switch(GetUserChoice()) {
      case 0:
        return;

      case 1:
	flag |= 0b1100;
	GenerateSparseMatrices();
        return;

      case 2:
	flag |= 0b0011;
	GenerateUsualMatrices();
	return;

      default:
        PrintMenu("Incorrect option");
    };

    PrintMenu();
  };
};


#undef END_OF_FOO
