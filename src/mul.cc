#include <mympf/mympf.h>

namespace mympf
{

  float_t mul(const float_t &x, const float_t &y)
  {
    float_t z;
    size_t z_precision;
    mympz::bignum_t xn = x.number;
    mympz::bignum_t yn = y.number;

    if (x.precision > y.precision)
    {
      expand_precision(yn, y.precision, x.precision);
      z_precision = 2 * x.precision;
    }
    else if (x.precision < y.precision)
    {
      expand_precision(xn, x.precision, y.precision);
      z_precision = 2 * y.precision;
    }
    else
    {
      z_precision = 2 * x.precision;
    }

    z.number = mympz::mul(xn, yn);
    z.precision = z_precision;
    z.set_neg(x.neg() ^ y.neg());
    return z;
  }

} // namespace mympf
