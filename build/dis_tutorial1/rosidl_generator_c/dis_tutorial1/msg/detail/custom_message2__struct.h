// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from dis_tutorial1:msg/CustomMessage2.idl
// generated code does not contain a copyright notice

#ifndef DIS_TUTORIAL1__MSG__DETAIL__CUSTOM_MESSAGE2__STRUCT_H_
#define DIS_TUTORIAL1__MSG__DETAIL__CUSTOM_MESSAGE2__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'text'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/CustomMessage2 in the package dis_tutorial1.
typedef struct dis_tutorial1__msg__CustomMessage2
{
  rosidl_runtime_c__String text;
  int32_t number;
  bool flag;
} dis_tutorial1__msg__CustomMessage2;

// Struct for a sequence of dis_tutorial1__msg__CustomMessage2.
typedef struct dis_tutorial1__msg__CustomMessage2__Sequence
{
  dis_tutorial1__msg__CustomMessage2 * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} dis_tutorial1__msg__CustomMessage2__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DIS_TUTORIAL1__MSG__DETAIL__CUSTOM_MESSAGE2__STRUCT_H_
