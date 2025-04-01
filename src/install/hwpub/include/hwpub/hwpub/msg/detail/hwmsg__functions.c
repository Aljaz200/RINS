// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from hwpub:msg/Hwmsg.idl
// generated code does not contain a copyright notice
#include "hwpub/msg/detail/hwmsg__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `s`
#include "rosidl_runtime_c/string_functions.h"

bool
hwpub__msg__Hwmsg__init(hwpub__msg__Hwmsg * msg)
{
  if (!msg) {
    return false;
  }
  // s
  if (!rosidl_runtime_c__String__init(&msg->s)) {
    hwpub__msg__Hwmsg__fini(msg);
    return false;
  }
  // num
  // b
  return true;
}

void
hwpub__msg__Hwmsg__fini(hwpub__msg__Hwmsg * msg)
{
  if (!msg) {
    return;
  }
  // s
  rosidl_runtime_c__String__fini(&msg->s);
  // num
  // b
}

bool
hwpub__msg__Hwmsg__are_equal(const hwpub__msg__Hwmsg * lhs, const hwpub__msg__Hwmsg * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // s
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->s), &(rhs->s)))
  {
    return false;
  }
  // num
  if (lhs->num != rhs->num) {
    return false;
  }
  // b
  if (lhs->b != rhs->b) {
    return false;
  }
  return true;
}

bool
hwpub__msg__Hwmsg__copy(
  const hwpub__msg__Hwmsg * input,
  hwpub__msg__Hwmsg * output)
{
  if (!input || !output) {
    return false;
  }
  // s
  if (!rosidl_runtime_c__String__copy(
      &(input->s), &(output->s)))
  {
    return false;
  }
  // num
  output->num = input->num;
  // b
  output->b = input->b;
  return true;
}

hwpub__msg__Hwmsg *
hwpub__msg__Hwmsg__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hwpub__msg__Hwmsg * msg = (hwpub__msg__Hwmsg *)allocator.allocate(sizeof(hwpub__msg__Hwmsg), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(hwpub__msg__Hwmsg));
  bool success = hwpub__msg__Hwmsg__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
hwpub__msg__Hwmsg__destroy(hwpub__msg__Hwmsg * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    hwpub__msg__Hwmsg__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
hwpub__msg__Hwmsg__Sequence__init(hwpub__msg__Hwmsg__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hwpub__msg__Hwmsg * data = NULL;

  if (size) {
    data = (hwpub__msg__Hwmsg *)allocator.zero_allocate(size, sizeof(hwpub__msg__Hwmsg), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = hwpub__msg__Hwmsg__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        hwpub__msg__Hwmsg__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
hwpub__msg__Hwmsg__Sequence__fini(hwpub__msg__Hwmsg__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      hwpub__msg__Hwmsg__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

hwpub__msg__Hwmsg__Sequence *
hwpub__msg__Hwmsg__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hwpub__msg__Hwmsg__Sequence * array = (hwpub__msg__Hwmsg__Sequence *)allocator.allocate(sizeof(hwpub__msg__Hwmsg__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = hwpub__msg__Hwmsg__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
hwpub__msg__Hwmsg__Sequence__destroy(hwpub__msg__Hwmsg__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    hwpub__msg__Hwmsg__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
hwpub__msg__Hwmsg__Sequence__are_equal(const hwpub__msg__Hwmsg__Sequence * lhs, const hwpub__msg__Hwmsg__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!hwpub__msg__Hwmsg__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
hwpub__msg__Hwmsg__Sequence__copy(
  const hwpub__msg__Hwmsg__Sequence * input,
  hwpub__msg__Hwmsg__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(hwpub__msg__Hwmsg);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    hwpub__msg__Hwmsg * data =
      (hwpub__msg__Hwmsg *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!hwpub__msg__Hwmsg__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          hwpub__msg__Hwmsg__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!hwpub__msg__Hwmsg__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
