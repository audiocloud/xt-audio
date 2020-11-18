#ifndef XT_AUDIO_STRUCTS_H
#define XT_AUDIO_STRUCTS_H

#include <xt/audio/Enums.h>
#include <xt/audio/Shared.h>
#include <xt/audio/Callbacks.h>
#include <cstdint>

typedef struct XtMix
{
  int32_t rate;
  XtSample sample;
} XtMix;

typedef struct XtBuffer 
{
  void const* input;
  void* output;
  double time;
  uint64_t position;
  XtError error;
  int32_t frames;
  XtBool timeValid;
} XtBuffer;

typedef struct XtVersion 
{
  int32_t major;
  int32_t minor;
} XtVersion;

typedef struct XtLatency 
{
  double input;
  double output;
} XtLatency;

typedef struct XtChannels 
{
  int32_t inputs;
  uint64_t inMask;
  int32_t outputs;
  uint64_t outMask;
} XtChannels;

typedef struct XtFormat 
{
  XtMix mix;
  XtChannels channels;
} XtFormat;

typedef struct XtErrorInfo 
{
  XtSystem system;
  XtCause cause;
  char const* text;
  uint32_t fault;
} XtErrorInfo;

typedef struct XtBufferSize
{
  double min;
  double max;
  double current;
} XtBufferSize;

typedef struct XtAttributes
{
  int32_t size;
  int32_t count;
  XtBool isFloat;
  XtBool isSigned;
} XtAttributes;

typedef struct XtStreamParams
{
  XtBool interleaved;
  XtOnBuffer onBuffer;
  XtOnXRun onXRun;
} XtStreamParams;

typedef struct XtDeviceStreamParams 
{
  XtStreamParams stream;
  XtFormat format;
  double bufferSize;
} XtDeviceStreamParams;

typedef struct XtAggregateDeviceParams 
{
  XtDevice* device;
  XtChannels channels;
  double bufferSize;
} XtAggregateDeviceParams;

typedef struct XtAggregateStreamParams 
{
  XtStreamParams stream;
  XtAggregateDeviceParams* devices;
  int32_t count;
  XtMix mix;
  XtDevice const* master;
} XtAggregateStreamParams;

#endif // XT_AUDIO_STRUCTS_H