#include "IMatrix.h"

class UsualMatrix : public IMatrix {
private:
  int **data;

protected:
  void InitData(void);
  void DeleteData(void);

public:
  UsualMatrix(const UsualMatrix&);
  UsualMatrix(const int size_n, const int size_m);
  UsualMatrix(const int size_n, const int size_m, const int **data);
  ~UsualMatrix(void);

  //--//

  UsualMatrix operator= (const UsualMatrix mx);
  UsualMatrix operator+ (const UsualMatrix mx) const; 
  UsualMatrix operator+= (const UsualMatrix mx) { return (*this = *this + mx); }; 
  
  UsualMatrix operator* (const int scal) const;
  UsualMatrix operator- (const UsualMatrix mx) const { return *this + mx*(-1); };
  UsualMatrix operator-= (const UsualMatrix mx) { return (*this = *this - mx); };

  UsualMatrix operator* (const UsualMatrix mx) const;
  UsualMatrix operator*= (const UsualMatrix mx) { return (*this = *this - mx); };

  //--//

  int GetElement(const int i, const int j) const;
  int SetElement(const int i, const int j, const int value);

  int GetSizeN(void) const {return sz.n;};
  int GetSizeM(void) const {return sz.m;};
};

