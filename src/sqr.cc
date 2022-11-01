#include <mympf/mympf.h>

namespace mympf
{

  float_t sqr(const float_t &x)
  {
    float_t y;
    size_t y_precision;

    y_precision = 2 * x.precision;
    y.number = mympz::sqr(x.number);
    y.precision = y_precision;
    return y;
  }

} // namespace mympf