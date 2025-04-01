// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from hwpub:srv/Customserv.idl
// generated code does not contain a copyright notice

#ifndef HWPUB__SRV__DETAIL__CUSTOMSERV__TRAITS_HPP_
#define HWPUB__SRV__DETAIL__CUSTOMSERV__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "hwpub/srv/detail/customserv__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace hwpub
{

namespace srv
{

inline void to_flow_style_yaml(
  const Customserv_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: s
  {
    out << "s: ";
    rosidl_generator_traits::value_to_yaml(msg.s, out);
    out << ", ";
  }

  // member: time
  {
    out << "time: ";
    rosidl_generator_traits::value_to_yaml(msg.time, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Customserv_Request & msg,
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

  // member: time
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "time: ";
    rosidl_generator_traits::value_to_yaml(msg.time, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Customserv_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace hwpub

namespace rosidl_generator_traits
{

[[deprecated("use hwpub::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const hwpub::srv::Customserv_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  hwpub::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use hwpub::srv::to_yaml() instead")]]
inline std::string to_yaml(const hwpub::srv::Customserv_Request & msg)
{
  return hwpub::srv::to_yaml(msg);
}

template<>
inline const char * data_type<hwpub::srv::Customserv_Request>()
{
  return "hwpub::srv::Customserv_Request";
}

template<>
inline const char * name<hwpub::srv::Customserv_Request>()
{
  return "hwpub/srv/Customserv_Request";
}

template<>
struct has_fixed_size<hwpub::srv::Customserv_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<hwpub::srv::Customserv_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<hwpub::srv::Customserv_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace hwpub
{

namespace srv
{

inline void to_flow_style_yaml(
  const Customserv_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: st
  {
    out << "st: ";
    rosidl_generator_traits::value_to_yaml(msg.st, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Customserv_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: st
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "st: ";
    rosidl_generator_traits::value_to_yaml(msg.st, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Customserv_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace hwpub

namespace rosidl_generator_traits
{

[[deprecated("use hwpub::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const hwpub::srv::Customserv_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  hwpub::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use hwpub::srv::to_yaml() instead")]]
inline std::string to_yaml(const hwpub::srv::Customserv_Response & msg)
{
  return hwpub::srv::to_yaml(msg);
}

template<>
inline const char * data_type<hwpub::srv::Customserv_Response>()
{
  return "hwpub::srv::Customserv_Response";
}

template<>
inline const char * name<hwpub::srv::Customserv_Response>()
{
  return "hwpub/srv/Customserv_Response";
}

template<>
struct has_fixed_size<hwpub::srv::Customserv_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<hwpub::srv::Customserv_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<hwpub::srv::Customserv_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<hwpub::srv::Customserv>()
{
  return "hwpub::srv::Customserv";
}

template<>
inline const char * name<hwpub::srv::Customserv>()
{
  return "hwpub/srv/Customserv";
}

template<>
struct has_fixed_size<hwpub::srv::Customserv>
  : std::integral_constant<
    bool,
    has_fixed_size<hwpub::srv::Customserv_Request>::value &&
    has_fixed_size<hwpub::srv::Customserv_Response>::value
  >
{
};

template<>
struct has_bounded_size<hwpub::srv::Customserv>
  : std::integral_constant<
    bool,
    has_bounded_size<hwpub::srv::Customserv_Request>::value &&
    has_bounded_size<hwpub::srv::Customserv_Response>::value
  >
{
};

template<>
struct is_service<hwpub::srv::Customserv>
  : std::true_type
{
};

template<>
struct is_service_request<hwpub::srv::Customserv_Request>
  : std::true_type
{
};

template<>
struct is_service_response<hwpub::srv::Customserv_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // HWPUB__SRV__DETAIL__CUSTOMSERV__TRAITS_HPP_
