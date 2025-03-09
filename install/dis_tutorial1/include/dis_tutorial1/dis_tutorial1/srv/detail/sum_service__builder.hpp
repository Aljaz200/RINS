// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from dis_tutorial1:srv/SumService.idl
// generated code does not contain a copyright notice

#ifndef DIS_TUTORIAL1__SRV__DETAIL__SUM_SERVICE__BUILDER_HPP_
#define DIS_TUTORIAL1__SRV__DETAIL__SUM_SERVICE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "dis_tutorial1/srv/detail/sum_service__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace dis_tutorial1
{

namespace srv
{

namespace builder
{

class Init_SumService_Request_numbers
{
public:
  explicit Init_SumService_Request_numbers(::dis_tutorial1::srv::SumService_Request & msg)
  : msg_(msg)
  {}
  ::dis_tutorial1::srv::SumService_Request numbers(::dis_tutorial1::srv::SumService_Request::_numbers_type arg)
  {
    msg_.numbers = std::move(arg);
    return std::move(msg_);
  }

private:
  ::dis_tutorial1::srv::SumService_Request msg_;
};

class Init_SumService_Request_request_text
{
public:
  Init_SumService_Request_request_text()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SumService_Request_numbers request_text(::dis_tutorial1::srv::SumService_Request::_request_text_type arg)
  {
    msg_.request_text = std::move(arg);
    return Init_SumService_Request_numbers(msg_);
  }

private:
  ::dis_tutorial1::srv::SumService_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::dis_tutorial1::srv::SumService_Request>()
{
  return dis_tutorial1::srv::builder::Init_SumService_Request_request_text();
}

}  // namespace dis_tutorial1


namespace dis_tutorial1
{

namespace srv
{

namespace builder
{

class Init_SumService_Response_sum
{
public:
  explicit Init_SumService_Response_sum(::dis_tutorial1::srv::SumService_Response & msg)
  : msg_(msg)
  {}
  ::dis_tutorial1::srv::SumService_Response sum(::dis_tutorial1::srv::SumService_Response::_sum_type arg)
  {
    msg_.sum = std::move(arg);
    return std::move(msg_);
  }

private:
  ::dis_tutorial1::srv::SumService_Response msg_;
};

class Init_SumService_Response_response_text
{
public:
  Init_SumService_Response_response_text()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SumService_Response_sum response_text(::dis_tutorial1::srv::SumService_Response::_response_text_type arg)
  {
    msg_.response_text = std::move(arg);
    return Init_SumService_Response_sum(msg_);
  }

private:
  ::dis_tutorial1::srv::SumService_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::dis_tutorial1::srv::SumService_Response>()
{
  return dis_tutorial1::srv::builder::Init_SumService_Response_response_text();
}

}  // namespace dis_tutorial1

#endif  // DIS_TUTORIAL1__SRV__DETAIL__SUM_SERVICE__BUILDER_HPP_
