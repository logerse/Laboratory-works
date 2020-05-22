#pragma once

#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <exception>
#endif


class BinPolynom {
  private:
    int order_;
    char *coefficents_;
    void init(const int, const char*);
  public:
    BinPolynom(void);
    BinPolynom(const int order);
    BinPolynom(const int order, const char *coef) { init(order,coef); };
    ~BinPolynom();

    BinPolynom operator= (BinPolynom);

   // Getters
   int order_get(void) const { return order_; };
   char* coef_get(void) const { return coefficents_; };
   //---//

   // Setters
   int order_set(const int order) { return order_=order; };
   char* coef_set(char * new_coef) { return (coefficents_ = new_coef); };
   const char coef_set(const int index, const char value)  
     { return (coefficents_[index] = value); };
   //---//
};


//------//


struct IncorrectOrder : public  std::exception {
  const char *what() const throw()
  {
    return "Incorrect order of polynom.";
  };
};


struct IncorrectCoefs : public  std::exception {
  const char *what() const throw()
  {
    return "Incorrect coefficents.";
  };
};

//------//
