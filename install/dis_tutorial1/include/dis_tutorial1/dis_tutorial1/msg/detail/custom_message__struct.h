// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from dis_tutorial1:msg/CustomMessage.idl
// generated code does not contain a copyright notice

#ifndef DIS_TUTORIAL1__MSG__DETAIL__CUSTOM_MESSAGE__STRUCT_H_
#define DIS_TUTORIAL1__MSG__DETAIL__CUSTOM_MESSAGE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'content'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/CustomMessage in the package dis_tutorial1.
/**
  * request constants
  * int8 FOO=1
  * int8 BAR=2
  * int32 y
  * another_pkg/AnotherMessage msg
  * response constants
  * uint32 SECRET=123456
  * another_pkg/YetAnotherMessage val
  * CustomMessageDefinedInThisPackage value
  * int32 result
 */
typedef struct dis_tutorial1__msg__CustomMessage
{
  rosidl_runtime_c__String content;
  uint8_t id;
} dis_tutorial1__msg__CustomMessage;

// Struct for a sequence of dis_tutorial1__msg__CustomMessage.
typedef struct dis_tutorial1__msg__CustomMessage__Sequence
{
  dis_tutorial1__msg__CustomMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} dis_tutorial1__msg__CustomMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DIS_TUTORIAL1__MSG__DETAIL__CUSTOM_MESSAGE__STRUCT_H_
