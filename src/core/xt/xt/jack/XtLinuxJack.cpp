#if XT_ENABLE_JACK
#include <xt/api/private/Platform.hpp>
#include <xt/api/private/Service.hpp>
#include <xt/api/private/Device.hpp>
#include <xt/api/private/Stream.hpp>
#include <xt/private/Shared.hpp>
#include <xt/private/Services.hpp>
#include <jack/jack.h>
#include <vector>
#include <memory>
#include <sstream>

// ---- local ----

// ---- forward ----

struct JackStream: public XtStream {
  const XtJackClient client;
  std::vector<XtJackPort> inputs;
  std::vector<XtJackPort> outputs;
  std::vector<void*> inputChannels;
  std::vector<void*> outputChannels;
  std::vector<XtJackConnection> connections;
  XT_IMPLEMENT_STREAM();
  XT_IMLEMENT_STREAM_SYSTEM(JACK);

  JackStream(XtJackClient&& client, 
    std::vector<XtJackPort>&& inputs, std::vector<XtJackPort>&& outputs,
    size_t inputCount, size_t outputCount, size_t sampleSize, size_t bufferFrames):
  client(std::move(client)), inputs(std::move(inputs)), outputs(std::move(outputs)), 
  inputChannels(inputCount, nullptr), outputChannels(outputCount, nullptr),
  connections() { XT_ASSERT(this->client.client != nullptr); }
};

// ---- local ----

static int XRunCallback(void* arg) {
  static_cast<JackStream*>(arg)->OnXRun();
  return 0;
}

static int ProcessCallback(jack_nframes_t frames, void* arg) {
  
  void* input;
  void* output;
  float period;
  double time = 0.0;
  uint64_t position = 0;
  XtBool timeValid = XtFalse;
  jack_nframes_t jackPosition;
  jack_time_t jackTime, nextTime;
  JackStream* s = static_cast<JackStream*>(arg);
  int32_t sampleSize = XtiGetSampleSize(s->_params.format.mix.sample);
  XtBuffer xtBuffer = { 0 };

  input = s->inputs.size() == 0? nullptr: &s->inputChannels[0];
  output = s->outputs.size() == 0? nullptr: &s->outputChannels[0];  
  if(jack_get_cycle_times(s->client.client, &jackPosition, &jackTime, &nextTime, &period) == 0) {
    timeValid = XtTrue;
    position = jackPosition;
    time = jackTime / 1000.0;
  }

  for(int32_t i = 0; i < s->inputs.size(); i++)
    s->inputChannels[i] = jack_port_get_buffer(s->inputs[i].port, frames);
  for(int32_t i = 0; i < s->outputs.size(); i++)
    s->outputChannels[i] = jack_port_get_buffer(s->outputs[i].port, frames);
  xtBuffer.input = input;
  xtBuffer.output = output;
  xtBuffer.frames = frames;
  xtBuffer.time = time;
  xtBuffer.position = position;
  xtBuffer.timeValid = timeValid;
  s->OnBuffer(&xtBuffer);
  return 0;
}

// ---- service ----

// ---- device ----

XtFault JackDevice::OpenStreamCore(const XtDeviceStreamParams* params, bool secondary, void* user, XtStream** stream) {
  
  XtFault fault;
  jack_client_t* c;
  size_t bufferFrames, sampleSize;
  std::unique_ptr<JackStream> result;

  c = jack_client_open(XtPlatform::instance->_id.c_str(), JackNoStartServer, nullptr);
  if(c == nullptr)
    return ESRCH;
  XtJackClient streamClient(c);
  
  std::vector<XtJackPort> inputs, outputs;
  if((fault = XtiJackCreatePorts(c, params->format.channels.inputs, params->format.channels.inMask, 
    JackPortIsInput, inputs)) != 0)
    return fault;
  if((fault = XtiJackCreatePorts(c, params->format.channels.outputs, params->format.channels.outMask, 
    JackPortIsOutput, outputs)) != 0)
    return fault;

  sampleSize = XtiGetSampleSize(params->format.mix.sample);
  bufferFrames = jack_get_buffer_size(streamClient.client);
  result.reset(new JackStream(std::move(streamClient), std::move(inputs), std::move(outputs), 
    params->format.channels.inputs, params->format.channels.outputs, bufferFrames, sampleSize));
  if((fault = jack_set_xrun_callback(c, &XRunCallback, result.get())) != 0)
    return fault;
  if((fault = jack_set_process_callback(c, &ProcessCallback, result.get())) != 0)
    return fault;
  *stream = result.release();
  return 0;
}

// ---- stream ----

XtFault JackStream::Stop() {
  connections.clear();
  return jack_deactivate(client.client);
}

XtFault JackStream::GetFrames(int32_t* frames) const {
  *frames = jack_get_buffer_size(client.client);
  return 0;
}

XtFault JackStream::GetLatency(XtLatency* latency) const {
  return 0;
}

XtFault JackStream::Start() {
  
  XtFault fault;
  std::vector<XtJackConnection> connections;
  if((fault = jack_activate(client.client)) != 0)
    return fault;

  for(int32_t i = 0; i < _params.format.channels.inputs; i++) {
    if((fault = jack_connect(client.client, 
      inputs[i].connectTo, jack_port_name(inputs[i].port))) != 0)
      return fault;
    connections.emplace_back(XtJackConnection(client.client, 
      inputs[i].connectTo, jack_port_name(inputs[i].port)));
  }

  for(int32_t i = 0; i < _params.format.channels.outputs; i++) {
    if((fault = jack_connect(client.client, 
      jack_port_name(outputs[i].port), outputs[i].connectTo)) != 0)
      return fault;
    connections.emplace_back(XtJackConnection(client.client, 
      jack_port_name(outputs[i].port), outputs[i].connectTo));
  }
  
  this->connections = std::move(connections);
  return 0;
}

#endif // XT_ENABLE_JACK