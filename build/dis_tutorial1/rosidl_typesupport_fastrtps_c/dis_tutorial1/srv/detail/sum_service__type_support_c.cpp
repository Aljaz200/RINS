// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from dis_tutorial1:srv/SumService.idl
// generated code does not contain a copyright notice
#include "dis_tutorial1/srv/detail/sum_service__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "dis_tutorial1/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "dis_tutorial1/srv/detail/sum_service__struct.h"
#include "dis_tutorial1/srv/detail/sum_service__functions.h"
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

#include "rosidl_runtime_c/primitives_sequence.h"  // numbers
#include "rosidl_runtime_c/primitives_sequence_functions.h"  // numbers
#include "rosidl_runtime_c/string.h"  // request_text
#include "rosidl_runtime_c/string_functions.h"  // request_text

// forward declare type support functions


using _SumService_Request__ros_msg_type = dis_tutorial1__srv__SumService_Request;

static bool _SumService_Request__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _SumService_Request__ros_msg_type * ros_message = static_cast<const _SumService_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: request_text
  {
    const rosidl_runtime_c__String * str = &ros_message->request_text;
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

  // Field name: numbers
  {
    size_t size = ros_message->numbers.size;
    auto array_ptr = ros_message->numbers.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  return true;
}

static bool _SumService_Request__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _SumService_Request__ros_msg_type * ros_message = static_cast<_SumService_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: request_text
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->request_text.data) {
      rosidl_runtime_c__String__init(&ros_message->request_text);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->request_text,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'request_text'\n");
      return false;
    }
  }

  // Field name: numbers
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->numbers.data) {
      rosidl_runtime_c__int32__Sequence__fini(&ros_message->numbers);
    }
    if (!rosidl_runtime_c__int32__Sequence__init(&ros_message->numbers, size)) {
      fprintf(stderr, "failed to create array for field 'numbers'");
      return false;
    }
    auto array_ptr = ros_message->numbers.data;
    cdr.deserializeArray(array_ptr, size);
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_dis_tutorial1
size_t get_serialized_size_dis_tutorial1__srv__SumService_Request(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _SumService_Request__ros_msg_type * ros_message = static_cast<const _SumService_Request__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name request_text
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->request_text.size + 1);
  // field.name numbers
  {
    size_t array_size = ros_message->numbers.size;
    auto array_ptr = ros_message->numbers.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _SumService_Request__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_dis_tutorial1__srv__SumService_Request(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_dis_tutorial1
size_t max_serialized_size_dis_tutorial1__srv__SumService_Request(
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

  // member: request_text
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
  // member: numbers
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = dis_tutorial1__srv__SumService_Request;
    is_plain =
      (
      offsetof(DataType, numbers) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _SumService_Request__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_dis_tutorial1__srv__SumService_Request(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_SumService_Request = {
  "dis_tutorial1::srv",
  "SumService_Request",
  _SumService_Request__cdr_serialize,
  _SumService_Request__cdr_deserialize,
  _SumService_Request__get_serialized_size,
  _SumService_Request__max_serialized_size
};

static rosidl_message_type_support_t _SumService_Request__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_SumService_Request,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, dis_tutorial1, srv, SumService_Request)() {
  return &_SumService_Request__type_support;
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
// #include "dis_tutorial1/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
// already included above
// #include "dis_tutorial1/srv/detail/sum_service__struct.h"
// already included above
// #include "dis_tutorial1/srv/detail/sum_service__functions.h"
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
// #include "rosidl_runtime_c/string.h"  // response_text
// already included above
// #include "rosidl_runtime_c/string_functions.h"  // response_text

// forward declare type support functions


using _SumService_Response__ros_msg_type = dis_tutorial1__srv__SumService_Response;

static bool _SumService_Response__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _SumService_Response__ros_msg_type * ros_message = static_cast<const _SumService_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: response_text
  {
    const rosidl_runtime_c__String * str = &ros_message->response_text;
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

  // Field name: sum
  {
    cdr << ros_message->sum;
  }

  return true;
}

static bool _SumService_Response__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _SumService_Response__ros_msg_type * ros_message = static_cast<_SumService_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: response_text
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->response_text.data) {
      rosidl_runtime_c__String__init(&ros_message->response_text);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->response_text,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'response_text'\n");
      return false;
    }
  }

  // Field name: sum
  {
    cdr >> ros_message->sum;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_dis_tutorial1
size_t get_serialized_size_dis_tutorial1__srv__SumService_Response(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _SumService_Response__ros_msg_type * ros_message = static_cast<const _SumService_Response__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name response_text
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->response_text.size + 1);
  // field.name sum
  {
    size_t item_size = sizeof(ros_message->sum);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _SumService_Response__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_dis_tutorial1__srv__SumService_Response(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_dis_tutorial1
size_t max_serialized_size_dis_tutorial1__srv__SumService_Response(
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

  // member: response_text
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
  // member: sum
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = dis_tutorial1__srv__SumService_Response;
    is_plain =
      (
      offsetof(DataType, sum) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _SumService_Response__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_dis_tutorial1__srv__SumService_Response(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_SumService_Response = {
  "dis_tutorial1::srv",
  "SumService_Response",
  _SumService_Response__cdr_serialize,
  _SumService_Response__cdr_deserialize,
  _SumService_Response__get_serialized_size,
  _SumService_Response__max_serialized_size
};

static rosidl_message_type_support_t _SumService_Response__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_SumService_Response,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, dis_tutorial1, srv, SumService_Response)() {
  return &_SumService_Response__type_support;
}

#if defined(__cplusplus)
}
#endif

#include "rosidl_typesupport_fastrtps_cpp/service_type_support.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_c/identifier.h"
// already included above
// #include "dis_tutorial1/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "dis_tutorial1/srv/sum_service.h"

#if defined(__cplusplus)
extern "C"
{
#endif

static service_type_support_callbacks_t SumService__callbacks = {
  "dis_tutorial1::srv",
  "SumService",
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, dis_tutorial1, srv, SumService_Request)(),
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, dis_tutorial1, srv, SumService_Response)(),
};

static rosidl_service_type_support_t SumService__handle = {
  rosidl_typesupport_fastrtps_c__identifier,
  &SumService__callbacks,
  get_service_typesupport_handle_function,
};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, dis_tutorial1, srv, SumService)() {
  return &SumService__handle;
}

#if defined(__cplusplus)
}
#endif
