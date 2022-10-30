#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mympf/mympf.h>

using namespace mympf;

TEST(Mympf, Div) {
  mympf::float_t x, y, z;
  std::string z_str;

  x = create("534.56");
  y = create("2.345");
  z = div(x, y);
  z_str = print_string(z);
  // std::cout << "z = " << z_str << std::endl;
  EXPECT_STREQ(z_str.c_str(), "227.95735607675903");

  // x = create("1983");
  // y = create("1993");
  // z = div(x,y);
  // z_str = print_string(z);
  // // std::cout << "z = " << z_str << std::endl;
  // EXPECT_STREQ(z_str.c_str(), "3952119.0");
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
