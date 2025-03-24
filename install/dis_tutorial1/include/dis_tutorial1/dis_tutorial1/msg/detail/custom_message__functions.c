// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from dis_tutorial1:msg/CustomMessage.idl
// generated code does not contain a copyright notice
#include "dis_tutorial1/msg/detail/custom_message__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `content`
#include "rosidl_runtime_c/string_functions.h"

bool
dis_tutorial1__msg__CustomMessage__init(dis_tutorial1__msg__CustomMessage * msg)
{
  if (!msg) {
    return false;
  }
  // content
  if (!rosidl_runtime_c__String__init(&msg->content)) {
    dis_tutorial1__msg__CustomMessage__fini(msg);
    return false;
  }
  // id
  return true;
}

void
dis_tutorial1__msg__CustomMessage__fini(dis_tutorial1__msg__CustomMessage * msg)
{
  if (!msg) {
    return;
  }
  // content
  rosidl_runtime_c__String__fini(&msg->content);
  // id
}

bool
dis_tutorial1__msg__CustomMessage__are_equal(const dis_tutorial1__msg__CustomMessage * lhs, const dis_tutorial1__msg__CustomMessage * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // content
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->content), &(rhs->content)))
  {
    return false;
  }
  // id
  if (lhs->id != rhs->id) {
    return false;
  }
  return true;
}

bool
dis_tutorial1__msg__CustomMessage__copy(
  const dis_tutorial1__msg__CustomMessage * input,
  dis_tutorial1__msg__CustomMessage * output)
{
  if (!input || !output) {
    return false;
  }
  // content
  if (!rosidl_runtime_c__String__copy(
      &(input->content), &(output->content)))
  {
    return false;
  }
  // id
  output->id = input->id;
  return true;
}

dis_tutorial1__msg__CustomMessage *
dis_tutorial1__msg__CustomMessage__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dis_tutorial1__msg__CustomMessage * msg = (dis_tutorial1__msg__CustomMessage *)allocator.allocate(sizeof(dis_tutorial1__msg__CustomMessage), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(dis_tutorial1__msg__CustomMessage));
  bool success = dis_tutorial1__msg__CustomMessage__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
dis_tutorial1__msg__CustomMessage__destroy(dis_tutorial1__msg__CustomMessage * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    dis_tutorial1__msg__CustomMessage__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
dis_tutorial1__msg__CustomMessage__Sequence__init(dis_tutorial1__msg__CustomMessage__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dis_tutorial1__msg__CustomMessage * data = NULL;

  if (size) {
    data = (dis_tutorial1__msg__CustomMessage *)allocator.zero_allocate(size, sizeof(dis_tutorial1__msg__CustomMessage), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = dis_tutorial1__msg__CustomMessage__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        dis_tutorial1__msg__CustomMessage__fini(&data[i - 1]);
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
dis_tutorial1__msg__CustomMessage__Sequence__fini(dis_tutorial1__msg__CustomMessage__Sequence * array)
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
      dis_tutorial1__msg__CustomMessage__fini(&array->data[i]);
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

dis_tutorial1__msg__CustomMessage__Sequence *
dis_tutorial1__msg__CustomMessage__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dis_tutorial1__msg__CustomMessage__Sequence * array = (dis_tutorial1__msg__CustomMessage__Sequence *)allocator.allocate(sizeof(dis_tutorial1__msg__CustomMessage__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = dis_tutorial1__msg__CustomMessage__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
dis_tutorial1__msg__CustomMessage__Sequence__destroy(dis_tutorial1__msg__CustomMessage__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    dis_tutorial1__msg__CustomMessage__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
dis_tutorial1__msg__CustomMessage__Sequence__are_equal(const dis_tutorial1__msg__CustomMessage__Sequence * lhs, const dis_tutorial1__msg__CustomMessage__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!dis_tutorial1__msg__CustomMessage__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
dis_tutorial1__msg__CustomMessage__Sequence__copy(
  const dis_tutorial1__msg__CustomMessage__Sequence * input,
  dis_tutorial1__msg__CustomMessage__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(dis_tutorial1__msg__CustomMessage);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    dis_tutorial1__msg__CustomMessage * data =
      (dis_tutorial1__msg__CustomMessage *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!dis_tutorial1__msg__CustomMessage__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          dis_tutorial1__msg__CustomMessage__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!dis_tutorial1__msg__CustomMessage__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
