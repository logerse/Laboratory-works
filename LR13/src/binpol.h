#pragma once

class BinPolynom {
  private:
   int order_;
   char *coefficents_;
   void init(int, char*);
  public:
   BinPolynom() { init(0,NULL); };
   ~BinPolynom() { free(coefficents_); };
};
~                                                                                              
~         
