#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mympf/mympf.h>

using namespace mympf;

TEST(Mympf, Exp) {
  mympf::float_t x, z;
  std::string z_str;

  x = create("-123");
  z = exp(x, 5);
  z_str = print_string(z);
  // std::cout << "z = " << z_str << std::endl;
  EXPECT_STREQ(z_str.c_str(), "-28153056843.0");

  x = create("0.1");
  z = exp(x, 2);
  z_str = print_string(z);
  // std::cout << "z = " << z_str << std::endl;
  EXPECT_STREQ(z_str.c_str(), "0.01");

  x = create("-0.004");
  z = exp(x,2);
  z_str = print_string(z);
  // std::cout << "z = " << z_str << std::endl;
  EXPECT_STREQ(z_str.c_str(), "0.000016");

  x = create("1983.0");
  z = exp(x,3);
  z_str = print_string(z);
  // std::cout << "z = " << z_str << std::endl;
  EXPECT_STREQ(z_str.c_str(), "7797729087.000");
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
