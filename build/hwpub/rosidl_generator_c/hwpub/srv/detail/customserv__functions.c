// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from hwpub:srv/Customserv.idl
// generated code does not contain a copyright notice
#include "hwpub/srv/detail/customserv__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `s`
#include "rosidl_runtime_c/string_functions.h"

bool
hwpub__srv__Customserv_Request__init(hwpub__srv__Customserv_Request * msg)
{
  if (!msg) {
    return false;
  }
  // s
  if (!rosidl_runtime_c__String__init(&msg->s)) {
    hwpub__srv__Customserv_Request__fini(msg);
    return false;
  }
  // time
  return true;
}

void
hwpub__srv__Customserv_Request__fini(hwpub__srv__Customserv_Request * msg)
{
  if (!msg) {
    return;
  }
  // s
  rosidl_runtime_c__String__fini(&msg->s);
  // time
}

bool
hwpub__srv__Customserv_Request__are_equal(const hwpub__srv__Customserv_Request * lhs, const hwpub__srv__Customserv_Request * rhs)
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
  // time
  if (lhs->time != rhs->time) {
    return false;
  }
  return true;
}

bool
hwpub__srv__Customserv_Request__copy(
  const hwpub__srv__Customserv_Request * input,
  hwpub__srv__Customserv_Request * output)
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
  // time
  output->time = input->time;
  return true;
}

hwpub__srv__Customserv_Request *
hwpub__srv__Customserv_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hwpub__srv__Customserv_Request * msg = (hwpub__srv__Customserv_Request *)allocator.allocate(sizeof(hwpub__srv__Customserv_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(hwpub__srv__Customserv_Request));
  bool success = hwpub__srv__Customserv_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
hwpub__srv__Customserv_Request__destroy(hwpub__srv__Customserv_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    hwpub__srv__Customserv_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
hwpub__srv__Customserv_Request__Sequence__init(hwpub__srv__Customserv_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hwpub__srv__Customserv_Request * data = NULL;

  if (size) {
    data = (hwpub__srv__Customserv_Request *)allocator.zero_allocate(size, sizeof(hwpub__srv__Customserv_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = hwpub__srv__Customserv_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        hwpub__srv__Customserv_Request__fini(&data[i - 1]);
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
hwpub__srv__Customserv_Request__Sequence__fini(hwpub__srv__Customserv_Request__Sequence * array)
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
      hwpub__srv__Customserv_Request__fini(&array->data[i]);
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

hwpub__srv__Customserv_Request__Sequence *
hwpub__srv__Customserv_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hwpub__srv__Customserv_Request__Sequence * array = (hwpub__srv__Customserv_Request__Sequence *)allocator.allocate(sizeof(hwpub__srv__Customserv_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = hwpub__srv__Customserv_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
hwpub__srv__Customserv_Request__Sequence__destroy(hwpub__srv__Customserv_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    hwpub__srv__Customserv_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
hwpub__srv__Customserv_Request__Sequence__are_equal(const hwpub__srv__Customserv_Request__Sequence * lhs, const hwpub__srv__Customserv_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!hwpub__srv__Customserv_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
hwpub__srv__Customserv_Request__Sequence__copy(
  const hwpub__srv__Customserv_Request__Sequence * input,
  hwpub__srv__Customserv_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(hwpub__srv__Customserv_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    hwpub__srv__Customserv_Request * data =
      (hwpub__srv__Customserv_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!hwpub__srv__Customserv_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          hwpub__srv__Customserv_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!hwpub__srv__Customserv_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `st`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

bool
hwpub__srv__Customserv_Response__init(hwpub__srv__Customserv_Response * msg)
{
  if (!msg) {
    return false;
  }
  // st
  if (!rosidl_runtime_c__String__init(&msg->st)) {
    hwpub__srv__Customserv_Response__fini(msg);
    return false;
  }
  return true;
}

void
hwpub__srv__Customserv_Response__fini(hwpub__srv__Customserv_Response * msg)
{
  if (!msg) {
    return;
  }
  // st
  rosidl_runtime_c__String__fini(&msg->st);
}

bool
hwpub__srv__Customserv_Response__are_equal(const hwpub__srv__Customserv_Response * lhs, const hwpub__srv__Customserv_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // st
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->st), &(rhs->st)))
  {
    return false;
  }
  return true;
}

bool
hwpub__srv__Customserv_Response__copy(
  const hwpub__srv__Customserv_Response * input,
  hwpub__srv__Customserv_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // st
  if (!rosidl_runtime_c__String__copy(
      &(input->st), &(output->st)))
  {
    return false;
  }
  return true;
}

hwpub__srv__Customserv_Response *
hwpub__srv__Customserv_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hwpub__srv__Customserv_Response * msg = (hwpub__srv__Customserv_Response *)allocator.allocate(sizeof(hwpub__srv__Customserv_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(hwpub__srv__Customserv_Response));
  bool success = hwpub__srv__Customserv_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
hwpub__srv__Customserv_Response__destroy(hwpub__srv__Customserv_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    hwpub__srv__Customserv_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
hwpub__srv__Customserv_Response__Sequence__init(hwpub__srv__Customserv_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hwpub__srv__Customserv_Response * data = NULL;

  if (size) {
    data = (hwpub__srv__Customserv_Response *)allocator.zero_allocate(size, sizeof(hwpub__srv__Customserv_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = hwpub__srv__Customserv_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        hwpub__srv__Customserv_Response__fini(&data[i - 1]);
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
hwpub__srv__Customserv_Response__Sequence__fini(hwpub__srv__Customserv_Response__Sequence * array)
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
      hwpub__srv__Customserv_Response__fini(&array->data[i]);
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

hwpub__srv__Customserv_Response__Sequence *
hwpub__srv__Customserv_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hwpub__srv__Customserv_Response__Sequence * array = (hwpub__srv__Customserv_Response__Sequence *)allocator.allocate(sizeof(hwpub__srv__Customserv_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = hwpub__srv__Customserv_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
hwpub__srv__Customserv_Response__Sequence__destroy(hwpub__srv__Customserv_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    hwpub__srv__Customserv_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
hwpub__srv__Customserv_Response__Sequence__are_equal(const hwpub__srv__Customserv_Response__Sequence * lhs, const hwpub__srv__Customserv_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!hwpub__srv__Customserv_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
hwpub__srv__Customserv_Response__Sequence__copy(
  const hwpub__srv__Customserv_Response__Sequence * input,
  hwpub__srv__Customserv_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(hwpub__srv__Customserv_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    hwpub__srv__Customserv_Response * data =
      (hwpub__srv__Customserv_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!hwpub__srv__Customserv_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          hwpub__srv__Customserv_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!hwpub__srv__Customserv_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
