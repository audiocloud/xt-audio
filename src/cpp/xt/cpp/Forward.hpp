#ifndef XT_FORWARD_HPP
#define XT_FORWARD_HPP

#include <xt/cpp/XtCore.hpp>

namespace Xt::Detail {

inline void 
HandleError(XtError error);
inline void XT_CALLBACK 
ForwardOnXRun(int32_t index, void* user);
inline void XT_CALLBACK 
ForwardOnError(char const* location, char const* message);
inline void XT_CALLBACK 
ForwardOnBuffer(XtStream const* coreStream, XtBuffer const* coreBuffer, void* user);

} // namespace Xt::Detail
#endif // XT_FORWARD_HPP