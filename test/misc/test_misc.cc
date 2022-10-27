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

void test_expand_decimal() {
  mympz::bignum_t x = mympz::create("8542543254353256547321648");
  mympz::bignum_t y = mympz::create("12321431542748931764381648963728542543254353256547321648");
  size_t k = expand_decimal(x, y);
  std::cout << "k = " << k << std::endl;
  std::cout << "x = " << mympz::print_string(x) << std::endl;
  std::cout << "y = " << mympz::print_string(y) << std::endl;
}

int main(int argc, char* argv[]) {
  test_merge();
  // test_expand_decimal();
  return 0;
}
