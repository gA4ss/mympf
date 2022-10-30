#include <mympf/mympf.h>

namespace mympf
{

  std::string print_string(const float_t &x)
  {
    if (x.number.number.empty())
      return "";

    std::string str = "";
    if (x.precision)
    {
      str = mympz::print_string(x.number);
      if (str[0] == '-')
      {
        str.erase(str.begin());
      }

      if (x.precision < str.length())
      {
        str.insert(str.end() - x.precision, '.');
      }
      else if (x.precision == str.length())
      {
        str = std::string("0.") + str;
      }
      else
      {
        size_t c = x.precision - str.length() + 1;
        std::string zs = std::string(c, '0');
        str = zs + str;
        str.insert(str.begin() + 1, '.');
      }
    }
    else
    {
      //
      // 不存在精度，则后末尾加0进行输出。
      //
      str = mympz::print_string(x.number);
      str += ".0";
      return str;
    }

    if (x.neg())
      str.insert(str.begin(), '-');

    return str;
  }

} // namespace mympf