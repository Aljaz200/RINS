// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from hwpub:msg/Hwmsg.idl
// generated code does not contain a copyright notice

#ifndef HWPUB__MSG__DETAIL__HWMSG__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define HWPUB__MSG__DETAIL__HWMSG__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "hwpub/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "hwpub/msg/detail/hwmsg__struct.hpp"

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

#include "fastcdr/Cdr.h"

namespace hwpub
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_hwpub
cdr_serialize(
  const hwpub::msg::Hwmsg & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_hwpub
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  hwpub::msg::Hwmsg & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_hwpub
get_serialized_size(
  const hwpub::msg::Hwmsg & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_hwpub
max_serialized_size_Hwmsg(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace hwpub

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_hwpub
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, hwpub, msg, Hwmsg)();

#ifdef __cplusplus
}
#endif

#endif  // HWPUB__MSG__DETAIL__HWMSG__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
