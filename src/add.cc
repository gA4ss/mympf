#include <mympf/mympf.h>

namespace mympf
{
  float_t add(const float_t &x, const float_t &y)
  {
    float_t z;

    if (x.neg() ^ y.neg())
    {
      if (ucmp(x, y) >= 0)
      {
        z = usub(x, y);
        if (x.neg())
        {
          z.set_neg(1);
        }
      }
      else
      {
        z = usub(y, x);
        if (y.neg())
        {
          z.set_neg(1);
        }
      }
    }
    else
    {
      z = uadd(x, y);
      z.set_neg(x.neg());
    }

    return z;
  }

  float_t uadd(const float_t &x, const float_t &y)
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
    mympz::bignum_t decimal_part = mympz::uadd(xd, yd);

    //
    // 计算溢出部分
    //
    mympz::bignum_t decimal_part_carry;
    size_t s = bn_size(xd);
    if (bn_size(decimal_part) > s)
    {
      size_t k = bn_size(decimal_part) - s;
      decimal_part_carry.number.insert(
          decimal_part_carry.number.end(),
          decimal_part.number.end() - k,
          decimal_part.number.end());

      decimal_part.number.erase(
          decimal_part.number.begin(),
          decimal_part.number.begin() + k);
    }
    else
    {
      //
      // 当只有一个字，发生进位时，这个进位的1
      // 也要加到整数部分中。
      //
      if (bn_size(decimal_part) == 1)
      {
        mympz::unit_t u = xd.number[0];
        mympz::unit_t v = yd.number[0];

        if (u < v)
          u = v;
        v = decimal_part.number[0];

        size_t i = 0, j = 0;
        while (1)
        {
          if (u > 10)
          {
            u = u / 10;
            i++;
          }

          if (v > 10)
          {
            v = v / 10;
            j++;
          }
          else
          {
            break;
          }
        }

        // 判定是否存在进位
        if (j > i)
        {
          // 从浮点部分去掉最高位的1
          v = 1;
          while (j--)
            v *= 10;
          decimal_part.number[0] -= v;
          decimal_part_carry = mympz::const_one;
        }
        else
        {
          decimal_part_carry = mympz::const_zero;
        }
      }
      else
      {
        decimal_part_carry = mympz::const_zero;
      }
    }

    // 计算整数部分
    mympz::bignum_t xi = x.integer_part;
    mympz::bignum_t yi = y.integer_part;

    mympz::bignum_t integer_part = mympz::uadd(xi, yi);
    if (!mympz::is_zero(decimal_part_carry))
    {
      integer_part = mympz::uadd(integer_part, decimal_part_carry);
    }

    float_t z;
    z.integer_part.neg = 0;
    z.integer_part = integer_part;
    z.decimal_part = decimal_part;
    return z;
  }

} // namespace mympf