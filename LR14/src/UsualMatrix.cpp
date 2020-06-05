#include "UsualMatrix.h"

//--- Constructors ---//


UsualMatrix::UsualMatrix(const UsualMatrix& mx)
  : size {mx.size.n, mx.size.m}
{
  this->InitData();

  for(int i=0; i < this->size.n; i++) {
    for(int j=0; j < this->size.m; j++)
      this->data[i][j] = mx.data[i][j];
  };
};


UsualMatrix::UsualMatrix(const int size_n, const int size_m)
  : size {size_n, size_m}
{
  if(!(size.n * size.m > 0) || size.n < 0) 
    throw std::length_error("[*] Matrix: некорректный размер матрицы");

  this->InitData();

  for(int i=0; i < this->size.n; i++) {
    for(int j=0; j < this->size.m; j++)
      this->data[i][j] = 0;
  };
};


UsualMatrix::UsualMatrix(const int size_n, const int size_m, const int **data)
  : size {size_n, size_m}
{
  if(!(size.n * size.m > 0) || size.n < 0) 
    throw std::length_error("[*] Matrix: некорректный размер матрицы");

  this->InitData();

  for(int i=0; i<size_n; i++) {
    for(int j=0; j<size_m; j++)
      this->data[i][j] = data[i][j];
  };
};


//--- Destructor ---//

UsualMatrix::~UsualMatrix(void)
{
  this->DeleteData();
};


//--- Functions ---//

//-- Interface --//

int 
UsualMatrix::GetElement(const int i, const int j)
const
{
  return this->data[i][j];
};


int
UsualMatrix::SetElement(const int i, const int j, const int value)
{
  return this->data[i][j] = value;
};

//-- Implementation --//

void
UsualMatrix::DeleteData(void)
{
  for(int i=0; i<this->size.n; i++)
    delete this->data[i];
  delete data;
};


void
UsualMatrix::InitData(void)
{
  this->data = new (std::nothrow) int*[this->size.n];
  for(int i=0; i<this->size.n; i++) {
    this->data[i] = new int[this->size.m];
  };
};
//--- END ---//
