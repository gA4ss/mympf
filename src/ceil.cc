#include <mympf/mympf.h>

namespace mympf
{

  float_t ceil(const float_t &x)
  {
    if (!x.precision)
      return x;

    float_t y = x;
    shrink_precision(y, 0);
    if (!y.neg())
    {
      y = uadd(y, const_1);
    }
    y.set_neg(x.neg());
    return y;
  }

} // namespace mympf
