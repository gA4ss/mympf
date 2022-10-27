#include <mympf/mympf.h>

namespace mympf
{

#define __earse_char(s, c)                               \
  {                                                      \
    (s).erase(                                           \
        std::remove_if((s).begin(), (s).end(),           \
                       [](char x) { return (c) == x; }), \
        (s).end());                                      \
  }

  static size_t __count_precision_from_string(const std::string &str)
  {
    size_t precision = 0;

    //
    // 去除负号
    //
    std::string s = str;
    if (str[0] == '-') {
      s = str.substr(1);
    }

    std::size_t found = s.find('.');
    if (found == 0)
    {
      precision = s.length() - 1;
    }
    else if ((found == std::string::npos) || (found == str.length() - 1))
    {
      precision = 0;
    }
    else
    {
      s = s.substr(found + 1);
      precision = s.length();
    }
    return precision;
  }

  float_t create(std::string str)
  {
    float_t r;

    __earse_char(str, ' ');
    r.precision = __count_precision_from_string(str);
    __earse_char(str, '.');
    r.number = mympz::create(str);

    return r;
  }

  float_t create(const mympz::bignum_t &number, size_t precision)
  {
    float_t r;
    r.number = number;
    r.precision = precision;
    return r;
  }

} // namespace mympf