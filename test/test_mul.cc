#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mympf/mympf.h>

using namespace mympf;

TEST(Mympf, Mul) {
  mympf::float_t x, y, z;
  std::string z_str;

  x = create("-123.000");
  y = create("2.345");
  z = mul(x, y);
  z_str = print_string(z);
  // std::cout << "z = " << z_str << std::endl;
  EXPECT_STREQ(z_str.c_str(), "-288.435000");

  x = create("3.832");
  y = create("-5.43");
  z = mul(x,y);
  z_str = print_string(z);
  // std::cout << "z = " << z_str << std::endl;
  EXPECT_STREQ(z_str.c_str(), "-20.807760");

  x = create("-1983.1210");
  y = create("-1993.0613");
  z = mul(x,y);
  z_str = print_string(z);
  // std::cout << "z = " << z_str << std::endl;
  EXPECT_STREQ(z_str.c_str(), "3952481.71831730");

  x = create("1983");
  y = create("1993");
  z = mul(x,y);
  z_str = print_string(z);
  // std::cout << "z = " << z_str << std::endl;
  EXPECT_STREQ(z_str.c_str(), "3952119.0");
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
