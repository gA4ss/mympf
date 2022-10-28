#include <mympf/mympf.h>

namespace mympf
{

  int cmp(const float_t &x, const float_t &y)
  {
    mympz::bignum_t _x = x.number;
    mympz::bignum_t _y = y.number;
    if (x.precision > y.precision)
    {
      expand_precision(_y, x.precision);
    }
    else if (x.precision < y.precision)
    {
      expand_precision(_x, y.precision);
    }

    return mympz::cmp(_x, _y);
  }

  int ucmp(const float_t &x, const float_t &y)
  {
    mympz::bignum_t _x = x.number;
    mympz::bignum_t _y = y.number;
    if (x.precision > y.precision)
    {
      expand_precision(_y, x.precision);
    }
    else if (x.precision < y.precision)
    {
      expand_precision(_x, y.precision);
    }

    return mympz::ucmp(_x, _y);
  }

} // namespace mympf