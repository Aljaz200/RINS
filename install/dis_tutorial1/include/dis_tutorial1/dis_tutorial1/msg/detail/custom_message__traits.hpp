// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from dis_tutorial1:msg/CustomMessage.idl
// generated code does not contain a copyright notice

#ifndef DIS_TUTORIAL1__MSG__DETAIL__CUSTOM_MESSAGE__TRAITS_HPP_
#define DIS_TUTORIAL1__MSG__DETAIL__CUSTOM_MESSAGE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "dis_tutorial1/msg/detail/custom_message__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace dis_tutorial1
{

namespace msg
{

inline void to_flow_style_yaml(
  const CustomMessage & msg,
  std::ostream & out)
{
  out << "{";
  // member: content
  {
    out << "content: ";
    rosidl_generator_traits::value_to_yaml(msg.content, out);
    out << ", ";
  }

  // member: id
  {
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const CustomMessage & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: content
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "content: ";
    rosidl_generator_traits::value_to_yaml(msg.content, out);
    out << "\n";
  }

  // member: id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const CustomMessage & msg, bool use_flow_style = false)
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
  const dis_tutorial1::msg::CustomMessage & msg,
  std::ostream & out, size_t indentation = 0)
{
  dis_tutorial1::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use dis_tutorial1::msg::to_yaml() instead")]]
inline std::string to_yaml(const dis_tutorial1::msg::CustomMessage & msg)
{
  return dis_tutorial1::msg::to_yaml(msg);
}

template<>
inline const char * data_type<dis_tutorial1::msg::CustomMessage>()
{
  return "dis_tutorial1::msg::CustomMessage";
}

template<>
inline const char * name<dis_tutorial1::msg::CustomMessage>()
{
  return "dis_tutorial1/msg/CustomMessage";
}

template<>
struct has_fixed_size<dis_tutorial1::msg::CustomMessage>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<dis_tutorial1::msg::CustomMessage>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<dis_tutorial1::msg::CustomMessage>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // DIS_TUTORIAL1__MSG__DETAIL__CUSTOM_MESSAGE__TRAITS_HPP_
