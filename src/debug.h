#ifndef MYMPF_DEBUG_H_
#define MYMPF_DEBUG_H_

namespace mympf
{
  void dbgprint(const char *filepath, int lineno, const char *funcname,
                const char *fmt, ...);

#ifdef ENABLE_DEBUG_INFO
#define mympf_dbgprint(s) dbgprint(__FILE__, __LINE__, __FUNCTION__, "%s", (s))
#define mympf_dbgprint_fmt(format, ...) dbgprint(__FILE__, __LINE__, __FUNCTION__, format, __VA_ARGS__)
#else
#define mympf_dbgprint(s)
#define mympf_dbgprint_fmt(format, ...)
#endif

} // namespace mympf

#endif // MYMPF_DEBUG_H_