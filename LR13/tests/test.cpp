#include <gtest/gtest.h>
#include "../src/binpol.h"
#include <iostream>

//-- BinPolynom initialization functions --//

TEST(BP_init, without_parametrs)
{
  BinPolynom test;
  ASSERT_EQ(test.order_get(), 0);
  ASSERT_EQ(*test.coef_get(), 0);
};


TEST(BP_init, with_valid_order)
{
  BinPolynom test(2);
  ASSERT_EQ(test.order_get(), 2);

  char *c = test.coef_get();
  ASSERT_EQ(c[0], 0);
  ASSERT_EQ(c[1], 0);
};


TEST(BP_init, with_valid_order_and_coefs)
{
  char validCoefs[] = {1,1};
  BinPolynom test = BinPolynom(1, validCoefs);

  char *c = test.coef_get();
  ASSERT_EQ(c[0], 3); // 3 == 0b11
  ASSERT_EQ(test.order_get(), 1);
};


TEST(BP_init, with_invalid_order)
{
  try
  {
   BinPolynom test(-1);
  }
  catch(IncorrectOrder& e)
  {
    SUCCEED();
  };
};

TEST(BP_init, with_invalid_coefs)
{
  char invalidCoefs[] = {2,3};
  try
  {
    BinPolynom test(2, invalidCoefs);
  }
  catch(IncorrectCoefs& e)
  {
    SUCCEED();
  };
};

//-- END --//


//-- BinPolynom operators --//

// Equate operator (=)
TEST(BP_op, EO_order_neq_first_bigger)
{
  BinPolynom testFirst = 1337;
  BinPolynom testSecond;

  testSecond = testFirst;
  int testSecondOrder = testSecond.order_get();
  ASSERT_EQ(testSecondOrder, 1337);
};

TEST(BP_op, EO_coefs_eq)
{
  char validCoefs[] = {1,0,1};
  BinPolynom testFirst(2, validCoefs);
  BinPolynom testSecond;

  testSecond = testFirst;
  ASSERT_EQ(testSecond.coef_get()[0], 5);
};

TEST(BP_op, EO_order_neq_second_bigger)
{
  BinPolynom testFirst = 1;
  BinPolynom testSecond = 2123;

  testSecond = testFirst;
  ASSERT_EQ(testSecond.order_get(), 1);
};

TEST(BP_op, EO_order_eq)
{
  BinPolynom testFirst=2;
  BinPolynom testSecond=2;

  testSecond = testFirst;
  ASSERT_EQ(testSecond.order_get(),2);
};

//-- END --//

int 
main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
};
