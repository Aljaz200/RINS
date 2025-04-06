// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from hwpub:msg/Hwmsg.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "hwpub/msg/detail/hwmsg__rosidl_typesupport_introspection_c.h"
#include "hwpub/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "hwpub/msg/detail/hwmsg__functions.h"
#include "hwpub/msg/detail/hwmsg__struct.h"


// Include directives for member types
// Member `s`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void hwpub__msg__Hwmsg__rosidl_typesupport_introspection_c__Hwmsg_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  hwpub__msg__Hwmsg__init(message_memory);
}

void hwpub__msg__Hwmsg__rosidl_typesupport_introspection_c__Hwmsg_fini_function(void * message_memory)
{
  hwpub__msg__Hwmsg__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember hwpub__msg__Hwmsg__rosidl_typesupport_introspection_c__Hwmsg_message_member_array[3] = {
  {
    "s",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(hwpub__msg__Hwmsg, s),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "num",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(hwpub__msg__Hwmsg, num),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "b",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(hwpub__msg__Hwmsg, b),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers hwpub__msg__Hwmsg__rosidl_typesupport_introspection_c__Hwmsg_message_members = {
  "hwpub__msg",  // message namespace
  "Hwmsg",  // message name
  3,  // number of fields
  sizeof(hwpub__msg__Hwmsg),
  hwpub__msg__Hwmsg__rosidl_typesupport_introspection_c__Hwmsg_message_member_array,  // message members
  hwpub__msg__Hwmsg__rosidl_typesupport_introspection_c__Hwmsg_init_function,  // function to initialize message memory (memory has to be allocated)
  hwpub__msg__Hwmsg__rosidl_typesupport_introspection_c__Hwmsg_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t hwpub__msg__Hwmsg__rosidl_typesupport_introspection_c__Hwmsg_message_type_support_handle = {
  0,
  &hwpub__msg__Hwmsg__rosidl_typesupport_introspection_c__Hwmsg_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_hwpub
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, hwpub, msg, Hwmsg)() {
  if (!hwpub__msg__Hwmsg__rosidl_typesupport_introspection_c__Hwmsg_message_type_support_handle.typesupport_identifier) {
    hwpub__msg__Hwmsg__rosidl_typesupport_introspection_c__Hwmsg_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &hwpub__msg__Hwmsg__rosidl_typesupport_introspection_c__Hwmsg_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
