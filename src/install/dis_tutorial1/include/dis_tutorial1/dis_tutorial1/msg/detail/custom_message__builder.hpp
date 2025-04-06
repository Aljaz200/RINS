// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from dis_tutorial1:msg/CustomMessage.idl
// generated code does not contain a copyright notice

#ifndef DIS_TUTORIAL1__MSG__DETAIL__CUSTOM_MESSAGE__BUILDER_HPP_
#define DIS_TUTORIAL1__MSG__DETAIL__CUSTOM_MESSAGE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "dis_tutorial1/msg/detail/custom_message__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace dis_tutorial1
{

namespace msg
{

namespace builder
{

class Init_CustomMessage_id
{
public:
  explicit Init_CustomMessage_id(::dis_tutorial1::msg::CustomMessage & msg)
  : msg_(msg)
  {}
  ::dis_tutorial1::msg::CustomMessage id(::dis_tutorial1::msg::CustomMessage::_id_type arg)
  {
    msg_.id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::dis_tutorial1::msg::CustomMessage msg_;
};

class Init_CustomMessage_content
{
public:
  Init_CustomMessage_content()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CustomMessage_id content(::dis_tutorial1::msg::CustomMessage::_content_type arg)
  {
    msg_.content = std::move(arg);
    return Init_CustomMessage_id(msg_);
  }

private:
  ::dis_tutorial1::msg::CustomMessage msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::dis_tutorial1::msg::CustomMessage>()
{
  return dis_tutorial1::msg::builder::Init_CustomMessage_content();
}

}  // namespace dis_tutorial1

#endif  // DIS_TUTORIAL1__MSG__DETAIL__CUSTOM_MESSAGE__BUILDER_HPP_
