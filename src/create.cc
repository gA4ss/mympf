#include <mympf/mympf.h>

namespace mympf
{

  float_t create(std::string str, bool hex)
  {
    float_t r;

    std::size_t found = str.find('.');
    if (found == 0)
    {
      r.integer_part.neg = 0;
      r.integer_part.number.push_back(0);
      r.decimal_part = mympz::create(str.substr(1), hex);
    }
    else if ((found == std::string::npos) ||
             (found == str.length() - 1))
    {
      r.decimal_part.number.push_back(0);
      r.integer_part = mympz::create(str.substr(0, found), hex);
    }
    else
    {
      r.integer_part = mympz::create(str.substr(0, found), hex);
      r.decimal_part = mympz::create(str.substr(found + 1), hex);
    }

    return r;
  }

  float_t create(const mympz::bignum_t &integer, const mympz::bignum_t &decimal)
  {
    float_t r;
    r.integer_part = integer;
    r.decimal_part = decimal;
    return r;
  }

  float_t create(const mympz::number_t &integer, const mympz::number_t &decimal, int neg)
  {
    float_t r;
    r.integer_part.number = integer;
    r.decimal_part.number = decimal;
    r.integer_part.neg = neg;
    return r;
  }

} // namespace mympf