#include <mympf/mympf.h>

namespace mympf
{

  __float_t::__float_t()
  {
    init_bignum(number);
    precision = 0;
  }

  size_t count_digits(const mympz::bignum_t &x)
  {
    size_t c = 0;
    mympz::bignum_t y = x;
    while (mympz::ucmp(y, mympz::const_10) >= 0)
    {
      y = mympz::idiv(y, mympz::const_10);
      c++;
    }
    c++;
    return c;
  }

  size_t shrink_zero(mympz::bignum_t &x, bool reverse)
  {
    if (x.number.empty())
      return 0;
    if ((x.number.size() == 1) && (x.number[0] == 0))
      return 0;

    size_t ret = 0;
    if (reverse)
    {
      int l = static_cast<int>(x.number.size());
      for (int i = l - 1; i > 0; i--)
      {
        if (x.number[i] == 0)
        {
          x.number.pop_back();
          ++ret;
        }
        else
        {
          break;
        }
      }
    }
    else
    {
      mympz::number_t::iterator it = x.number.begin();
      while (it < x.number.end())
      {
        if (*it == 0)
        {
          it = x.number.erase(it);
          ++ret;
        }
        else
        {
          break;
        }
      }
    }
    return ret;
  }

  size_t shrink_precision(mympz::bignum_t &x, size_t current_precision, size_t target_precision)
  {
    if (current_precision <= target_precision)
    {
      return 0;
    }

    size_t n =  current_precision - target_precision;

    while (n--)
    {
      x = mympz::idiv(x, mympz::const_10);
    }

    return (current_precision - target_precision);
  }

  size_t shrink_precision(float_t &x, size_t target_precision)
  {
    size_t s = shrink_precision(x.number, x.precision, target_precision);
    x.precision = target_precision;
    return s;
  }

  size_t expand_word(mympz::unit_t &w, mympz::unit_t m)
  {
    // 保证 w < m
    if (w == m)
      return w;
    if (w > m)
    {
      // 应该抛出异常
      return w;
    }
    size_t i = 0, j = 0;
    mympz::unit_t u = w, v = m;
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

    size_t k = j - i;

    while (k--)
    {
      w *= 10;
    }

    return (j - i);
  }

  size_t expand_number(mympz::bignum_t &x, const mympz::bignum_t &y)
  {
    // 保证 w < m
    if (mympz::cmp(x, y) == 0)
      return 0;
    if (mympz::cmp(x, y) > 0)
    {
      // 应该抛出异常
      return 0;
    }
    size_t i = 0, j = 0;
    mympz::bignum_t u = x, v = y;

    while (1)
    {
      if (mympz::cmp(u, mympz::const_10) > 0)
      {
        u = mympz::idiv(u, mympz::const_10);
        i++;
      }

      if (mympz::cmp(v, mympz::const_10) > 0)
      {
        v = mympz::idiv(v, mympz::const_10);
        j++;
      }
      else
      {
        break;
      }
    }

    size_t k = j - i;

    while (k--)
    {
      x = mympz::mul(x, mympz::const_10);
    }

    return (j - i);
  }

  size_t expand_precision(mympz::bignum_t &x, size_t current_precision, size_t target_precision)
  {
    if (current_precision >= target_precision)
    {
      return 0;
    }

    size_t n = target_precision - current_precision;

    while (n--)
    {
      x = mympz::mul(x, mympz::const_10);
    }

    return (target_precision - current_precision);
  }

  float_t integer_part(const float_t &x)
  {
    float_t y = x;
    shrink_precision(y, 0);
    y.set_neg(x.neg());
    return y;
  }

  float_t decimal_part(const float_t &x)
  {
    float_t y = x;
    shrink_precision(y, 0);
    y = usub(x, y);
    y.precision = x.precision;
    return y;
  }

  size_t shrink_zero_precision(float_t &x)
  {
    if ((!x.precision) || (mympz::is_zero(x.number)))
      return 0;

    size_t s = x.precision, p = x.precision;
    mympz::bignum_t y = x.number;
    mympz::division_result_t qr;

    while(s)
    {
      qr = mympz::div(y, mympz::const_10);
      if (!mympz::is_zero(qr.second))
      {
        break;
      }
      y = qr.first;
      s--;
    }
    
    x.number = y;
    x.precision = s;
    return (p - s);
  }

} // namespace mympf