// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from hwpub:srv/Customserv.idl
// generated code does not contain a copyright notice
#include "hwpub/srv/detail/customserv__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "hwpub/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "hwpub/srv/detail/customserv__struct.h"
#include "hwpub/srv/detail/customserv__functions.h"
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


using _Customserv_Request__ros_msg_type = hwpub__srv__Customserv_Request;

static bool _Customserv_Request__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _Customserv_Request__ros_msg_type * ros_message = static_cast<const _Customserv_Request__ros_msg_type *>(untyped_ros_message);
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

  // Field name: time
  {
    cdr << ros_message->time;
  }

  return true;
}

static bool _Customserv_Request__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _Customserv_Request__ros_msg_type * ros_message = static_cast<_Customserv_Request__ros_msg_type *>(untyped_ros_message);
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

  // Field name: time
  {
    cdr >> ros_message->time;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_hwpub
size_t get_serialized_size_hwpub__srv__Customserv_Request(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _Customserv_Request__ros_msg_type * ros_message = static_cast<const _Customserv_Request__ros_msg_type *>(untyped_ros_message);
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
  // field.name time
  {
    size_t item_size = sizeof(ros_message->time);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _Customserv_Request__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_hwpub__srv__Customserv_Request(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_hwpub
size_t max_serialized_size_hwpub__srv__Customserv_Request(
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
  // member: time
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = hwpub__srv__Customserv_Request;
    is_plain =
      (
      offsetof(DataType, time) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _Customserv_Request__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_hwpub__srv__Customserv_Request(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_Customserv_Request = {
  "hwpub::srv",
  "Customserv_Request",
  _Customserv_Request__cdr_serialize,
  _Customserv_Request__cdr_deserialize,
  _Customserv_Request__get_serialized_size,
  _Customserv_Request__max_serialized_size
};

static rosidl_message_type_support_t _Customserv_Request__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_Customserv_Request,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, hwpub, srv, Customserv_Request)() {
  return &_Customserv_Request__type_support;
}

#if defined(__cplusplus)
}
#endif

// already included above
// #include <cassert>
// already included above
// #include <limits>
// already included above
// #include <string>
// already included above
// #include "rosidl_typesupport_fastrtps_c/identifier.h"
// already included above
// #include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
// already included above
// #include "hwpub/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
// already included above
// #include "hwpub/srv/detail/customserv__struct.h"
// already included above
// #include "hwpub/srv/detail/customserv__functions.h"
// already included above
// #include "fastcdr/Cdr.h"

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

// already included above
// #include "rosidl_runtime_c/string.h"  // st
// already included above
// #include "rosidl_runtime_c/string_functions.h"  // st

// forward declare type support functions


using _Customserv_Response__ros_msg_type = hwpub__srv__Customserv_Response;

static bool _Customserv_Response__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _Customserv_Response__ros_msg_type * ros_message = static_cast<const _Customserv_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: st
  {
    const rosidl_runtime_c__String * str = &ros_message->st;
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

  return true;
}

static bool _Customserv_Response__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _Customserv_Response__ros_msg_type * ros_message = static_cast<_Customserv_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: st
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->st.data) {
      rosidl_runtime_c__String__init(&ros_message->st);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->st,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'st'\n");
      return false;
    }
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_hwpub
size_t get_serialized_size_hwpub__srv__Customserv_Response(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _Customserv_Response__ros_msg_type * ros_message = static_cast<const _Customserv_Response__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name st
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->st.size + 1);

  return current_alignment - initial_alignment;
}

static uint32_t _Customserv_Response__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_hwpub__srv__Customserv_Response(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_hwpub
size_t max_serialized_size_hwpub__srv__Customserv_Response(
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

  // member: st
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

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = hwpub__srv__Customserv_Response;
    is_plain =
      (
      offsetof(DataType, st) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _Customserv_Response__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_hwpub__srv__Customserv_Response(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_Customserv_Response = {
  "hwpub::srv",
  "Customserv_Response",
  _Customserv_Response__cdr_serialize,
  _Customserv_Response__cdr_deserialize,
  _Customserv_Response__get_serialized_size,
  _Customserv_Response__max_serialized_size
};

static rosidl_message_type_support_t _Customserv_Response__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_Customserv_Response,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, hwpub, srv, Customserv_Response)() {
  return &_Customserv_Response__type_support;
}

#if defined(__cplusplus)
}
#endif

#include "rosidl_typesupport_fastrtps_cpp/service_type_support.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_c/identifier.h"
// already included above
// #include "hwpub/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "hwpub/srv/customserv.h"

#if defined(__cplusplus)
extern "C"
{
#endif

static service_type_support_callbacks_t Customserv__callbacks = {
  "hwpub::srv",
  "Customserv",
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, hwpub, srv, Customserv_Request)(),
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, hwpub, srv, Customserv_Response)(),
};

static rosidl_service_type_support_t Customserv__handle = {
  rosidl_typesupport_fastrtps_c__identifier,
  &Customserv__callbacks,
  get_service_typesupport_handle_function,
};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, hwpub, srv, Customserv)() {
  return &Customserv__handle;
}

#if defined(__cplusplus)
}
#endif
