#include "SparseMatrix.h"

#ifndef IOSTREAM
#include <iostream>
#define IOSTREAM
#endif

//--- Constructors ---//


SparseMatrix::SparseMatrix(const SparseMatrix& mx)
{
  sz = mx.sz;
  this->InitData();

  Node_st* cur;
  cur = mx.data.HEAD;
  while(cur != mx.data.TAIL) {
    this->data.PushBack(cur->row, cur->column, cur->value);
    cur = cur->next;
  };

  this->data.PushBack(cur->row, cur->column, cur->value);
};


SparseMatrix::SparseMatrix(const int size_n, const int size_m)
{
  sz.n = size_n;
  sz.m = size_m;
  if(!(sz.n * sz.m > 0) || sz.n < 0) 
    throw std::length_error("[*] Matrix: некорректный размер матрицы");

  this->InitData();
};


SparseMatrix::SparseMatrix(const int size_n, const int size_m, const int **data_)
{
  sz.n = size_n;
  sz.m = size_m;
  if(!(sz.n * sz.m > 0) || sz.n < 0) 
    throw std::length_error("[*] Matrix: некорректный размер матрицы");

  this->InitData();

  for(int i=0; i<size_n; i++) 
    for(int j=0; j<size_m; j++)
      if(data_[i][j])
        data.PushBack(i, j, data_[i][j]);
};


//--- Destructor ---//

SparseMatrix::~SparseMatrix(void)
{
  this->DeleteData();
};


//--- Functions ---//


//-- Operators --//


SparseMatrix
SparseMatrix::operator= (const SparseMatrix mx)
{
  Equate(&mx);
  return (*this);
};
 

SparseMatrix
SparseMatrix::operator+ (const SparseMatrix mx)
const
{
  SparseMatrix result = {*this};
  result.AddMatrix(&mx);
  return result;
};


SparseMatrix
SparseMatrix::operator*(const int scal)
const
{
  SparseMatrix result {*this};
  result.MultOnScalar(scal);
  return result;
};


SparseMatrix
SparseMatrix::operator* (const SparseMatrix mx)
const
{
  SparseMatrix result {this->sz.n, this->sz.m};
  result.MultOnMatrix(this, &mx);
  return result;
};

//-- Interface --//

int 
SparseMatrix::GetElement(const int i, const int j)
const
{
  if((i > sz.n || i < 0) || (j > sz.m || j < 0))
    throw std::length_error("Getting element: Incorrect row or column.");

  Node_st* result = data.FindElement(i, j);
  if(result == nullptr) return 0;
  return result->value;
};


int
SparseMatrix::SetElement(const int i, const int j, const int value)
{
  if((i > sz.n || i < 0) || (j > sz.m || j < 0))
    throw std::length_error("Getting element: Incorrect row or column.");

  // Optimization trick
  // If element exist and not equal zero -> we start finding them.
  //
  // [] [x] [] [] [] [] ... []
  // []
  // []
  // [x]
  // []
  // ...
  // []
  //
  if(data.buffer == nullptr) {
    int max_size {(sz.m >= sz.n) ? sz.m : sz.n};
    data.buffer = new char[max_size];
    for(int i=0; i<max_size; i++)
      data.buffer[i] = 0;
  }

  Node_st* result = nullptr;
  if(data.buffer[i] & 2 != 0 && data.buffer[j] & 1 != 0) 
    result = data.FindElement(i, j);

  if(result == nullptr && value != 0) {
    data.PushBack(i, j, value);
    data.buffer[i] |= 2; data.buffer[j] |= 1;
    return value;

  } else if( result != nullptr ) {
    if(value != 0) return (result->value = value);
    data.buffer[i] &= ~2; data.buffer[j] &= ~1;
    data.DeleteNode(result);
  };

  return value;
};

//-- Implementation --//

void
SparseMatrix::DeleteData(void)
{};


void
SparseMatrix::InitData(void)
{
  data.TAIL = (data.HEAD = nullptr);
};

//--- END ---//
