// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from dis_tutorial1:srv/SumService.idl
// generated code does not contain a copyright notice

#ifndef DIS_TUTORIAL1__SRV__DETAIL__SUM_SERVICE__STRUCT_H_
#define DIS_TUTORIAL1__SRV__DETAIL__SUM_SERVICE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'request_text'
#include "rosidl_runtime_c/string.h"
// Member 'numbers'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in srv/SumService in the package dis_tutorial1.
typedef struct dis_tutorial1__srv__SumService_Request
{
  rosidl_runtime_c__String request_text;
  rosidl_runtime_c__int32__Sequence numbers;
} dis_tutorial1__srv__SumService_Request;

// Struct for a sequence of dis_tutorial1__srv__SumService_Request.
typedef struct dis_tutorial1__srv__SumService_Request__Sequence
{
  dis_tutorial1__srv__SumService_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} dis_tutorial1__srv__SumService_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'response_text'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/SumService in the package dis_tutorial1.
typedef struct dis_tutorial1__srv__SumService_Response
{
  rosidl_runtime_c__String response_text;
  int32_t sum;
} dis_tutorial1__srv__SumService_Response;

// Struct for a sequence of dis_tutorial1__srv__SumService_Response.
typedef struct dis_tutorial1__srv__SumService_Response__Sequence
{
  dis_tutorial1__srv__SumService_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} dis_tutorial1__srv__SumService_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DIS_TUTORIAL1__SRV__DETAIL__SUM_SERVICE__STRUCT_H_
