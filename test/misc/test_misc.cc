#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <mympf/mympf.h>

using namespace mympf;

void test_merge() {
  mympf::float_t x;
  mympz::bignum_t y;
  std::string y_str;
  x = create("000019833.1415926000000");
  y = merge(x);
  y_str = print_string(y);
  std::cout << "y = " << y_str << std::endl;

  x = create("-612.44532");
  y = merge(x);
  y_str = print_string(y);
  std::cout << "y = " << y_str << std::endl;
}

void test_expand_decimal_word() {
  mympz::unit_t w = 46589, m = 344321675491;
  size_t k = expand_decimal_word(w, m);
  std::cout << "w = " << w << " " << "k = " << k << std::endl;
  std::cout << "m = " << m << std::endl;

  w = 4, m = 20;
  k = expand_decimal_word(w, m);
  std::cout << "w = " << w << " " << "k = " << k << std::endl;
  std::cout << "m = " << m << std::endl;

  w = 1, m = 431431231432143214;
  k = expand_decimal_word(w, m);
  std::cout << "w = " << w << " " << "k = " << k << std::endl;
  std::cout << "m = " << m << std::endl;

  w = 55, m = 55000;
  k = expand_decimal_word(w, m);
  std::cout << "w = " << w << " " << "k = " << k << std::endl;
  std::cout << "m = " << m << std::endl;
}

int main(int argc, char* argv[]) {
  // test_merge();
  test_expand_decimal_word();
  return 0;
}
