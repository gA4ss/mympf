#include <mympf/mympf.h>

namespace mympf
{

  float_t mod(const float_t &x, const float_t &y, size_t precision)
  {
    mympf_dbgprint_fmt("mod(%s, %s) with %lu precision.\n",
                       print_string(x).c_str(),
                       print_string(y).c_str(),
                       precision);

    if (ucmp(x, y) == 0)
    {
      return create(0);
    }
    else if (ucmp(x, y) < 0)
    {
      //
      // 区分同号与异号
      //
      if (x.neg() ^ y.neg())
      {
        return usub(y, x);
      }
      else
      {
        return x;
      }
    }

    float_t q = div(x, y, precision);
    q = floor(q);

#if DEBUG
    float_t __dbg = mul(y, q);
    mympf_dbgprint_fmt("t = mul(y, q) = %s.\n", print_string(__dbg).c_str());
    __dbg = x.neg() ^ y.neg() ? sub(x, __dbg) : usub(x, __dbg);
    __dbg.set_neg(x.neg());
    mympf_dbgprint_fmt("sub(x, t) = %s.\n", print_string(__dbg).c_str());
    return __dbg;
#else
    float_t r = x.neg() ^ y.neg() ? sub(x, mul(y, q)) : usub(x, mul(y, q));
    r.set_neg(x.neg());
    return r;
#endif
  }

} // namespace mympf
