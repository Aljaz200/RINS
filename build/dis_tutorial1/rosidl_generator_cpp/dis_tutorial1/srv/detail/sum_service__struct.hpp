// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from dis_tutorial1:srv/SumService.idl
// generated code does not contain a copyright notice

#ifndef DIS_TUTORIAL1__SRV__DETAIL__SUM_SERVICE__STRUCT_HPP_
#define DIS_TUTORIAL1__SRV__DETAIL__SUM_SERVICE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__dis_tutorial1__srv__SumService_Request __attribute__((deprecated))
#else
# define DEPRECATED__dis_tutorial1__srv__SumService_Request __declspec(deprecated)
#endif

namespace dis_tutorial1
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SumService_Request_
{
  using Type = SumService_Request_<ContainerAllocator>;

  explicit SumService_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->request_text = "";
    }
  }

  explicit SumService_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : request_text(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->request_text = "";
    }
  }

  // field types and members
  using _request_text_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _request_text_type request_text;
  using _numbers_type =
    std::vector<int32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int32_t>>;
  _numbers_type numbers;

  // setters for named parameter idiom
  Type & set__request_text(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->request_text = _arg;
    return *this;
  }
  Type & set__numbers(
    const std::vector<int32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int32_t>> & _arg)
  {
    this->numbers = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    dis_tutorial1::srv::SumService_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const dis_tutorial1::srv::SumService_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<dis_tutorial1::srv::SumService_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<dis_tutorial1::srv::SumService_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      dis_tutorial1::srv::SumService_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<dis_tutorial1::srv::SumService_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      dis_tutorial1::srv::SumService_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<dis_tutorial1::srv::SumService_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<dis_tutorial1::srv::SumService_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<dis_tutorial1::srv::SumService_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__dis_tutorial1__srv__SumService_Request
    std::shared_ptr<dis_tutorial1::srv::SumService_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__dis_tutorial1__srv__SumService_Request
    std::shared_ptr<dis_tutorial1::srv::SumService_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SumService_Request_ & other) const
  {
    if (this->request_text != other.request_text) {
      return false;
    }
    if (this->numbers != other.numbers) {
      return false;
    }
    return true;
  }
  bool operator!=(const SumService_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SumService_Request_

// alias to use template instance with default allocator
using SumService_Request =
  dis_tutorial1::srv::SumService_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace dis_tutorial1


#ifndef _WIN32
# define DEPRECATED__dis_tutorial1__srv__SumService_Response __attribute__((deprecated))
#else
# define DEPRECATED__dis_tutorial1__srv__SumService_Response __declspec(deprecated)
#endif

namespace dis_tutorial1
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SumService_Response_
{
  using Type = SumService_Response_<ContainerAllocator>;

  explicit SumService_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->response_text = "";
      this->sum = 0l;
    }
  }

  explicit SumService_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : response_text(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->response_text = "";
      this->sum = 0l;
    }
  }

  // field types and members
  using _response_text_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _response_text_type response_text;
  using _sum_type =
    int32_t;
  _sum_type sum;

  // setters for named parameter idiom
  Type & set__response_text(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->response_text = _arg;
    return *this;
  }
  Type & set__sum(
    const int32_t & _arg)
  {
    this->sum = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    dis_tutorial1::srv::SumService_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const dis_tutorial1::srv::SumService_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<dis_tutorial1::srv::SumService_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<dis_tutorial1::srv::SumService_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      dis_tutorial1::srv::SumService_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<dis_tutorial1::srv::SumService_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      dis_tutorial1::srv::SumService_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<dis_tutorial1::srv::SumService_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<dis_tutorial1::srv::SumService_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<dis_tutorial1::srv::SumService_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__dis_tutorial1__srv__SumService_Response
    std::shared_ptr<dis_tutorial1::srv::SumService_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__dis_tutorial1__srv__SumService_Response
    std::shared_ptr<dis_tutorial1::srv::SumService_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SumService_Response_ & other) const
  {
    if (this->response_text != other.response_text) {
      return false;
    }
    if (this->sum != other.sum) {
      return false;
    }
    return true;
  }
  bool operator!=(const SumService_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SumService_Response_

// alias to use template instance with default allocator
using SumService_Response =
  dis_tutorial1::srv::SumService_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace dis_tutorial1

namespace dis_tutorial1
{

namespace srv
{

struct SumService
{
  using Request = dis_tutorial1::srv::SumService_Request;
  using Response = dis_tutorial1::srv::SumService_Response;
};

}  // namespace srv

}  // namespace dis_tutorial1

#endif  // DIS_TUTORIAL1__SRV__DETAIL__SUM_SERVICE__STRUCT_HPP_
