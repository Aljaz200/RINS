// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from dis_tutorial1:msg/CustomMessage2.idl
// generated code does not contain a copyright notice

#ifndef DIS_TUTORIAL1__MSG__DETAIL__CUSTOM_MESSAGE2__TRAITS_HPP_
#define DIS_TUTORIAL1__MSG__DETAIL__CUSTOM_MESSAGE2__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "dis_tutorial1/msg/detail/custom_message2__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace dis_tutorial1
{

namespace msg
{

inline void to_flow_style_yaml(
  const CustomMessage2 & msg,
  std::ostream & out)
{
  out << "{";
  // member: text
  {
    out << "text: ";
    rosidl_generator_traits::value_to_yaml(msg.text, out);
    out << ", ";
  }

  // member: number
  {
    out << "number: ";
    rosidl_generator_traits::value_to_yaml(msg.number, out);
    out << ", ";
  }

  // member: flag
  {
    out << "flag: ";
    rosidl_generator_traits::value_to_yaml(msg.flag, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const CustomMessage2 & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: text
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "text: ";
    rosidl_generator_traits::value_to_yaml(msg.text, out);
    out << "\n";
  }

  // member: number
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "number: ";
    rosidl_generator_traits::value_to_yaml(msg.number, out);
    out << "\n";
  }

  // member: flag
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "flag: ";
    rosidl_generator_traits::value_to_yaml(msg.flag, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const CustomMessage2 & msg, bool use_flow_style = false)
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

}  // namespace dis_tutorial1

namespace rosidl_generator_traits
{

[[deprecated("use dis_tutorial1::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const dis_tutorial1::msg::CustomMessage2 & msg,
  std::ostream & out, size_t indentation = 0)
{
  dis_tutorial1::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use dis_tutorial1::msg::to_yaml() instead")]]
inline std::string to_yaml(const dis_tutorial1::msg::CustomMessage2 & msg)
{
  return dis_tutorial1::msg::to_yaml(msg);
}

template<>
inline const char * data_type<dis_tutorial1::msg::CustomMessage2>()
{
  return "dis_tutorial1::msg::CustomMessage2";
}

template<>
inline const char * name<dis_tutorial1::msg::CustomMessage2>()
{
  return "dis_tutorial1/msg/CustomMessage2";
}

template<>
struct has_fixed_size<dis_tutorial1::msg::CustomMessage2>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<dis_tutorial1::msg::CustomMessage2>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<dis_tutorial1::msg::CustomMessage2>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // DIS_TUTORIAL1__MSG__DETAIL__CUSTOM_MESSAGE2__TRAITS_HPP_
