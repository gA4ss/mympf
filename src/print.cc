#include <mympf/mympf.h>

namespace mympf
{

  std::string print_string(const float_t &x, bool hex, bool low_case)
  {
    if (x.integer_part.number.empty() || x.decimal_part.number.empty())
      return "";

    std::string str = mympz::print_string(x.integer_part, hex, low_case);
    if (str == "0") {
      if (x.neg())
        str = "-0";
    }
    str += ".";
    str += mympz::print_string(x.decimal_part, hex, low_case);

    return str;
  }

} // namespace mympf