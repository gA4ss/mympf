#include <mympf/mympf.h>

namespace mympf
{

  int cmp(const float_t &x, const float_t &y)
  {
    return mympz::cmp(x.number, y.number);
  }

  int ucmp(const float_t &x, const float_t &y)
  {
    return mympz::ucmp(x.number, y.number);
  }

} // namespace mympf