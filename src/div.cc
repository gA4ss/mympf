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
    mympz::bignum_t q = mympz::const_0; // 为了补位
    bool qz = true;                     // 表示q为0
    bool e = false;                     // 表示随后需要对占用位的商1进行减法

    //
    // 小数部分的除法
    //

    size_t b = 0;
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
      // p < yn
      // b <= c
      //
      b = count_digits(p);
      d = expand_precision(p, b, c);
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
      // 如果商q为0，并且新的被除数数与除数的位数相差大于1
      // 则有可能在商上产生用0占位。所以这时要把商当作1来计算
      // 并且表明这个变换，在随后在减去这个1。
      //
      // 被除数与除数如果位数不相差1位以上则不可能产生用0占位
      // 的情况。
      //
      if ((qz) && (d > 1))
      {
        e = true;
        q = mympz::const_1;
      }
      t = mympz::exp(mympz::const_10, mympz::create(d));
      q = mympz::mul(q, t);
      q = mympz::uadd(q, res.first);
      mympf_dbgprint_fmt("qs = %s.\n", mympz::print_string(q).c_str());

      // 这里使用qz表示q不为0则原因是，不想使用mympz::is_zero，感觉在循环中这样
      // 影响效率。
      // 运行到此，q肯定不为0。
      qz = false;
    }

    //
    // 设置精度
    //
    z.precision = e ? count_digits(q) - 1 : count_digits(q);
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
    shrink_zero_precision(z);
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
    shrink_zero_precision(z);
    return z;
  }

} // namespace mympf