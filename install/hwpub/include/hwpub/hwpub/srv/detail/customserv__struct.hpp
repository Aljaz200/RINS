// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from hwpub:srv/Customserv.idl
// generated code does not contain a copyright notice

#ifndef HWPUB__SRV__DETAIL__CUSTOMSERV__STRUCT_HPP_
#define HWPUB__SRV__DETAIL__CUSTOMSERV__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__hwpub__srv__Customserv_Request __attribute__((deprecated))
#else
# define DEPRECATED__hwpub__srv__Customserv_Request __declspec(deprecated)
#endif

namespace hwpub
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct Customserv_Request_
{
  using Type = Customserv_Request_<ContainerAllocator>;

  explicit Customserv_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->s = "";
      this->time = 0ll;
    }
  }

  explicit Customserv_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : s(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->s = "";
      this->time = 0ll;
    }
  }

  // field types and members
  using _s_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _s_type s;
  using _time_type =
    int64_t;
  _time_type time;

  // setters for named parameter idiom
  Type & set__s(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->s = _arg;
    return *this;
  }
  Type & set__time(
    const int64_t & _arg)
  {
    this->time = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    hwpub::srv::Customserv_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const hwpub::srv::Customserv_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<hwpub::srv::Customserv_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<hwpub::srv::Customserv_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      hwpub::srv::Customserv_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<hwpub::srv::Customserv_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      hwpub::srv::Customserv_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<hwpub::srv::Customserv_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<hwpub::srv::Customserv_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<hwpub::srv::Customserv_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__hwpub__srv__Customserv_Request
    std::shared_ptr<hwpub::srv::Customserv_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__hwpub__srv__Customserv_Request
    std::shared_ptr<hwpub::srv::Customserv_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Customserv_Request_ & other) const
  {
    if (this->s != other.s) {
      return false;
    }
    if (this->time != other.time) {
      return false;
    }
    return true;
  }
  bool operator!=(const Customserv_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Customserv_Request_

// alias to use template instance with default allocator
using Customserv_Request =
  hwpub::srv::Customserv_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace hwpub


#ifndef _WIN32
# define DEPRECATED__hwpub__srv__Customserv_Response __attribute__((deprecated))
#else
# define DEPRECATED__hwpub__srv__Customserv_Response __declspec(deprecated)
#endif

namespace hwpub
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct Customserv_Response_
{
  using Type = Customserv_Response_<ContainerAllocator>;

  explicit Customserv_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->st = "";
    }
  }

  explicit Customserv_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : st(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->st = "";
    }
  }

  // field types and members
  using _st_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _st_type st;

  // setters for named parameter idiom
  Type & set__st(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->st = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    hwpub::srv::Customserv_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const hwpub::srv::Customserv_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<hwpub::srv::Customserv_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<hwpub::srv::Customserv_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      hwpub::srv::Customserv_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<hwpub::srv::Customserv_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      hwpub::srv::Customserv_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<hwpub::srv::Customserv_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<hwpub::srv::Customserv_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<hwpub::srv::Customserv_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__hwpub__srv__Customserv_Response
    std::shared_ptr<hwpub::srv::Customserv_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__hwpub__srv__Customserv_Response
    std::shared_ptr<hwpub::srv::Customserv_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Customserv_Response_ & other) const
  {
    if (this->st != other.st) {
      return false;
    }
    return true;
  }
  bool operator!=(const Customserv_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Customserv_Response_

// alias to use template instance with default allocator
using Customserv_Response =
  hwpub::srv::Customserv_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace hwpub

namespace hwpub
{

namespace srv
{

struct Customserv
{
  using Request = hwpub::srv::Customserv_Request;
  using Response = hwpub::srv::Customserv_Response;
};

}  // namespace srv

}  // namespace hwpub

#endif  // HWPUB__SRV__DETAIL__CUSTOMSERV__STRUCT_HPP_
