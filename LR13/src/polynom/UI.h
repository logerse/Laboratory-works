#pragma once
#include "../../../UI/UI.h"
#include "polynom.h"

class UILR13 : public UserInterface {
private:
  Polynom CreatePolynom(void);
  void CreatePolynomOption(void);
  void EquatePolynoms(void);
//  void AdditionPolynoms(void);
//  void SubtrationPolynoms(void);
//  void MultiplicationPolynoms(void);
//  void LogicalOperations(void);

protected:
  void PrintMenuOptions(void);
public:
  void Start(void);
};
