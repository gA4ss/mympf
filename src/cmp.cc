#include <mympf/mympf.h>

namespace mympf
{

  int cmp(const float_t &x, const float_t &y)
  {
    int r = mympz::cmp(x.integer_part, y.integer_part);
    if (r == 0)
    {
      r = mympz::ucmp(x.decimal_part, y.decimal_part);
      return r;
    }
    return r;
  }

  int ucmp(const float_t &x, const float_t &y)
  {
    int r = mympz::ucmp(x.integer_part, y.integer_part);
    if (r == 0)
    {
      r = mympz::ucmp(x.decimal_part, y.decimal_part);
      return r;
    }
    return r;
  }

} // namespace mympf