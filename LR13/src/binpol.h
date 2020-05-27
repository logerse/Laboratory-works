#pragma once

#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <exception>
#endif


class BinPolynom {
  private:
    int order_;
    unsigned char *coefficents_;
    void init(const int, const unsigned char*);
    void refreshOrder(void);
    BinPolynom& multOnMonom(const int orderOfMonom);
  public:
    BinPolynom(void);
    BinPolynom(const int order);
    BinPolynom(const int order, const unsigned char *coef) { init(order,coef); };
    ~BinPolynom();

    BinPolynom& operator= (BinPolynom&);
    BinPolynom& operator+ (BinPolynom&) const;
    BinPolynom& operator- (BinPolynom& bp) const { return *this + bp;};
    BinPolynom& operator+= (BinPolynom& bp) { return (*this = *this + bp); };
    BinPolynom& operator-= (BinPolynom& bp) { return (*this = *this + bp); };

    BinPolynom& operator* (BinPolynom&) const;

    // Getters
    int order_get(void) const { return order_; };
    unsigned char *coef_get(void) const { return coefficents_; };
    // --- //

    // Testing
    void testRefreshOrder(void) { refreshOrder(); };
    BinPolynom& testMultOnMonom(const int orderOfMonom) {return multOnMonom(orderOfMonom);};
    // --- //
};


class testBinPolynom : public BinPolynom {

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

struct InvalidOrderOfMonom : public  std::exception {
  const char *what() const throw()
  {
    return "Invalid order of monomial.";
  };
};

//------//
