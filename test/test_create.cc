#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mympf/mympf.h>

using namespace mympf;

TEST(Mympf, Create) {
  mympf::float_t x = const_0;
  std::string x_str;

  x = create("0.000000000000000000000000000000001");
  x_str = print_string(x);
  EXPECT_STREQ(x_str.c_str(), "0.000000000000000000000000000000001");

  x = create("-0.000000000000000000000000000000002");
  x_str = print_string(x);
  EXPECT_STREQ(x_str.c_str(), "-0.000000000000000000000000000000002");

  x = create("1.0");
  x_str = print_string(x);
  EXPECT_STREQ(x_str.c_str(), "1.0");

  x = create("3.1415926");
  x_str = print_string(x);
  EXPECT_STREQ(x_str.c_str(), "3.1415926");

  x = create("-0.618");
  x_str = print_string(x);
  EXPECT_STREQ(x_str.c_str(), "-0.618");
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
