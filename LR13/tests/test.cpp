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

  unsigned char *c = test.coef_get();
  ASSERT_EQ(c[0], 0);
  ASSERT_EQ(c[1], 0);
};


TEST(BP_init, with_valid_order_and_coefs)
{
  unsigned char validCoefs[] = {1,1};
  BinPolynom test = BinPolynom(1, validCoefs);

  unsigned char *c = test.coef_get();
  ASSERT_EQ(c[0], 192); // 0xc0 == 192 == 0b11000000
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
  unsigned char invalidCoefs[] = {2,3};
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



//-- BinPolynom private function 'refreshOrder' --//

TEST(RefreshOrder, first_test)
{
  const unsigned char coef[] = {1,1,1,0};
  BinPolynom test(3, coef);

  test.testRefreshOrder();

  ASSERT_EQ(test.order_get(), 2);
};

TEST(MultOnMonom, first_test)
{
  const unsigned char coef[] = {1,1};
  BinPolynom test(1, coef);

  BinPolynom testResult = test.testMultOnMonom(1);
  ASSERT_EQ(*testResult.coef_get(), '\x60');
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
  unsigned char validCoefs[] = {1,0,1};
  BinPolynom testFirst(2, validCoefs);
  BinPolynom testSecond;

  testSecond = testFirst;
  ASSERT_EQ(testSecond.coef_get()[0], 160); // 0b10100000 == 0xa0
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

// Addition operator (+)

TEST(BP_op, AO_order_eq_first_is_zero)
{
  BinPolynom testFirst = 4;
  unsigned char coefs[] = {1,1,0,1,1}; // 11011 == 27
  BinPolynom testSecond(4, coefs);

  testSecond = (BinPolynom&) testSecond + testFirst;
  ASSERT_EQ(testSecond.order_get(), testFirst.order_get());
  
  ASSERT_EQ(*testSecond.coef_get(), 216); // 0x11011000 == 0xd8
};

TEST(BP_op, AO_order_eq)
{
  unsigned char coefFirst[] = {1,1};
  unsigned char coefSecond[] = {1,0};

  BinPolynom testFirst(1, coefFirst);
  BinPolynom testSecond(1, coefSecond);

  BinPolynom testThird = (BinPolynom&) testFirst + testSecond;

  ASSERT_EQ(testThird.order_get(), testFirst.order_get());
  ASSERT_EQ(*testThird.coef_get(), '\x40'); // xor(2,3) == 1 => 0b01000000 == 0x40
};

TEST(BP_op, AO_order_neq)
{
  unsigned char coefFirst[] = {1,1,1};
  unsigned char coefSecond[] = {1,0};

  BinPolynom testFirst(2, coefFirst);
  BinPolynom testSecond(1, coefSecond);

  BinPolynom testThird = (BinPolynom&) testFirst + testSecond;

  ASSERT_EQ(testThird.order_get(), testFirst.order_get());
  ASSERT_EQ(*testThird.coef_get(), '\x60'); // xor(4, 7) == 3 => 0x01100000 == 0x60
};

// Subtration operator (-)

TEST(BP_op, SO_order_eq_first_is_zero)
{
  BinPolynom testFirst = 4;
  unsigned char coefs[] = {1,1,0,1,1}; // 11011 == 27
  BinPolynom testSecond(4, coefs);

  testSecond = testSecond - testFirst;
  ASSERT_EQ(testSecond.order_get(), testFirst.order_get());
  
  ASSERT_EQ(*testSecond.coef_get(), 216); // 0x11011000 == 0xd8
};

// Addition-equate operator (+=)

TEST(BP_op, AEO_order_eq_first_is_zero)
{
  BinPolynom testFirst = 4;
  unsigned char coefs[] = {1,1,0,1,1}; // 11011 == 27
  BinPolynom testSecond(4, coefs);

  testFirst += testSecond;
  ASSERT_EQ(testSecond.order_get(), testFirst.order_get());
  
  ASSERT_EQ(*testFirst.coef_get(), 216); // 0x11011000 == 0xd8
};

// Subtration-equate operator (-=)

TEST(BP_op, SEO_order_eq_first_is_zero)
{
  BinPolynom testFirst = 4;
  unsigned char coefs[] = {1,1,0,1,1}; // 11011 == 27
  BinPolynom testSecond(4, coefs);

  testFirst -= testSecond;
  ASSERT_EQ(testSecond.order_get(), testFirst.order_get());
  
  ASSERT_EQ(*testFirst.coef_get(), 216); // 0x11011000 == 0xd8
};

// Multiplication operator (*)

TEST(BP_op, MO_simple)
{
  unsigned char coefsFirst[] = {1,0,1,1};
  unsigned char coefsSecond[] = {0,1};

  BinPolynom testFirst(3, coefsFirst);
  BinPolynom testSecond(1, coefsSecond);

  BinPolynom testThird = testFirst * testSecond;

  ASSERT_EQ(*testThird.coef_get(), '\x58'); // 0b01011000 == 0x58
};

//-- END --//

int 
main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
};
