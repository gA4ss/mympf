#include <mympf/mympf.h>

namespace mympf
{

  float_t sub(const float_t &x, const float_t &y)
  {
    float_t z;

    if (x.neg() ^ y.neg())
    {
      z = uadd(x, y);
      z.set_neg(x.neg());
    }
    else // 符号相同
    {
      int neg = x.neg();
      if (ucmp(x, y) >= 0)
      {
        if (neg == 0)
        {
          z = usub(x, y);
        }
        else
        {
          z = uadd(x, y);
          z.set_neg(1);
        }
      }
      else
      {
        if (neg == 0)
        {
          z = usub(y, x);
          z.set_neg(1);
        }
        else
        {
          z = usub(y, x);
        }
      }
    }

    return z;
  }

  float_t usub(const float_t &x, const float_t &y)
  {
    //
    // 首先计算小数部分
    //

    // 扩展小数部分位数，使得小数部分进行对齐
    mympz::bignum_t xd = x.decimal_part;
    mympz::bignum_t yd = y.decimal_part;

    size_t xdl = bn_size(xd);
    size_t ydl = bn_size(yd);

    if ((xdl == ydl) && (xdl == 1))
    {
      if (xd.number[0] > yd.number[0])
      {
        expand_decimal_word(yd.number[0], xd.number[0]);
      }
      else if (xd.number[0] < yd.number[0])
      {
        expand_decimal_word(xd.number[0], yd.number[0]);
      }
    }
    else
    {
      if (mympz::ucmp(xd, yd) > 0)
      {
        expand_decimal(yd, xd);
      }
      else if (mympz::ucmp(xd, yd) < 0)
      {
        expand_decimal(xd, yd);
      }
    }
    // 到这里xd与yd的长度应该一致

    //
    // 这里判定是否存在借位
    //
    mympz::bignum_t decimal_part;
    mympz::bignum_t decimal_part_borrow;
    if (ucmp(xd, yd) < 0)
    {
      decimal_part_borrow = mympz::const_one;
      decimal_part = mympz::usub(yd, xd);

      //
      // 统计借位的倍数
      //
      mympz::bignum_t b = mympz::const_one;
      mympz::bignum_t t = mympz::create(10);
      while (1)
      {
        if (mympz::cmp(xd, t) > 0)
        {
          xd = mympz::idiv(xd, t);
          b = mympz::mul(b, t);
        }
        else
        {
          break;
        }
      }
      b = mympz::mul(b, t);
      decimal_part = mympz::usub(b, decimal_part);
    }
    else if (ucmp(xd, yd) > 0)
    {
      decimal_part = mympz::usub(xd, yd);
      decimal_part_borrow = mympz::const_zero;
    }
    else
    {
      decimal_part = mympz::const_zero;
      decimal_part_borrow = mympz::const_zero;
    }

    // 计算整数部分
    mympz::bignum_t xi = x.integer_part;
    mympz::bignum_t yi = y.integer_part;

    mympz::bignum_t integer_part = mympz::usub(xi, yi);
    integer_part = mympz::usub(integer_part, decimal_part_borrow);

    float_t z;
    z.integer_part.neg = 0;
    z.integer_part = integer_part;
    z.decimal_part = decimal_part;
    return z;
  }

} // namespace mympf
