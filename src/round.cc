#include <mympf/mympf.h>

namespace mympf
{

  static float_t __effective_digit(const float_t &x, size_t precision, mympz::unit_t &v)
  {
    if (precision >= x.precision)
    {
      v = 0;
      return decimal_part(x);
    }

    // 得到新的小数部分
    float_t new_decimal_park = decimal_part(x);
    shrink_precision(new_decimal_park, precision + 1);

    const mympz::bignum_t const_10 = mympz::create(10);

    // 新的尾数的末尾数
    mympz::bignum_t k = mympz::mod(new_decimal_park.number, const_10);
    v = mympz::get_word(k);

    // 去掉缩放时多加的判断位
    new_decimal_park.number = mympz::idiv(new_decimal_park.number, const_10);
    new_decimal_park.precision = precision;
    return new_decimal_park;
  }

  // 就判断整数后的第一位小数是不是大于5
  static bool __mantissa_is_greater_than_5(const float_t &x)
  {
    float_t y = decimal_part(x);
    size_t c = count_digits(y.number);
    mympz::bignum_t e = mympz::exp(mympz::create(10), mympz::create(c));
    mympz::bignum_t f = mympz::create(5);
    mympz::bignum_t n = mympz::idiv(y.number, e);

    if (mympz::ucmp(n, f) >= 0)
      return true;

    return false;
  }

  /* 当尾数为5，而尾数后面的数字均为0时，应看尾数“5”的前一位：若前一位数字此时为奇数，
   * 就应向前进一位；若前一位数字此时为偶数，则应将尾数舍去。数字“0”在此时应被视为偶数。
   */
  float_t round(const float_t &x, size_t precision)
  {
    if (!x.precision)
      return x;
    if (x.precision <= precision)
      return x;

    float_t y = integer_part(x);

    //
    // 仅保留整数部分
    //
    const float_t const_1 = create(1);
    if (precision == 0)
    {
      if (__mantissa_is_greater_than_5(x))
      {
        if (mympz::is_odd(y.number))
        {
          if (!y.neg())
          {
            return add(y, const_1);
          }
          else
          {
            return sub(y, const_1);
          }
        }
        else
        {
          return y;
        }
      }
      else
      {
        return y;
      }
    }

    //
    // 尾数不是5
    //
    mympz::unit_t v = 0;
    // 返回的有效位仅是有效位
    float_t effective_part = __effective_digit(x, precision, v);
    y = uadd(y, effective_part);

    //
    // 四舍五入
    //
    if (v >= 5)
    {
      float_t plus = create(1, effective_part.precision);
      y = uadd(y, plus);
    }

    // 符号与x保持一致
    y.set_neg(x.neg());
    return y;
  }

} // namespace mympf
