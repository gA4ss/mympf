#include <mympf/mympf.h>

namespace mympf
{

  float_t ceil(const float_t &x)
  {
    if (!x.precision)
      return x;

    float_t y = x;
    const float_t const_1 = create(1, 0);
    shrink_precision(y, 0);
    if (!y.neg())
    {
      y = uadd(y, const_1);
    }
    y.set_neg(x.neg());
    return y;
  }

} // namespace mympf
