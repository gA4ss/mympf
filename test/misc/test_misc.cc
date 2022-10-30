#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <mympf/mympf.h>

using namespace mympf;

void test_expand_decimal_word() {
  mympz::unit_t w = 46589, m = 344321675491;
  size_t k = expand_word(w, m);
  std::cout << "w = " << w << " " << "k = " << k << std::endl;
  std::cout << "m = " << m << std::endl;

  w = 4, m = 20;
  k = expand_word(w, m);
  std::cout << "w = " << w << " " << "k = " << k << std::endl;
  std::cout << "m = " << m << std::endl;

  w = 1, m = 431431231432143214;
  k = expand_word(w, m);
  std::cout << "w = " << w << " " << "k = " << k << std::endl;
  std::cout << "m = " << m << std::endl;

  w = 55, m = 55000;
  k = expand_word(w, m);
  std::cout << "w = " << w << " " << "k = " << k << std::endl;
  std::cout << "m = " << m << std::endl;
}

void test_count_digits() {
  mympz::bignum_t x = mympz::create("1000");
  size_t k = count_digits(x);
  std::cout << "x = " << mympz::print_string(x) << std::endl;
  std::cout << "k = " << k << std::endl;
  std::cout << std::endl;

  x = mympz::create("9");
  k = count_digits(x);
  std::cout << "x = " << mympz::print_string(x) << std::endl;
  std::cout << "k = " << k << std::endl;
  std::cout << std::endl;

  x = mympz::create("10031");
  k = count_digits(x);
  std::cout << "x = " << mympz::print_string(x) << std::endl;
  std::cout << "k = " << k << std::endl;
  std::cout << std::endl;

  x = mympz::create("88");
  k = count_digits(x);
  std::cout << "x = " << mympz::print_string(x) << std::endl;
  std::cout << "k = " << k << std::endl;
  std::cout << std::endl;

  x = mympz::create("9901");
  k = count_digits(x);
  std::cout << "x = " << mympz::print_string(x) << std::endl;
  std::cout << "k = " << k << std::endl;
  std::cout << std::endl;
}

int main(int argc, char* argv[]) {
  test_count_digits();
  // test_expand_decimal();
  return 0;
}
