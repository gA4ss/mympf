#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mympf/mympf.h>

using namespace mympf;

TEST(Mympf, Merge) {
  mympf::float_t x;
  mympz::bignum_t y;
  std::string y_str;

  x = create("000019833.1415926000000");
  y = merge(x);
  y_str = print_string(y);
  EXPECT_STREQ(y_str.c_str(), "198331415926");

  x = create("-612.44532");
  y = merge(x);
  y_str = print_string(y);
  EXPECT_STREQ(y_str.c_str(), "-61244532");
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
