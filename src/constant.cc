#include <mympf/mympf.h>

namespace mympf
{

  float_t const_null = create("null");
  float_t const_0 = create(0, 0);
  float_t const_1 = create(1, 0);
  float_t const_10 = create(10, 0);

  void init()
  {
    mympz::init();
    if (bn_size(const_0.number) == 0)
    {
      const_0 = create(0, 0);
    }

    if (bn_size(const_1.number) == 0)
    {
      const_1 = create(0, 0);
    }

    if (bn_size(const_10.number) == 0)
    {
      const_10 = create(0, 0);
    }
  }

} // namespace mympf