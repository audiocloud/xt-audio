#ifndef XT_API_PRIVATE_DEVICE_LIST_HPP
#define XT_API_PRIVATE_DEVICE_LIST_HPP

#include <xt/api/public/Enums.h>
#include <xt/api/public/Shared.h>
#include <xt/private/Shared.hpp>

#define XT_IMPLEMENT_DEVICE_LIST(s)                                            \
  XtFault GetCount(int32_t* count) const override;                             \
  XtSystem GetSystem() const override { return XtSystem##s; }                  \
  XtFault GetId(int32_t index, char* buffer, int32_t* size) const override;    \
  XtFault GetName(char const* id, char* buffer, int32_t* size) const override; \
  XtFault GetDefaultId(XtBool output, char* buffer, int32_t* size) const override;

struct XtDeviceList
{
  virtual ~XtDeviceList() { };  
  virtual XtSystem GetSystem() const = 0;
  virtual XtFault GetCount(int32_t* count) const = 0;
  virtual XtFault GetId(int32_t index, char* buffer, int32_t* size) const = 0;
  virtual XtFault GetName(char const* id, char* buffer, int32_t* size) const = 0;
  virtual XtFault GetDefaultId(XtBool output, char* buffer, int32_t* size) const = 0;
};

#endif // XT_API_PRIVATE_DEVICE_LIST_HPP