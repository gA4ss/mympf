#include <mympf/mympf.h>

namespace mympf
{

  static size_t __shrink_zero(mympz::bignum_t &x, bool reverse)
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

  /* 保留最后一个零 */
  void shrink_zero(float_t &x)
  {
    __shrink_zero(x.integer_part, true);
    __shrink_zero(x.decimal_part, false);
  }

  void shrink_integer_zero(float_t &x)
  {
    __shrink_zero(x.integer_part, true);
  }

  void shrink_decimal_zero(float_t &x)
  {
    // 去除末尾的0字
    __shrink_zero(x.decimal_part, false);
    if (mympz::is_zero(x.decimal_part))
    {
      return;
    }

    mympz::unit_t w = x.decimal_part.number[0];
    while (!(w % 10))
    {
      w = w / 10;
    }
  }

  mympz::bignum_t merge(const float_t &x)
  {
    float_t _x = x;
    shrink_integer_zero(_x);
    shrink_decimal_zero(_x);

    mympz::bignum_t y = x.integer_part;
    y.number.insert(y.number.begin(),
                    x.decimal_part.number.begin(),
                    x.decimal_part.number.end());
    return y;
  }

  size_t expand_decimal_word(mympz::unit_t &w, mympz::unit_t m)
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

  size_t expand_decimal(mympz::bignum_t &x, const mympz::bignum_t &y)
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
    mympz::bignum_t t = mympz::create(10);

    while (1)
    {
      if (mympz::cmp(u, t) > 0)
      {
        u = mympz::idiv(u, t);
        i++;
      }

      if (mympz::cmp(v, t) > 0)
      {
        v = mympz::idiv(v, t);
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
      x = mympz::mul(x, t);
    }

    return (j - i);
  }

} // namespace mympf