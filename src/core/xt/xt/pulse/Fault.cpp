#include <xt/pulse/Fault.hpp>
#if !XT_ENABLE_PULSE_AUDIO

XtCause XtiGetPulseAudioFaultCause(XtFault fault) 
{ return XtCauseUnknown; }
char const* XtiGetPulseAudioFaultText(XtFault fault) 
{ return nullptr; }

#else // !XT_ENABLE_PULSE_AUDIO
#include <pulse/pulseaudio.h>

char const*
XtiGetPulseAudioFaultText(XtFault fault)
{ return fault == XT_PA_ERR_FORMAT? "XT_PA_ERR_FORMAT": pa_strerror(fault); }

XtCause
XtiGetPulseAudioFaultCause(XtFault fault)
{ 
  switch(fault) {
  case XT_PA_ERR_FORMAT: return XtCauseFormat;
  case PA_ERR_BUSY:
  case PA_ERR_EXIST:
  case PA_ERR_KILLED:
  case PA_ERR_NOENTITY: return XtCauseEndpoint;
  case PA_ERR_VERSION:
  case PA_ERR_INVALIDSERVER:
  case PA_ERR_MODINITFAILED:
  case PA_ERR_CONNECTIONREFUSED:
  case PA_ERR_CONNECTIONTERMINATED: return XtCauseService;
  default: return XtCauseUnknown;
  }
}

#endif // !XT_ENABLE_PULSE_AUDIO