#ifndef MYMPF_EXCEPTION_H_
#define MYMPF_EXCEPTION_H_

namespace mympf
{
#define mympf_exception(format, ...)                                              \
  {                                                                               \
    throw my::MyException("<mympf>",                                              \
                          __FILE__, __LINE__, __FUNCTION__, format, __VA_ARGS__); \
  }

#define mympf_exponent_is_too_big(e)                                                              \
  {                                                                                               \
    throw my::MyException("<mympf>",                                                              \
                          __FILE__, __LINE__, __FUNCTION__, "%s", "exponent " #e " is too big."); \
  }

#define unknown_mympf_exception()                                                                   \
  {                                                                                                 \
    throw my::MyException("<mympf> Unknown Exception", __FILE__, __LINE__, __FUNCTION__, "%s", ""); \
  }
} // namespace mympf

#endif // MYMPF_EXCEPTION_H_