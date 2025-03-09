// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from dis_tutorial1:srv/SumService.idl
// generated code does not contain a copyright notice

#ifndef DIS_TUTORIAL1__SRV__DETAIL__SUM_SERVICE__FUNCTIONS_H_
#define DIS_TUTORIAL1__SRV__DETAIL__SUM_SERVICE__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "dis_tutorial1/msg/rosidl_generator_c__visibility_control.h"

#include "dis_tutorial1/srv/detail/sum_service__struct.h"

/// Initialize srv/SumService message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * dis_tutorial1__srv__SumService_Request
 * )) before or use
 * dis_tutorial1__srv__SumService_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_dis_tutorial1
bool
dis_tutorial1__srv__SumService_Request__init(dis_tutorial1__srv__SumService_Request * msg);

/// Finalize srv/SumService message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_dis_tutorial1
void
dis_tutorial1__srv__SumService_Request__fini(dis_tutorial1__srv__SumService_Request * msg);

/// Create srv/SumService message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * dis_tutorial1__srv__SumService_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_dis_tutorial1
dis_tutorial1__srv__SumService_Request *
dis_tutorial1__srv__SumService_Request__create();

/// Destroy srv/SumService message.
/**
 * It calls
 * dis_tutorial1__srv__SumService_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_dis_tutorial1
void
dis_tutorial1__srv__SumService_Request__destroy(dis_tutorial1__srv__SumService_Request * msg);

/// Check for srv/SumService message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_dis_tutorial1
bool
dis_tutorial1__srv__SumService_Request__are_equal(const dis_tutorial1__srv__SumService_Request * lhs, const dis_tutorial1__srv__SumService_Request * rhs);

/// Copy a srv/SumService message.
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
ROSIDL_GENERATOR_C_PUBLIC_dis_tutorial1
bool
dis_tutorial1__srv__SumService_Request__copy(
  const dis_tutorial1__srv__SumService_Request * input,
  dis_tutorial1__srv__SumService_Request * output);

/// Initialize array of srv/SumService messages.
/**
 * It allocates the memory for the number of elements and calls
 * dis_tutorial1__srv__SumService_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_dis_tutorial1
bool
dis_tutorial1__srv__SumService_Request__Sequence__init(dis_tutorial1__srv__SumService_Request__Sequence * array, size_t size);

/// Finalize array of srv/SumService messages.
/**
 * It calls
 * dis_tutorial1__srv__SumService_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_dis_tutorial1
void
dis_tutorial1__srv__SumService_Request__Sequence__fini(dis_tutorial1__srv__SumService_Request__Sequence * array);

/// Create array of srv/SumService messages.
/**
 * It allocates the memory for the array and calls
 * dis_tutorial1__srv__SumService_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_dis_tutorial1
dis_tutorial1__srv__SumService_Request__Sequence *
dis_tutorial1__srv__SumService_Request__Sequence__create(size_t size);

/// Destroy array of srv/SumService messages.
/**
 * It calls
 * dis_tutorial1__srv__SumService_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_dis_tutorial1
void
dis_tutorial1__srv__SumService_Request__Sequence__destroy(dis_tutorial1__srv__SumService_Request__Sequence * array);

/// Check for srv/SumService message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_dis_tutorial1
bool
dis_tutorial1__srv__SumService_Request__Sequence__are_equal(const dis_tutorial1__srv__SumService_Request__Sequence * lhs, const dis_tutorial1__srv__SumService_Request__Sequence * rhs);

/// Copy an array of srv/SumService messages.
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
ROSIDL_GENERATOR_C_PUBLIC_dis_tutorial1
bool
dis_tutorial1__srv__SumService_Request__Sequence__copy(
  const dis_tutorial1__srv__SumService_Request__Sequence * input,
  dis_tutorial1__srv__SumService_Request__Sequence * output);

/// Initialize srv/SumService message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * dis_tutorial1__srv__SumService_Response
 * )) before or use
 * dis_tutorial1__srv__SumService_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_dis_tutorial1
bool
dis_tutorial1__srv__SumService_Response__init(dis_tutorial1__srv__SumService_Response * msg);

/// Finalize srv/SumService message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_dis_tutorial1
void
dis_tutorial1__srv__SumService_Response__fini(dis_tutorial1__srv__SumService_Response * msg);

/// Create srv/SumService message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * dis_tutorial1__srv__SumService_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_dis_tutorial1
dis_tutorial1__srv__SumService_Response *
dis_tutorial1__srv__SumService_Response__create();

/// Destroy srv/SumService message.
/**
 * It calls
 * dis_tutorial1__srv__SumService_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_dis_tutorial1
void
dis_tutorial1__srv__SumService_Response__destroy(dis_tutorial1__srv__SumService_Response * msg);

/// Check for srv/SumService message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_dis_tutorial1
bool
dis_tutorial1__srv__SumService_Response__are_equal(const dis_tutorial1__srv__SumService_Response * lhs, const dis_tutorial1__srv__SumService_Response * rhs);

/// Copy a srv/SumService message.
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
ROSIDL_GENERATOR_C_PUBLIC_dis_tutorial1
bool
dis_tutorial1__srv__SumService_Response__copy(
  const dis_tutorial1__srv__SumService_Response * input,
  dis_tutorial1__srv__SumService_Response * output);

/// Initialize array of srv/SumService messages.
/**
 * It allocates the memory for the number of elements and calls
 * dis_tutorial1__srv__SumService_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_dis_tutorial1
bool
dis_tutorial1__srv__SumService_Response__Sequence__init(dis_tutorial1__srv__SumService_Response__Sequence * array, size_t size);

/// Finalize array of srv/SumService messages.
/**
 * It calls
 * dis_tutorial1__srv__SumService_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_dis_tutorial1
void
dis_tutorial1__srv__SumService_Response__Sequence__fini(dis_tutorial1__srv__SumService_Response__Sequence * array);

/// Create array of srv/SumService messages.
/**
 * It allocates the memory for the array and calls
 * dis_tutorial1__srv__SumService_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_dis_tutorial1
dis_tutorial1__srv__SumService_Response__Sequence *
dis_tutorial1__srv__SumService_Response__Sequence__create(size_t size);

/// Destroy array of srv/SumService messages.
/**
 * It calls
 * dis_tutorial1__srv__SumService_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_dis_tutorial1
void
dis_tutorial1__srv__SumService_Response__Sequence__destroy(dis_tutorial1__srv__SumService_Response__Sequence * array);

/// Check for srv/SumService message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_dis_tutorial1
bool
dis_tutorial1__srv__SumService_Response__Sequence__are_equal(const dis_tutorial1__srv__SumService_Response__Sequence * lhs, const dis_tutorial1__srv__SumService_Response__Sequence * rhs);

/// Copy an array of srv/SumService messages.
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
ROSIDL_GENERATOR_C_PUBLIC_dis_tutorial1
bool
dis_tutorial1__srv__SumService_Response__Sequence__copy(
  const dis_tutorial1__srv__SumService_Response__Sequence * input,
  dis_tutorial1__srv__SumService_Response__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // DIS_TUTORIAL1__SRV__DETAIL__SUM_SERVICE__FUNCTIONS_H_
