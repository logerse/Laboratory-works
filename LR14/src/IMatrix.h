#include <stdexcept>
#pragma once

#ifndef FSTREAM
#define FSTREAM
#include <fstream>
#endif

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef STRING
#define STRING
#include <string>
#endif


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
  virtual void InitData(void) = 0;
  virtual void DeleteData(void) = 0;
  
  void Equate(const IMatrix* mx) {
    this->DeleteData();
    this->sz = mx->sz;
    this->InitData();                  
                                   
    for(int i=0; i<this->sz.n; i++)  
      for(int j=0; j<this->sz.m; j++)
	this->SetElement(i, j, mx->GetElement(i, j));
  };

  void MultOnScalar(const int scalar) {
    for(int i=0; i<this->sz.n; i++)
      for(int j=0; j<this->sz.m; j++)
        this->SetElement(i, j, this->GetElement(i, j) * scalar);
  };

  void MultOnMatrix(const IMatrix* mxA, const IMatrix* mxB) {
    if(mxA->sz.n != mxB->sz.m)
      throw std::length_error("Mutipication: Multiplication of two matrices is defined if and only if the number of columns of the left matrix is the same as the number of rows of the right matrix.");
  
    int newEl = 0;
    for(int i=0; i<mxA->sz.n; i++) { 
      for(int j=0; j<mxB->sz.m; j++) {
        for(int k=0; k<mxA->sz.n; k++) {   
          newEl = this->GetElement(i,j);
          newEl += mxA->GetElement(i,k) * mxB->GetElement(k,j);
          this->SetElement(i, j, newEl);                    
        };
      };
    };  
  };

  void AddMatrix(const IMatrix* mx) {  
    if(!(this->sz == mx->sz))
      throw std::length_error("Matrix: matrix size not equate for addition.");

    int newValue = 0;
    for(int i=0; i<this->sz.n; i++)
      for(int j=0; j<this->sz.m; j++) {
        newValue = this->GetElement(i, j) + mx->GetElement(i, j);
        this->SetElement(i, j, newValue);
      };
 };

public:
  size_st sz{}; // NOTE: Getter and setter
  virtual int GetElement(const int i, const int j) const = 0;
  virtual int SetElement(const int i, const int j, const int value) = 0;

  void Print(void) const {
    for(int i=0; i<this->sz.n; i++) {
      for(int j=0; j<this-> sz.m; j++) {
        std::cout << this->GetElement(i,j) << " ";
      };
      std::cout << std::endl;
    }
  };

  void SaveAsPng(std::string result_name) const {
    std::ofstream dat;
    dat.open("data.dat");
    for(int i=0; i<this->sz.n; i++) {
      for(int j=0; j<this->sz.m; j++)
        dat << this->GetElement(i,j) << " "; 
      dat << std::endl;
    };
    dat.close();

    std::ofstream script;
    script.open("script.p");
    script << "set terminal png size 500,500" << std::endl;
    script << "set output 'data/" << result_name.data() << std::endl;
    script << "plot 'data.dat' matrix with image" << std::endl;
    script.close();

    system("gnuplot script.p");
  };

  virtual ~IMatrix() {};
};
