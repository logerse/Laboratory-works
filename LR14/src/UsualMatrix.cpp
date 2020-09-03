#include "UsualMatrix.h"

#ifndef IOSTREAM
#include <iostream>
#define IOSTREAM
#endif

//--- Constructors ---//


UsualMatrix::UsualMatrix(const UsualMatrix& mx)
{
  sz = mx.sz;
  this->InitData();

  for(int i=0; i < this->sz.n; i++) {
    for(int j=0; j < this->sz.m; j++)
      this->data[i][j] = mx.data[i][j];
  };
};


UsualMatrix::UsualMatrix(const int size_n, const int size_m)
{
  sz.n = size_n;
  sz.m = size_m;
  if(!(sz.n * sz.m > 0) || sz.n < 0) 
    throw std::length_error("[*] Matrix: некорректный размер матрицы");

  this->InitData();

  for(int i=0; i < this->sz.n; i++) {
    for(int j=0; j < this->sz.m; j++)
      this->data[i][j] = 0;
  };
};


UsualMatrix::UsualMatrix(const int size_n, const int size_m, const int **data)
{
  sz.n = size_n; sz.m = size_m;
  if(!(sz.n * sz.m > 0) || sz.n < 0) 
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


//-- Operators --//


UsualMatrix
UsualMatrix::operator= (const UsualMatrix mx)
{
  Equate(&mx);
  return (*this);
};
 

UsualMatrix
UsualMatrix::operator+ (const UsualMatrix mx)
const
{
  UsualMatrix result = {*this};
  result.AddMatrix(&mx);
  return result;
};


UsualMatrix
UsualMatrix::operator*(const int scal)
const
{
  UsualMatrix result {*this};
  result.MultOnScalar(scal);
  return result;
};


UsualMatrix
UsualMatrix::operator* (const UsualMatrix mx)
const
{
  UsualMatrix result {this->sz.n, this->sz.m};
  result.MultOnMatrix(this, &mx);
  return result;
};

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
  for(int i=0; i<this->sz.n; i++)
    delete this->data[i];
  delete data;
};


void
UsualMatrix::InitData(void)
{
  this->data = new (std::nothrow) int*[this->sz.n];
  for(int i=0; i<this->sz.n; i++) {
    this->data[i] = new int[this->sz.m];
  };
};

//--- END ---//
