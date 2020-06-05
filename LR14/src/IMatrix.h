#include <stdexcept>


struct size_st {
  int n;
  int m;

  size_st(void) : n {0}, m {0} {};
  bool operator= (size_st& sz) { return ((n == sz.n) && (m == sz.m)); };
};


class IMatrix {
protected:
  size_st size {};
  void InitData(void) {};
  void DeleteData(void)  {};

public:
  int GetElement(const int i, const int j) { return 0; };
  int SetElement(const int i, const int j, const int value) { return 0; };
  
  template<typename T> T& operator= (const T& mx);
  template<typename T> T operator+ (const T& mx) const;
};

template<typename T>
T&
IMatrix::operator= (const T& mx)
{
  this->DeleteData();
  this->size = mx.size;
  this->InitData();

  for(int i=0; i<this->size.n; i++)
    for(int j=0; j<this->size.m; j++)
      this->SetElement(i, j, mx.GetElement(i, j));

  return (*this);
};
  

template<typename T>
T
IMatrix::operator+ (const T& mx)
const
{
  if(!(this->size == mx.size)) 
    throw std::length_error("Matrix: matrix size not equate for addition.");

  T result {*this};
  
  for(int i=0; i<result.size.n; i++)
    for(int j=0; j<result.size.m; j++)
      result.SetElement(i, j, mx.GetElement(i, j) + result.GetElement(i, j) );

  return result;
};
