#include <mympf/mympf.h>

namespace mympf
{

  float_t div(const float_t &x, const float_t &y, size_t precision)
  {
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
    bool sub_one = false;
    if (mympz::is_zero(q))
    {
      q = mympz::const_1;
      sub_one = true;
    }
    else
    {
      q = mympz::const_0;
    }

    size_t c = count_digits(yn), d = 0, e = 0;
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
      // std::cout << "d = " << d << std::endl;
      if (mympz::ucmp(p, yn) < 0)
      {
        p = mympz::mul(p, mympz::const_10);
        d++;
      }

      // 如果d不为0，则商扩大位数
      if (d)
        d--;

      // 相除
      res = mympz::div(p, yn);
      p = res.second;
      // std::cout << "q = " << mympz::print_string(res.first) << std::endl;
      // std::cout << "r = " << mympz::print_string(res.second) << std::endl;

      //
      // 设置商
      //
      t = mympz::exp(mympz::const_10, mympz::create(d));
      q = mympz::mul(q, t);
      std::cout << "q = " << mympz::print_string(q) << std::endl;
      q = mympz::uadd(q, res.first);
      e += count_digits(res.first);
    }

    //
    // 设置精度
    //
    if (!i)
    {
      z.precision = precision;
    }
    else
    {
      z.precision = e;
    }

    t = mympz::exp(mympz::const_10, mympz::create(e));
    result = mympz::mul(result, t);

    // 如果商之前是1，则现在减去。
    if (sub_one)
    {
      q = mympz::usub(q, t);
    }

    result = mympz::uadd(result, q);
    z.number = result;
    return z;
  }

} // namespace mympf