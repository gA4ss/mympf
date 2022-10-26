#ifndef MYMPF_H_
#define MYMPF_H_

#include <cmath>
#include <algorithm>
#include <sstream>
#include <iostream>

#include <mympz/mympz.h>
#include <mympf/compile.h>
#include <mympf/exception.h>
#include <mympf/debug.h>

namespace mympf
{

  typedef struct
  {
    mympz::bignum_t integer_part;
    mympz::bignum_t decimal_part;

    int neg() const { return integer_part.neg; }
  } float_t;

  float_t create(std::string str, bool hex = false);
  float_t create(const mympz::bignum_t &integer, const mympz::bignum_t &decimal);
  float_t create(const mympz::number_t &integer, const mympz::number_t &decimal, int neg = 0);

  float_t add(const float_t &x, const float_t &y);
  float_t sub(const float_t &x, const float_t &y);
  float_t mul(const float_t &x, const float_t &y);
  float_t div(const float_t &x, const float_t &y);
  float_t mod(const float_t &x, const float_t &y);
  float_t exp(const float_t &x, const size_t p);
  int cmp(const float_t &x, const float_t &y);
  float_t sqr(const float_t &x);

  std::string print_string(const float_t &x, bool hex = false, bool low_case = false);

  void shrink_zero(float_t &x);
  void shrink_integer_zero(float_t &x);
  void shrink_decimal_zero(float_t &x);
  mympz::bignum_t merge(const float_t &x);
  void expand_decimal(float_t &x, size_t n);
  size_t expand_decimal_word(mympz::unit_t &w, mympz::unit_t m);
} // namespace mympf

#endif // MYMPF_H_