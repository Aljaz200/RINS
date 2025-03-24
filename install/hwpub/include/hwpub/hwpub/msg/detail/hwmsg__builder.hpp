// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from hwpub:msg/Hwmsg.idl
// generated code does not contain a copyright notice

#ifndef HWPUB__MSG__DETAIL__HWMSG__BUILDER_HPP_
#define HWPUB__MSG__DETAIL__HWMSG__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "hwpub/msg/detail/hwmsg__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace hwpub
{

namespace msg
{

namespace builder
{

class Init_Hwmsg_b
{
public:
  explicit Init_Hwmsg_b(::hwpub::msg::Hwmsg & msg)
  : msg_(msg)
  {}
  ::hwpub::msg::Hwmsg b(::hwpub::msg::Hwmsg::_b_type arg)
  {
    msg_.b = std::move(arg);
    return std::move(msg_);
  }

private:
  ::hwpub::msg::Hwmsg msg_;
};

class Init_Hwmsg_num
{
public:
  explicit Init_Hwmsg_num(::hwpub::msg::Hwmsg & msg)
  : msg_(msg)
  {}
  Init_Hwmsg_b num(::hwpub::msg::Hwmsg::_num_type arg)
  {
    msg_.num = std::move(arg);
    return Init_Hwmsg_b(msg_);
  }

private:
  ::hwpub::msg::Hwmsg msg_;
};

class Init_Hwmsg_s
{
public:
  Init_Hwmsg_s()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Hwmsg_num s(::hwpub::msg::Hwmsg::_s_type arg)
  {
    msg_.s = std::move(arg);
    return Init_Hwmsg_num(msg_);
  }

private:
  ::hwpub::msg::Hwmsg msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::hwpub::msg::Hwmsg>()
{
  return hwpub::msg::builder::Init_Hwmsg_s();
}

}  // namespace hwpub

#endif  // HWPUB__MSG__DETAIL__HWMSG__BUILDER_HPP_
