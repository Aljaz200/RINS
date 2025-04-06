// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hwpub:srv/Customserv.idl
// generated code does not contain a copyright notice

#ifndef HWPUB__SRV__DETAIL__CUSTOMSERV__STRUCT_H_
#define HWPUB__SRV__DETAIL__CUSTOMSERV__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 's'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/Customserv in the package hwpub.
typedef struct hwpub__srv__Customserv_Request
{
  rosidl_runtime_c__String s;
  int64_t time;
} hwpub__srv__Customserv_Request;

// Struct for a sequence of hwpub__srv__Customserv_Request.
typedef struct hwpub__srv__Customserv_Request__Sequence
{
  hwpub__srv__Customserv_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hwpub__srv__Customserv_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'st'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/Customserv in the package hwpub.
typedef struct hwpub__srv__Customserv_Response
{
  rosidl_runtime_c__String st;
} hwpub__srv__Customserv_Response;

// Struct for a sequence of hwpub__srv__Customserv_Response.
typedef struct hwpub__srv__Customserv_Response__Sequence
{
  hwpub__srv__Customserv_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hwpub__srv__Customserv_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HWPUB__SRV__DETAIL__CUSTOMSERV__STRUCT_H_
