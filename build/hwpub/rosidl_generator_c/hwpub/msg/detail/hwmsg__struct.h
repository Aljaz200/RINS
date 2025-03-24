// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hwpub:msg/Hwmsg.idl
// generated code does not contain a copyright notice

#ifndef HWPUB__MSG__DETAIL__HWMSG__STRUCT_H_
#define HWPUB__MSG__DETAIL__HWMSG__STRUCT_H_

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

/// Struct defined in msg/Hwmsg in the package hwpub.
typedef struct hwpub__msg__Hwmsg
{
  rosidl_runtime_c__String s;
  int64_t num;
  bool b;
} hwpub__msg__Hwmsg;

// Struct for a sequence of hwpub__msg__Hwmsg.
typedef struct hwpub__msg__Hwmsg__Sequence
{
  hwpub__msg__Hwmsg * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hwpub__msg__Hwmsg__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HWPUB__MSG__DETAIL__HWMSG__STRUCT_H_
