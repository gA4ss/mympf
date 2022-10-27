#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mympf/mympf.h>

using namespace mympf;

TEST(Mympf, Cmp) {
  mympf::float_t x, y;

  x = create("1.0");
  y = create("3.1415926");
  EXPECT_EQ(cmp(x, y), -1);

  x = create("-0.618");
  y = create("-3.1415926");
  EXPECT_EQ(cmp(x, y), 1);

  x = create("4.3");
  y = create("3.1");
  EXPECT_EQ(cmp(x, y), 1);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
