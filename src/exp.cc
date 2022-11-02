#include <mympf/mympf.h>

namespace mympf
{

  float_t exp(const float_t &x, const mympz::bignum_t &p)
  {
    float_t y;

    if (p.number.size() > 1)
    {
      mympf_exponent_is_too_big(p);
    }

    y.number = mympz::exp(x.number, p);
    y.precision = x.precision * p.number[0];

    return y;
  }

  float_t exp(const float_t &x, const size_t p)
  {
    return exp(x, mympz::create(p));
  }

  float_t exp(const float_t &x, const float_t &p)
  {
    return exp(x, integer_part(p).number);
  }

} // namespace mympf