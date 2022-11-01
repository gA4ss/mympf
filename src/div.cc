#include <mympf/mympf.h>
#include "debug.h"

namespace mympf
{

  float_t div(const float_t &x, const float_t &y, size_t precision)
  {
    mympf_dbgprint_fmt("div(%s, %s) with %lu precision.\n",
                       print_string(x).c_str(),
                       print_string(y).c_str(),
                       precision);

    float_t z;
    mympz::bignum_t xn = x.number;
    mympz::bignum_t yn = y.number;

    if (x.precision > y.precision)
    {
      expand_precision(yn, y.precision, x.precision);
    }
    else if (x.precision < y.precision)
    {
      expand_precision(xn, x.precision, y.precision);
    }

    mympz::division_result_t res = mympz::div(xn, yn);
    mympz::bignum_t result = res.first;

    mympz::bignum_t t;
    mympz::bignum_t p = res.second;
    mympz::bignum_t q = res.first;

    //
    // 如果商是零，则首先设商为1
    //
    bool e = false;
    if (mympz::is_zero(q))
    {
      q = mympz::const_1;
      e = true;
    }
    else
    {
      q = mympz::const_0;
    }

    size_t c = count_digits(yn), d = 0;
    // size_t i = precision + 1;     // 加1多一位为了进行四舍五入
    int i = static_cast<int>(precision);
    while (i--)
    {
      if (mympz::is_zero(p))
      {
        break;
      }

      //
      // 这里余数肯定小于除数
      //
      d = count_digits(p);
      d = expand_precision(p, d, c);
      if (mympz::ucmp(p, yn) < 0)
      {
        p = mympz::mul(p, mympz::const_10);
        d++;
      }

      // 相除
      res = mympz::div(p, yn);
      p = res.second;
      mympf_dbgprint_fmt("q = %s.\n", mympz::print_string(res.first).c_str());
      mympf_dbgprint_fmt("r = %s.\n", mympz::print_string(res.second).c_str());

      //
      // 设置商
      //
      t = mympz::exp(mympz::const_10, mympz::create(d));
      q = mympz::mul(q, t);
      q = mympz::uadd(q, res.first);
      mympf_dbgprint_fmt("qs = %s.\n", mympz::print_string(q).c_str());
    }

    //
    // 设置精度
    //
    z.precision = count_digits(q);
    if (e)
    {
      (z.precision)--;
    }
    mympf_dbgprint_fmt("z.precision = %lu.\n", z.precision);

    t = mympz::exp(mympz::const_10, mympz::create(z.precision));
    result = mympz::mul(result, t);
    if (e)
    {
      q = mympz::usub(q, t);
    }
    result = mympz::uadd(result, q);
    z.number = result;
    z.set_neg(x.neg() ^ y.neg());
    return z;
  }

  float_t idiv(const float_t &x, const float_t &y)
  {
    float_t z;
    mympz::bignum_t _x = x.number;
    shrink_precision(_x, x.precision, 0);
    mympz::bignum_t _y = y.number;
    shrink_precision(_y, y.precision, 0);
    z.number = mympz::idiv(_x, _y);
    z.precision = 0;
    return z;
  }

} // namespace mympf