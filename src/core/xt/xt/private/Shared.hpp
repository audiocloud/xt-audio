#ifndef XT_PRIVATE_SHARED_HPP
#define XT_PRIVATE_SHARED_HPP

#include <xt/api/public/Enums.h>
#include <xt/api/public/Shared.h>
#include <xt/api/public/Structs.h>
#include <atomic>
#include <cstdint>

typedef uint32_t XtFault;

#define XT_STRINGIFY(s) #s
#define XT_TRACE(m) XtiTrace({__FILE__,  __func__, __LINE__}, m)
#define XT_ASSERT(c) ((c) || (XtiAssert({__FILE__,  __func__, __LINE__}, #c), 0))

inline bool
XtiCompareExchange(std::atomic_int& value, int32_t expected, int32_t desired)
{ return value.compare_exchange_strong(expected, desired); }

bool
XtiCalledOnMainThread();
int32_t
XtiGetPopCount64(uint64_t x);
uint32_t
XtiGetErrorFault(XtError error);
int32_t
XtiGetSampleSize(XtSample sample);
XtError
XtiCreateError(XtSystem system, XtFault fault);
XtServiceError
XtiGetServiceError(XtSystem system, XtFault fault);
void
XtiTrace(XtLocation const& location, char const* msg);
void
XtiAssert(XtLocation const& location, char const* expr);
void
XtiCopyString(char const* source, char* buffer, int32_t* size);
void
XtiDeinterleave(void** dst, void const* src, int32_t frames, int32_t channels, int32_t size);
void
XtiInterleave(void* dst, void const* const* src, int32_t frames, int32_t channels, int32_t size);

#endif // XT_PRIVATE_SHARED_HPP