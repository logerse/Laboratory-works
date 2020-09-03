#pragma once
#include "../../../UI/UI.h"
#include "../SparseMatrix.h"
#include "../UsualMatrix.h"

class UILR14 : public UserInterface {
private:
  SparseMatrix *SM_a, *SM_b;
  UsualMatrix *UM_a, *UM_b;
  int flag = 0;

  void GenerateUsualMatrices(void);
  void GenerateSparseMatrices(void);
  void ActionsWithMatrices(void);
  void PrintActionsMenu(void);
  void PrintActionsMenu(const char *err);

  void AddMatrices(void);
  void MultMatrices(void);
  void ShowMatrices(void);

protected:
  void PrintMenuOptions(void);

public:
  void Start(void);
  ~UILR14(void) {
    if(flag & 4) { delete SM_a; delete SM_b; };
    if(flag & 1) { delete UM_a; delete UM_b; };
  };
};
