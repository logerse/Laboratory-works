#include "IMatrix.h"
#include "List/LinkedList.h"

class SparseMatrix : public IMatrix {
protected:
  void InitData(void);
  void DeleteData(void);

public:
  LinkedList data {};
  SparseMatrix(const SparseMatrix&);
  SparseMatrix(const int size_n, const int size_m);
  SparseMatrix(const int size_n, const int size_m, const int **data);
  ~SparseMatrix(void);

  //--//

  SparseMatrix operator= (const SparseMatrix mx);
  SparseMatrix operator+ (const SparseMatrix mx) const; 
  SparseMatrix operator+= (const SparseMatrix mx) { return (*this = *this + mx); }; 
  
  SparseMatrix operator* (const int scal) const;
  SparseMatrix operator- (const SparseMatrix mx) const { return *this + mx*(-1); };
  SparseMatrix operator-= (const SparseMatrix mx) { return (*this = *this - mx); };

  SparseMatrix operator* (const SparseMatrix mx) const;
  SparseMatrix operator*= (const SparseMatrix mx) { return (*this = *this - mx); };

  //--//

  int GetElement(const int i, const int j) const;
  int SetElement(const int i, const int j, const int value);

  int GetSizeN(void) const {return sz.n;};
  int GetSizeM(void) const {return sz.m;};
};

