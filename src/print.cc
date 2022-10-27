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
      str.insert(str.end() - x.precision, '.');
    }
    else
    {
      str = mympz::print_string(x.number);
      str += ".0";
    }

    // 整理一下字符串
    size_t found = str.find('.');
    if (found == 0)
    {
      str = '0' + str;
    }
    else if ((found == 1) && (str[0] == '-'))
    {
      str.insert(str.begin() + 1, '0');
    }

    return str;
  }

} // namespace mympf