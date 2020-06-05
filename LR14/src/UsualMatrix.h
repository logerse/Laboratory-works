#include "IMatrix.h"

class UsualMatrix : public IMatrix {
private:
  int **data;
  size_st size {};

protected:
  void InitData(void);
  void DeleteData(void);

public:
  UsualMatrix(const UsualMatrix&);
  UsualMatrix(const int size_n, const int size_m);
  UsualMatrix(const int size_n, const int size_m, const int **data);
  ~UsualMatrix(void);

  int GetElement(const int i, const int j) const;
  int SetElement(const int i, const int j, const int value);

  int GetSizeN(void) const {return size.n;};
  int GetSizeM(void) const {return size.m;};
};

