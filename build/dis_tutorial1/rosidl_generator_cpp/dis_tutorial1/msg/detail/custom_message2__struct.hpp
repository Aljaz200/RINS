// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from dis_tutorial1:msg/CustomMessage2.idl
// generated code does not contain a copyright notice

#ifndef DIS_TUTORIAL1__MSG__DETAIL__CUSTOM_MESSAGE2__STRUCT_HPP_
#define DIS_TUTORIAL1__MSG__DETAIL__CUSTOM_MESSAGE2__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__dis_tutorial1__msg__CustomMessage2 __attribute__((deprecated))
#else
# define DEPRECATED__dis_tutorial1__msg__CustomMessage2 __declspec(deprecated)
#endif

namespace dis_tutorial1
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct CustomMessage2_
{
  using Type = CustomMessage2_<ContainerAllocator>;

  explicit CustomMessage2_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->text = "";
      this->number = 0l;
      this->flag = false;
    }
  }

  explicit CustomMessage2_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : text(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->text = "";
      this->number = 0l;
      this->flag = false;
    }
  }

  // field types and members
  using _text_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _text_type text;
  using _number_type =
    int32_t;
  _number_type number;
  using _flag_type =
    bool;
  _flag_type flag;

  // setters for named parameter idiom
  Type & set__text(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->text = _arg;
    return *this;
  }
  Type & set__number(
    const int32_t & _arg)
  {
    this->number = _arg;
    return *this;
  }
  Type & set__flag(
    const bool & _arg)
  {
    this->flag = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    dis_tutorial1::msg::CustomMessage2_<ContainerAllocator> *;
  using ConstRawPtr =
    const dis_tutorial1::msg::CustomMessage2_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<dis_tutorial1::msg::CustomMessage2_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<dis_tutorial1::msg::CustomMessage2_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      dis_tutorial1::msg::CustomMessage2_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<dis_tutorial1::msg::CustomMessage2_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      dis_tutorial1::msg::CustomMessage2_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<dis_tutorial1::msg::CustomMessage2_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<dis_tutorial1::msg::CustomMessage2_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<dis_tutorial1::msg::CustomMessage2_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__dis_tutorial1__msg__CustomMessage2
    std::shared_ptr<dis_tutorial1::msg::CustomMessage2_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__dis_tutorial1__msg__CustomMessage2
    std::shared_ptr<dis_tutorial1::msg::CustomMessage2_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CustomMessage2_ & other) const
  {
    if (this->text != other.text) {
      return false;
    }
    if (this->number != other.number) {
      return false;
    }
    if (this->flag != other.flag) {
      return false;
    }
    return true;
  }
  bool operator!=(const CustomMessage2_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CustomMessage2_

// alias to use template instance with default allocator
using CustomMessage2 =
  dis_tutorial1::msg::CustomMessage2_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace dis_tutorial1

#endif  // DIS_TUTORIAL1__MSG__DETAIL__CUSTOM_MESSAGE2__STRUCT_HPP_
