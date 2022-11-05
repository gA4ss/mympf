#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mympf/mympf.h>

using namespace mympf;

TEST(Mympf, IDiv) {
  mympf::float_t x, y, z;
  std::string z_str;

  x = create("5.2");
  y = create("4.3");
  z = idiv(x, y);
  z_str = print_string(z);
  // std::cout << "z = " << z_str << std::endl;
  EXPECT_STREQ(z_str.c_str(), "1.0");

  x = create("-5.2");
  y = create("-4.3");
  z = idiv(x, y);
  z_str = print_string(z);
  // std::cout << "z = " << z_str << std::endl;
  EXPECT_STREQ(z_str.c_str(), "1.0");

  x = create("-5.2");
  y = create("4.3");
  z = idiv(x, y);
  z_str = print_string(z);
  // std::cout << "z = " << z_str << std::endl;
  EXPECT_STREQ(z_str.c_str(), "-1.0");

  x = create("5.2");
  y = create("-4.3");
  z = idiv(x, y);
  z_str = print_string(z);
  // std::cout << "z = " << z_str << std::endl;
  EXPECT_STREQ(z_str.c_str(), "-1.0");
}

TEST(Mympf, Div) {
  mympf::float_t x, y, z;
  std::string z_str;

  x = create("534.56");
  y = create("2.345");
  z = div(x, y);
  z_str = print_string(z);
  // std::cout << "z = " << z_str << std::endl;
  EXPECT_STREQ(z_str.c_str(), "227.957356076759061833");

  x = create("1");
  y = create("3");
  z = div(x, y);
  z_str = print_string(z);
  // std::cout << "z = " << z_str << std::endl;
  EXPECT_STREQ(z_str.c_str(), "0.3333333333333333");

  x = create("1983");
  y = create("1993");
  z = div(x,y);
  z_str = print_string(z);
  // std::cout << "z = " << z_str << std::endl;
  EXPECT_STREQ(z_str.c_str(), "0.99498243853487205");

  x = create("2.09");
  y = create("2.0");
  z = div(x, y);
  z_str = print_string(z);
  EXPECT_STREQ(z_str.c_str(), "1.045");
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
