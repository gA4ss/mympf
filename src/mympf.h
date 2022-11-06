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

  /*
   * 从定义可以看出，本库的精度是有限的，最大为2^sizeof(unsigned long long)次方。通常状况下为2^64次方。
   * 这个精度应该是够用的。暂定如此，如果需要扩展成无限精度，可以将size_t precision的类型与运算换成，
   * mympz::bignum_t类型即可。
   */
  typedef struct __float_t
  {
    __float_t();
    mympz::bignum_t number;
    size_t precision;

    int neg() const { return number.neg; }
    void set_neg(int neg = 0) { number.neg = neg; }

  } float_t;

  float_t create(mympz::unit_t word, size_t precision = 0, int neg = 0);
  float_t create(std::string str);
  float_t create(const mympz::bignum_t &number, size_t precision);

  float_t integer_part(const float_t &x);
  float_t decimal_part(const float_t &x);

  float_t floor(const float_t &x);
  float_t ceil(const float_t &x);
  float_t round(const float_t &x, size_t precision = 0);

  float_t add(const float_t &x, const float_t &y);
  float_t uadd(const float_t &x, const float_t &y);
  float_t sub(const float_t &x, const float_t &y);
  float_t usub(const float_t &x, const float_t &y);
  float_t mul(const float_t &x, const float_t &y);
  float_t idiv(const float_t &x, const float_t &y);
  float_t div(const float_t &x, const float_t &y, size_t precision = 16);
  float_t mod(const float_t &x, const float_t &y, size_t precision = 16);

  /*
   * 指数运算虽然提供了bignum_t的指数版本，可是目前通常最大还是2^64次方来运算，因为已经足够大了。
   * 这里的`const float_t &p`仅取整数部分，忽略小数部分。
   */
  float_t exp(const float_t &x, const float_t &p);
  float_t exp(const float_t &x, const mympz::bignum_t &p);
  float_t exp(const float_t &x, const size_t p);
  int cmp(const float_t &x, const float_t &y);
  int ucmp(const float_t &x, const float_t &y);
  float_t sqr(const float_t &x);

  std::string print_string(const float_t &x);

  //
  // 内部一些辅助函数
  //
  size_t count_digits(const mympz::bignum_t &x);
  size_t shrink_zero(mympz::bignum_t &x, bool reverse = true);
  size_t shrink_precision(float_t &x, size_t target_precision);
  size_t shrink_precision(mympz::bignum_t &x, size_t current_precision, size_t target_precision);
  size_t shrink_zero_precision(float_t &x);
  size_t expand_word(mympz::unit_t &w, mympz::unit_t m);
  size_t expand_number(mympz::bignum_t &x, const mympz::bignum_t &y);
  size_t expand_precision(mympz::bignum_t &x, size_t current_precision, size_t target_precision);

  // void init();
  // extern float_t const_null;
  // extern float_t const_0;
  // extern float_t const_1;
  // extern float_t const_10;

} // namespace mympf

#endif // MYMPF_H_