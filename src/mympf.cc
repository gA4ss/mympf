#include <mympf/mympf.h>

namespace mympf
{

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