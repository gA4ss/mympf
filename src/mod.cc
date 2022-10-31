#include <mympf/mympf.h>

namespace mympf {

float_t mod(const float_t &x, const float_t &y) {
  float_t z;

  // 首先进行整除
  z.number = mympz::idiv(x.number, y.number);

  return z;
}

} // namespace mympf
