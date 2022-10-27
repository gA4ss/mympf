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
    float_t z;
    z.number = mympz::usub(x.number, y.number);
    z.precision = x.precision > y.precision ? x.precision : y.precision;
    return z;
  }

} // namespace mympf
