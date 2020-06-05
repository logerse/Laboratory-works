#include "IMatrix.h"

class UsualMatrix : public IMatrix {
private:
  int **data;

protected:
  void InitData(void);
  void DeleteData(void);

public:
  size_st sz {};
  UsualMatrix(const UsualMatrix&);
  UsualMatrix(const int size_n, const int size_m);
  UsualMatrix(const int size_n, const int size_m, const int **data);
  ~UsualMatrix(void);

  int GetElement(const int i, const int j) const;
  int SetElement(const int i, const int j, const int value);

  int GetSizeN(void) const {return sz.n;};
  int GetSizeM(void) const {return sz.m;};
};
