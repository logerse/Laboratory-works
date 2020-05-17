#pragma once

class BinPolynom {
  private:
    int order_;
    char *coefficents_;
    void init(int, char*);
  public:
    BinPolynom() { init(0,NULL); };
    BinPolynom(const int order) { init(order, NULL); };
    BinPolynom(const int order, const char *coef) { init(order,coef); };
    ~BinPolynom() { free(coefficents_); };
};

