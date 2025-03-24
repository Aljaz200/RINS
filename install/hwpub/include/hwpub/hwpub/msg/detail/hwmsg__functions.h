// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from hwpub:msg/Hwmsg.idl
// generated code does not contain a copyright notice

#ifndef HWPUB__MSG__DETAIL__HWMSG__FUNCTIONS_H_
#define HWPUB__MSG__DETAIL__HWMSG__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "hwpub/msg/rosidl_generator_c__visibility_control.h"

#include "hwpub/msg/detail/hwmsg__struct.h"

/// Initialize msg/Hwmsg message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * hwpub__msg__Hwmsg
 * )) before or use
 * hwpub__msg__Hwmsg__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_hwpub
bool
hwpub__msg__Hwmsg__init(hwpub__msg__Hwmsg * msg);

/// Finalize msg/Hwmsg message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_hwpub
void
hwpub__msg__Hwmsg__fini(hwpub__msg__Hwmsg * msg);

/// Create msg/Hwmsg message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * hwpub__msg__Hwmsg__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_hwpub
hwpub__msg__Hwmsg *
hwpub__msg__Hwmsg__create();

/// Destroy msg/Hwmsg message.
/**
 * It calls
 * hwpub__msg__Hwmsg__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_hwpub
void
hwpub__msg__Hwmsg__destroy(hwpub__msg__Hwmsg * msg);

/// Check for msg/Hwmsg message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_hwpub
bool
hwpub__msg__Hwmsg__are_equal(const hwpub__msg__Hwmsg * lhs, const hwpub__msg__Hwmsg * rhs);

/// Copy a msg/Hwmsg message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_hwpub
bool
hwpub__msg__Hwmsg__copy(
  const hwpub__msg__Hwmsg * input,
  hwpub__msg__Hwmsg * output);

/// Initialize array of msg/Hwmsg messages.
/**
 * It allocates the memory for the number of elements and calls
 * hwpub__msg__Hwmsg__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_hwpub
bool
hwpub__msg__Hwmsg__Sequence__init(hwpub__msg__Hwmsg__Sequence * array, size_t size);

/// Finalize array of msg/Hwmsg messages.
/**
 * It calls
 * hwpub__msg__Hwmsg__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_hwpub
void
hwpub__msg__Hwmsg__Sequence__fini(hwpub__msg__Hwmsg__Sequence * array);

/// Create array of msg/Hwmsg messages.
/**
 * It allocates the memory for the array and calls
 * hwpub__msg__Hwmsg__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_hwpub
hwpub__msg__Hwmsg__Sequence *
hwpub__msg__Hwmsg__Sequence__create(size_t size);

/// Destroy array of msg/Hwmsg messages.
/**
 * It calls
 * hwpub__msg__Hwmsg__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_hwpub
void
hwpub__msg__Hwmsg__Sequence__destroy(hwpub__msg__Hwmsg__Sequence * array);

/// Check for msg/Hwmsg message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_hwpub
bool
hwpub__msg__Hwmsg__Sequence__are_equal(const hwpub__msg__Hwmsg__Sequence * lhs, const hwpub__msg__Hwmsg__Sequence * rhs);

/// Copy an array of msg/Hwmsg messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_hwpub
bool
hwpub__msg__Hwmsg__Sequence__copy(
  const hwpub__msg__Hwmsg__Sequence * input,
  hwpub__msg__Hwmsg__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // HWPUB__MSG__DETAIL__HWMSG__FUNCTIONS_H_
