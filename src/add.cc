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
        z.set_neg(x.neg());
      }
      else
      {
        z = usub(y, x);
        z.set_neg(y.neg());
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
    float_t z;
    mympz::bignum_t xn = x.number;
    mympz::bignum_t yn = y.number;

    if (x.precision > y.precision)
    {
      expand_precision(yn, y.precision, x.precision);
    }
    else if (x.precision < y.precision)
    {
      expand_precision(xn, x.precision, y.precision);
    }

    z.number = mympz::uadd(xn, yn);
    z.precision = x.precision > y.precision ? x.precision : y.precision;
    shrink_zero_precision(z);
    return z;
  }

} // namespace mympf