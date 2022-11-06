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
        z = usub(x, y);
        if (neg)
        {
          z.set_neg(1);
        }
      }
      else
      {
        z = usub(y, x);
        if (!neg)
        {
          z.set_neg(1);
        }
      }
    }

    return z;
  }

  float_t usub(const float_t &x, const float_t &y)
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

    z.number = mympz::usub(xn, yn);
    z.precision = x.precision > y.precision ? x.precision : y.precision;
    shrink_zero_precision(z);
    return z;
  }

} // namespace mympf
