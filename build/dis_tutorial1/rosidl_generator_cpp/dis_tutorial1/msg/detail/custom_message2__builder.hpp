// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from dis_tutorial1:msg/CustomMessage2.idl
// generated code does not contain a copyright notice

#ifndef DIS_TUTORIAL1__MSG__DETAIL__CUSTOM_MESSAGE2__BUILDER_HPP_
#define DIS_TUTORIAL1__MSG__DETAIL__CUSTOM_MESSAGE2__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "dis_tutorial1/msg/detail/custom_message2__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace dis_tutorial1
{

namespace msg
{

namespace builder
{

class Init_CustomMessage2_flag
{
public:
  explicit Init_CustomMessage2_flag(::dis_tutorial1::msg::CustomMessage2 & msg)
  : msg_(msg)
  {}
  ::dis_tutorial1::msg::CustomMessage2 flag(::dis_tutorial1::msg::CustomMessage2::_flag_type arg)
  {
    msg_.flag = std::move(arg);
    return std::move(msg_);
  }

private:
  ::dis_tutorial1::msg::CustomMessage2 msg_;
};

class Init_CustomMessage2_number
{
public:
  explicit Init_CustomMessage2_number(::dis_tutorial1::msg::CustomMessage2 & msg)
  : msg_(msg)
  {}
  Init_CustomMessage2_flag number(::dis_tutorial1::msg::CustomMessage2::_number_type arg)
  {
    msg_.number = std::move(arg);
    return Init_CustomMessage2_flag(msg_);
  }

private:
  ::dis_tutorial1::msg::CustomMessage2 msg_;
};

class Init_CustomMessage2_text
{
public:
  Init_CustomMessage2_text()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CustomMessage2_number text(::dis_tutorial1::msg::CustomMessage2::_text_type arg)
  {
    msg_.text = std::move(arg);
    return Init_CustomMessage2_number(msg_);
  }

private:
  ::dis_tutorial1::msg::CustomMessage2 msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::dis_tutorial1::msg::CustomMessage2>()
{
  return dis_tutorial1::msg::builder::Init_CustomMessage2_text();
}

}  // namespace dis_tutorial1

#endif  // DIS_TUTORIAL1__MSG__DETAIL__CUSTOM_MESSAGE2__BUILDER_HPP_
