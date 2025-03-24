// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from hwpub:msg/Hwmsg.idl
// generated code does not contain a copyright notice
#include "hwpub/msg/detail/hwmsg__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "hwpub/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "hwpub/msg/detail/hwmsg__struct.h"
#include "hwpub/msg/detail/hwmsg__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "rosidl_runtime_c/string.h"  // s
#include "rosidl_runtime_c/string_functions.h"  // s

// forward declare type support functions


using _Hwmsg__ros_msg_type = hwpub__msg__Hwmsg;

static bool _Hwmsg__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _Hwmsg__ros_msg_type * ros_message = static_cast<const _Hwmsg__ros_msg_type *>(untyped_ros_message);
  // Field name: s
  {
    const rosidl_runtime_c__String * str = &ros_message->s;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: num
  {
    cdr << ros_message->num;
  }

  // Field name: b
  {
    cdr << (ros_message->b ? true : false);
  }

  return true;
}

static bool _Hwmsg__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _Hwmsg__ros_msg_type * ros_message = static_cast<_Hwmsg__ros_msg_type *>(untyped_ros_message);
  // Field name: s
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->s.data) {
      rosidl_runtime_c__String__init(&ros_message->s);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->s,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 's'\n");
      return false;
    }
  }

  // Field name: num
  {
    cdr >> ros_message->num;
  }

  // Field name: b
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->b = tmp ? true : false;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_hwpub
size_t get_serialized_size_hwpub__msg__Hwmsg(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _Hwmsg__ros_msg_type * ros_message = static_cast<const _Hwmsg__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name s
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->s.size + 1);
  // field.name num
  {
    size_t item_size = sizeof(ros_message->num);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name b
  {
    size_t item_size = sizeof(ros_message->b);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _Hwmsg__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_hwpub__msg__Hwmsg(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_hwpub
size_t max_serialized_size_hwpub__msg__Hwmsg(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // member: s
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: num
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: b
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = hwpub__msg__Hwmsg;
    is_plain =
      (
      offsetof(DataType, b) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _Hwmsg__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_hwpub__msg__Hwmsg(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_Hwmsg = {
  "hwpub::msg",
  "Hwmsg",
  _Hwmsg__cdr_serialize,
  _Hwmsg__cdr_deserialize,
  _Hwmsg__get_serialized_size,
  _Hwmsg__max_serialized_size
};

static rosidl_message_type_support_t _Hwmsg__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_Hwmsg,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, hwpub, msg, Hwmsg)() {
  return &_Hwmsg__type_support;
}

#if defined(__cplusplus)
}
#endif
