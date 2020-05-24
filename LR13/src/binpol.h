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
    void refreshOrder(void);
  public:
    BinPolynom(void);
    BinPolynom(const int order);
    BinPolynom(const int order, const char *coef) { init(order,coef); };
    ~BinPolynom();

    BinPolynom& operator= (BinPolynom&);
    BinPolynom& operator+ (BinPolynom&) const;
    BinPolynom& operator+= (BinPolynom& bp) { return (*this = *this + bp); };
    BinPolynom& operator- (BinPolynom& bp) const { return *this + bp;};
    BinPolynom& operator-= (BinPolynom& bp) { return (*this = *this + bp); };

    // Getters
    int order_get(void) const { return order_; };
    char *coef_get(void) const { return coefficents_; };
    // --- //

    // Testing
    void testRefreshOrder(void) { refreshOrder(); };
    // --- //
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
