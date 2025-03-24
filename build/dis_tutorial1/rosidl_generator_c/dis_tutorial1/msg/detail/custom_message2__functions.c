// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from dis_tutorial1:msg/CustomMessage2.idl
// generated code does not contain a copyright notice
#include "dis_tutorial1/msg/detail/custom_message2__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `text`
#include "rosidl_runtime_c/string_functions.h"

bool
dis_tutorial1__msg__CustomMessage2__init(dis_tutorial1__msg__CustomMessage2 * msg)
{
  if (!msg) {
    return false;
  }
  // text
  if (!rosidl_runtime_c__String__init(&msg->text)) {
    dis_tutorial1__msg__CustomMessage2__fini(msg);
    return false;
  }
  // number
  // flag
  return true;
}

void
dis_tutorial1__msg__CustomMessage2__fini(dis_tutorial1__msg__CustomMessage2 * msg)
{
  if (!msg) {
    return;
  }
  // text
  rosidl_runtime_c__String__fini(&msg->text);
  // number
  // flag
}

bool
dis_tutorial1__msg__CustomMessage2__are_equal(const dis_tutorial1__msg__CustomMessage2 * lhs, const dis_tutorial1__msg__CustomMessage2 * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // text
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->text), &(rhs->text)))
  {
    return false;
  }
  // number
  if (lhs->number != rhs->number) {
    return false;
  }
  // flag
  if (lhs->flag != rhs->flag) {
    return false;
  }
  return true;
}

bool
dis_tutorial1__msg__CustomMessage2__copy(
  const dis_tutorial1__msg__CustomMessage2 * input,
  dis_tutorial1__msg__CustomMessage2 * output)
{
  if (!input || !output) {
    return false;
  }
  // text
  if (!rosidl_runtime_c__String__copy(
      &(input->text), &(output->text)))
  {
    return false;
  }
  // number
  output->number = input->number;
  // flag
  output->flag = input->flag;
  return true;
}

dis_tutorial1__msg__CustomMessage2 *
dis_tutorial1__msg__CustomMessage2__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dis_tutorial1__msg__CustomMessage2 * msg = (dis_tutorial1__msg__CustomMessage2 *)allocator.allocate(sizeof(dis_tutorial1__msg__CustomMessage2), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(dis_tutorial1__msg__CustomMessage2));
  bool success = dis_tutorial1__msg__CustomMessage2__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
dis_tutorial1__msg__CustomMessage2__destroy(dis_tutorial1__msg__CustomMessage2 * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    dis_tutorial1__msg__CustomMessage2__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
dis_tutorial1__msg__CustomMessage2__Sequence__init(dis_tutorial1__msg__CustomMessage2__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dis_tutorial1__msg__CustomMessage2 * data = NULL;

  if (size) {
    data = (dis_tutorial1__msg__CustomMessage2 *)allocator.zero_allocate(size, sizeof(dis_tutorial1__msg__CustomMessage2), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = dis_tutorial1__msg__CustomMessage2__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        dis_tutorial1__msg__CustomMessage2__fini(&data[i - 1]);
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
dis_tutorial1__msg__CustomMessage2__Sequence__fini(dis_tutorial1__msg__CustomMessage2__Sequence * array)
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
      dis_tutorial1__msg__CustomMessage2__fini(&array->data[i]);
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

dis_tutorial1__msg__CustomMessage2__Sequence *
dis_tutorial1__msg__CustomMessage2__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dis_tutorial1__msg__CustomMessage2__Sequence * array = (dis_tutorial1__msg__CustomMessage2__Sequence *)allocator.allocate(sizeof(dis_tutorial1__msg__CustomMessage2__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = dis_tutorial1__msg__CustomMessage2__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
dis_tutorial1__msg__CustomMessage2__Sequence__destroy(dis_tutorial1__msg__CustomMessage2__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    dis_tutorial1__msg__CustomMessage2__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
dis_tutorial1__msg__CustomMessage2__Sequence__are_equal(const dis_tutorial1__msg__CustomMessage2__Sequence * lhs, const dis_tutorial1__msg__CustomMessage2__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!dis_tutorial1__msg__CustomMessage2__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
dis_tutorial1__msg__CustomMessage2__Sequence__copy(
  const dis_tutorial1__msg__CustomMessage2__Sequence * input,
  dis_tutorial1__msg__CustomMessage2__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(dis_tutorial1__msg__CustomMessage2);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    dis_tutorial1__msg__CustomMessage2 * data =
      (dis_tutorial1__msg__CustomMessage2 *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!dis_tutorial1__msg__CustomMessage2__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          dis_tutorial1__msg__CustomMessage2__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!dis_tutorial1__msg__CustomMessage2__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
