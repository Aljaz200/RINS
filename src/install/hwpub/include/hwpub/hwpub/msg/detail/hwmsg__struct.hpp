// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from hwpub:msg/Hwmsg.idl
// generated code does not contain a copyright notice

#ifndef HWPUB__MSG__DETAIL__HWMSG__STRUCT_HPP_
#define HWPUB__MSG__DETAIL__HWMSG__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__hwpub__msg__Hwmsg __attribute__((deprecated))
#else
# define DEPRECATED__hwpub__msg__Hwmsg __declspec(deprecated)
#endif

namespace hwpub
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Hwmsg_
{
  using Type = Hwmsg_<ContainerAllocator>;

  explicit Hwmsg_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->s = "";
      this->num = 0ll;
      this->b = false;
    }
  }

  explicit Hwmsg_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : s(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->s = "";
      this->num = 0ll;
      this->b = false;
    }
  }

  // field types and members
  using _s_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _s_type s;
  using _num_type =
    int64_t;
  _num_type num;
  using _b_type =
    bool;
  _b_type b;

  // setters for named parameter idiom
  Type & set__s(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->s = _arg;
    return *this;
  }
  Type & set__num(
    const int64_t & _arg)
  {
    this->num = _arg;
    return *this;
  }
  Type & set__b(
    const bool & _arg)
  {
    this->b = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    hwpub::msg::Hwmsg_<ContainerAllocator> *;
  using ConstRawPtr =
    const hwpub::msg::Hwmsg_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<hwpub::msg::Hwmsg_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<hwpub::msg::Hwmsg_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      hwpub::msg::Hwmsg_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<hwpub::msg::Hwmsg_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      hwpub::msg::Hwmsg_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<hwpub::msg::Hwmsg_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<hwpub::msg::Hwmsg_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<hwpub::msg::Hwmsg_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__hwpub__msg__Hwmsg
    std::shared_ptr<hwpub::msg::Hwmsg_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__hwpub__msg__Hwmsg
    std::shared_ptr<hwpub::msg::Hwmsg_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Hwmsg_ & other) const
  {
    if (this->s != other.s) {
      return false;
    }
    if (this->num != other.num) {
      return false;
    }
    if (this->b != other.b) {
      return false;
    }
    return true;
  }
  bool operator!=(const Hwmsg_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Hwmsg_

// alias to use template instance with default allocator
using Hwmsg =
  hwpub::msg::Hwmsg_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace hwpub

#endif  // HWPUB__MSG__DETAIL__HWMSG__STRUCT_HPP_
