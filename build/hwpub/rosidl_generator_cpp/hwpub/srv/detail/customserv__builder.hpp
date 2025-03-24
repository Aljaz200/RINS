// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from hwpub:srv/Customserv.idl
// generated code does not contain a copyright notice

#ifndef HWPUB__SRV__DETAIL__CUSTOMSERV__BUILDER_HPP_
#define HWPUB__SRV__DETAIL__CUSTOMSERV__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "hwpub/srv/detail/customserv__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace hwpub
{

namespace srv
{

namespace builder
{

class Init_Customserv_Request_time
{
public:
  explicit Init_Customserv_Request_time(::hwpub::srv::Customserv_Request & msg)
  : msg_(msg)
  {}
  ::hwpub::srv::Customserv_Request time(::hwpub::srv::Customserv_Request::_time_type arg)
  {
    msg_.time = std::move(arg);
    return std::move(msg_);
  }

private:
  ::hwpub::srv::Customserv_Request msg_;
};

class Init_Customserv_Request_s
{
public:
  Init_Customserv_Request_s()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Customserv_Request_time s(::hwpub::srv::Customserv_Request::_s_type arg)
  {
    msg_.s = std::move(arg);
    return Init_Customserv_Request_time(msg_);
  }

private:
  ::hwpub::srv::Customserv_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::hwpub::srv::Customserv_Request>()
{
  return hwpub::srv::builder::Init_Customserv_Request_s();
}

}  // namespace hwpub


namespace hwpub
{

namespace srv
{

namespace builder
{

class Init_Customserv_Response_st
{
public:
  Init_Customserv_Response_st()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::hwpub::srv::Customserv_Response st(::hwpub::srv::Customserv_Response::_st_type arg)
  {
    msg_.st = std::move(arg);
    return std::move(msg_);
  }

private:
  ::hwpub::srv::Customserv_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::hwpub::srv::Customserv_Response>()
{
  return hwpub::srv::builder::Init_Customserv_Response_st();
}

}  // namespace hwpub

#endif  // HWPUB__SRV__DETAIL__CUSTOMSERV__BUILDER_HPP_
