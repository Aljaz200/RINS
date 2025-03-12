// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from hwpub:msg/Hwmsg.idl
// generated code does not contain a copyright notice

#ifndef HWPUB__MSG__DETAIL__HWMSG__TRAITS_HPP_
#define HWPUB__MSG__DETAIL__HWMSG__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "hwpub/msg/detail/hwmsg__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace hwpub
{

namespace msg
{

inline void to_flow_style_yaml(
  const Hwmsg & msg,
  std::ostream & out)
{
  out << "{";
  // member: s
  {
    out << "s: ";
    rosidl_generator_traits::value_to_yaml(msg.s, out);
    out << ", ";
  }

  // member: num
  {
    out << "num: ";
    rosidl_generator_traits::value_to_yaml(msg.num, out);
    out << ", ";
  }

  // member: b
  {
    out << "b: ";
    rosidl_generator_traits::value_to_yaml(msg.b, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Hwmsg & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: s
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "s: ";
    rosidl_generator_traits::value_to_yaml(msg.s, out);
    out << "\n";
  }

  // member: num
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "num: ";
    rosidl_generator_traits::value_to_yaml(msg.num, out);
    out << "\n";
  }

  // member: b
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "b: ";
    rosidl_generator_traits::value_to_yaml(msg.b, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Hwmsg & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace hwpub

namespace rosidl_generator_traits
{

[[deprecated("use hwpub::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const hwpub::msg::Hwmsg & msg,
  std::ostream & out, size_t indentation = 0)
{
  hwpub::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use hwpub::msg::to_yaml() instead")]]
inline std::string to_yaml(const hwpub::msg::Hwmsg & msg)
{
  return hwpub::msg::to_yaml(msg);
}

template<>
inline const char * data_type<hwpub::msg::Hwmsg>()
{
  return "hwpub::msg::Hwmsg";
}

template<>
inline const char * name<hwpub::msg::Hwmsg>()
{
  return "hwpub/msg/Hwmsg";
}

template<>
struct has_fixed_size<hwpub::msg::Hwmsg>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<hwpub::msg::Hwmsg>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<hwpub::msg::Hwmsg>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // HWPUB__MSG__DETAIL__HWMSG__TRAITS_HPP_
