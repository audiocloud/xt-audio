#ifndef XT_API_PUBLIC_STREAM_H
#define XT_API_PUBLIC_STREAM_H

#include <xt/api/public/Shared.h>
#include <xt/api/public/Structs.h>
#include <cstdint>

#ifdef __cplusplus
extern "C" {
#endif

XT_API XtError XT_CALL 
XtStreamStop(XtStream* s);
XT_API XtError XT_CALL 
XtStreamStart(XtStream* s);
XT_API void XT_CALL 
XtStreamDestroy(XtStream* s);
XT_API const XtFormat* XT_CALL 
XtStreamGetFormat(XtStream const* s);
XT_API XtError XT_CALL 
XtStreamGetFrames(XtStream const* s, int32_t* frames);
XT_API XtError XT_CALL 
XtStreamGetLatency(XtStream const* s, XtLatency* latency);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // XT_API_PUBLIC_STREAM_H