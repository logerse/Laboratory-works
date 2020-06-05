#include <stdexcept>


struct size_st {
public:
  int n;
  int m;
  size_st(void) : n {0}, m {0} {};
  size_st(const int n_, const int m_) : n {n_}, m {m_}{};
  bool operator== (const size_st& sz) const { return ((n == sz.n) && (m == sz.m)); };
};


class IMatrix {
protected:
  virtual void InitData(void) {};
  virtual void DeleteData(void)  {};

public:
  size_st sz {};
  virtual int GetElement(const int i, const int j) { puts("GetElement"); return i+j; };
  virtual int SetElement(const int i, const int j, const int value) { puts("SetElement"); return i+j+value; };
  
  template<typename T> T& operator= (const T& mx);
  template<typename T> T& operator+ (const T& mx) const;
};

template<typename T>
T& IMatrix::operator= (const T& mx)
{
  this->DeleteData();
  this->sz = mx.sz;
  this->InitData();

  for(int i=0; i<this->sz.n; i++)
    for(int j=0; j<this->sz.m; j++)
      this->SetElement(i, j, mx.GetElement(i, j));

  return (*this);
};
  

template<typename T>
T& IMatrix::operator+ (const T& mx)
const
{
  if(!(this->sz == mx.sz)) 
    throw std::length_error("Matrix: matrix size not equate for addition.");

  T& result = (*new T(mx));
  
  int newValue = 0;
  for(int i=0; i<result.sz.n; i++)
    for(int j=0; j<result.sz.m; j++) {
      newValue =/* GetElement(i, j); + */mx.GetElement(i, j);
      result.SetElement(i, j, newValue);
    };

  return result;
};