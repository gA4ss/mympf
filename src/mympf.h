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
    mympz::bignum_t number;
    size_t precision;

    int neg() const { return number.neg; }
    void set_neg(int neg=0) { number.neg = neg; }
  } float_t;

  float_t create(std::string str);
  float_t create(const mympz::bignum_t &number, size_t precision);

  float_t add(const float_t &x, const float_t &y);
  float_t uadd(const float_t &x, const float_t &y);
  float_t sub(const float_t &x, const float_t &y);
  float_t usub(const float_t &x, const float_t &y);
  float_t mul(const float_t &x, const float_t &y);
  float_t div(const float_t &x, const float_t &y);
  float_t mod(const float_t &x, const float_t &y);
  float_t exp(const float_t &x, const size_t p);
  int cmp(const float_t &x, const float_t &y);
  int ucmp(const float_t &x, const float_t &y);
  float_t sqr(const float_t &x);

  std::string print_string(const float_t &x);

  size_t shrink_zero(mympz::bignum_t &x, bool reverse=true);
  size_t expand_word(mympz::unit_t &w, mympz::unit_t m);
  size_t expand_number(mympz::bignum_t &x, const mympz::bignum_t &y);
  size_t expand_precision(mympz::bignum_t &x, size_t target_precision);

} // namespace mympf

#endif // MYMPF_H_