#include <gtest/gtest.h>
#include "../src/binpol.h"



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
  ASSERT_EQ(*c, 1);
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

int 
main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
};
