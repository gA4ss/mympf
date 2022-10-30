#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mympf/mympf.h>

using namespace mympf;

TEST(Mympf, uAdd) {
  mympf::float_t x, y, z;
  std::string z_str;

  x = create("123.1234655434342");
  y = create("5667.1234655434342");
  z = uadd(x,y);
  z_str = print_string(z);
  // std::cout << "z = " << z_str << std::endl;
  EXPECT_STREQ(z_str.c_str(), "5790.2469310868684");

  x = create("3.832");
  y = create("5.43");
  z = uadd(x,y);
  z_str = print_string(z);
  // std::cout << "z = " << z_str << std::endl;
  EXPECT_STREQ(z_str.c_str(), "9.262");
}

TEST(Mympf, uSub) {
  mympf::float_t x, y, z;
  std::string z_str;

  x = create("123.1234655434342");
  y = create("5667.1234655434342");
  z = usub(y,x);
  z_str = print_string(z);
  // std::cout << "z = " << z_str << std::endl;
  EXPECT_STREQ(z_str.c_str(), "5544.0000000000000");

  x = create("3.832");
  y = create("5.43");
  z = usub(y,x);
  z_str = print_string(z);
  // std::cout << "z = " << z_str << std::endl;
  EXPECT_STREQ(z_str.c_str(), "1.598");
}

TEST(Mympf, Add) {
  mympf::float_t x, y, z;
  std::string z_str;

  x = create("-123.123465543");
  y = create("5667.56543");
  z = add(x, y);
  z_str = print_string(z);
  // std::cout << "z = " << z_str << std::endl;
  EXPECT_STREQ(z_str.c_str(), "5544.441964457");

  x = create("3.832");
  y = create("-5.43");
  z = add(x,y);
  z_str = print_string(z);
  // std::cout << "z = " << z_str << std::endl;
  EXPECT_STREQ(z_str.c_str(), "-1.598");

  x = create("-1983.1210");
  y = create("-1993.0613");
  z = add(x,y);
  z_str = print_string(z);
  // std::cout << "z = " << z_str << std::endl;
  EXPECT_STREQ(z_str.c_str(), "-3976.1823");

  x = create("1983");
  y = create("1993");
  z = add(x,y);
  z_str = print_string(z);
  // std::cout << "z = " << z_str << std::endl;
  EXPECT_STREQ(z_str.c_str(), "3976.0");
}

TEST(Mympf, Sub) {
  mympf::float_t x, y, z;
  std::string z_str;

  x = create("-123.123465543");
  y = create("5667.56543");
  z = sub(x, y);
  z_str = print_string(z);
  // std::cout << "z = " << z_str << std::endl;
  EXPECT_STREQ(z_str.c_str(), "-5790.688895543");

  x = create("3.832");
  y = create("-5.43");
  z = sub(x,y);
  z_str = print_string(z);
  // std::cout << "z = " << z_str << std::endl;
  EXPECT_STREQ(z_str.c_str(), "9.262");

  x = create("-1983.1");
  y = create("-1993.6");
  z = sub(x,y);
  z_str = print_string(z);
  // std::cout << "z = " << z_str << std::endl;
  EXPECT_STREQ(z_str.c_str(), "10.5");

  x = create("1983");
  y = create("1993");
  z = sub(x,y);
  z_str = print_string(z);
  // std::cout << "z = " << z_str << std::endl;
  EXPECT_STREQ(z_str.c_str(), "-10.0");
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
