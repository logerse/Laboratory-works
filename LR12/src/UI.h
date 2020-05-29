#pragma once

class UserInterface {
private:
  void PrintMenu(void);
  void PrintMenu(const char*);
  int GetUserChoice(void);

  void CreateMatrix(void);
  void EquateMatrix(void);
  void AdditionMatrix(void);
  void SubtractionMatrix(void);
  void MultiplicationMatrix(void);
  void DivisionMatrix(void);
public:
  void Start(void);
};
