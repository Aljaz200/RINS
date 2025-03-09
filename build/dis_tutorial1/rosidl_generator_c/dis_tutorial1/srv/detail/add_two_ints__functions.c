// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from dis_tutorial1:srv/AddTwoInts.idl
// generated code does not contain a copyright notice
#include "dis_tutorial1/srv/detail/add_two_ints__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

bool
dis_tutorial1__srv__AddTwoInts_Request__init(dis_tutorial1__srv__AddTwoInts_Request * msg)
{
  if (!msg) {
    return false;
  }
  // a
  // b
  return true;
}

void
dis_tutorial1__srv__AddTwoInts_Request__fini(dis_tutorial1__srv__AddTwoInts_Request * msg)
{
  if (!msg) {
    return;
  }
  // a
  // b
}

bool
dis_tutorial1__srv__AddTwoInts_Request__are_equal(const dis_tutorial1__srv__AddTwoInts_Request * lhs, const dis_tutorial1__srv__AddTwoInts_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // a
  if (lhs->a != rhs->a) {
    return false;
  }
  // b
  if (lhs->b != rhs->b) {
    return false;
  }
  return true;
}

bool
dis_tutorial1__srv__AddTwoInts_Request__copy(
  const dis_tutorial1__srv__AddTwoInts_Request * input,
  dis_tutorial1__srv__AddTwoInts_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // a
  output->a = input->a;
  // b
  output->b = input->b;
  return true;
}

dis_tutorial1__srv__AddTwoInts_Request *
dis_tutorial1__srv__AddTwoInts_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dis_tutorial1__srv__AddTwoInts_Request * msg = (dis_tutorial1__srv__AddTwoInts_Request *)allocator.allocate(sizeof(dis_tutorial1__srv__AddTwoInts_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(dis_tutorial1__srv__AddTwoInts_Request));
  bool success = dis_tutorial1__srv__AddTwoInts_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
dis_tutorial1__srv__AddTwoInts_Request__destroy(dis_tutorial1__srv__AddTwoInts_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    dis_tutorial1__srv__AddTwoInts_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
dis_tutorial1__srv__AddTwoInts_Request__Sequence__init(dis_tutorial1__srv__AddTwoInts_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dis_tutorial1__srv__AddTwoInts_Request * data = NULL;

  if (size) {
    data = (dis_tutorial1__srv__AddTwoInts_Request *)allocator.zero_allocate(size, sizeof(dis_tutorial1__srv__AddTwoInts_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = dis_tutorial1__srv__AddTwoInts_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        dis_tutorial1__srv__AddTwoInts_Request__fini(&data[i - 1]);
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
dis_tutorial1__srv__AddTwoInts_Request__Sequence__fini(dis_tutorial1__srv__AddTwoInts_Request__Sequence * array)
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
      dis_tutorial1__srv__AddTwoInts_Request__fini(&array->data[i]);
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

dis_tutorial1__srv__AddTwoInts_Request__Sequence *
dis_tutorial1__srv__AddTwoInts_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dis_tutorial1__srv__AddTwoInts_Request__Sequence * array = (dis_tutorial1__srv__AddTwoInts_Request__Sequence *)allocator.allocate(sizeof(dis_tutorial1__srv__AddTwoInts_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = dis_tutorial1__srv__AddTwoInts_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
dis_tutorial1__srv__AddTwoInts_Request__Sequence__destroy(dis_tutorial1__srv__AddTwoInts_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    dis_tutorial1__srv__AddTwoInts_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
dis_tutorial1__srv__AddTwoInts_Request__Sequence__are_equal(const dis_tutorial1__srv__AddTwoInts_Request__Sequence * lhs, const dis_tutorial1__srv__AddTwoInts_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!dis_tutorial1__srv__AddTwoInts_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
dis_tutorial1__srv__AddTwoInts_Request__Sequence__copy(
  const dis_tutorial1__srv__AddTwoInts_Request__Sequence * input,
  dis_tutorial1__srv__AddTwoInts_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(dis_tutorial1__srv__AddTwoInts_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    dis_tutorial1__srv__AddTwoInts_Request * data =
      (dis_tutorial1__srv__AddTwoInts_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!dis_tutorial1__srv__AddTwoInts_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          dis_tutorial1__srv__AddTwoInts_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!dis_tutorial1__srv__AddTwoInts_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


bool
dis_tutorial1__srv__AddTwoInts_Response__init(dis_tutorial1__srv__AddTwoInts_Response * msg)
{
  if (!msg) {
    return false;
  }
  // sum
  return true;
}

void
dis_tutorial1__srv__AddTwoInts_Response__fini(dis_tutorial1__srv__AddTwoInts_Response * msg)
{
  if (!msg) {
    return;
  }
  // sum
}

bool
dis_tutorial1__srv__AddTwoInts_Response__are_equal(const dis_tutorial1__srv__AddTwoInts_Response * lhs, const dis_tutorial1__srv__AddTwoInts_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // sum
  if (lhs->sum != rhs->sum) {
    return false;
  }
  return true;
}

bool
dis_tutorial1__srv__AddTwoInts_Response__copy(
  const dis_tutorial1__srv__AddTwoInts_Response * input,
  dis_tutorial1__srv__AddTwoInts_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // sum
  output->sum = input->sum;
  return true;
}

dis_tutorial1__srv__AddTwoInts_Response *
dis_tutorial1__srv__AddTwoInts_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dis_tutorial1__srv__AddTwoInts_Response * msg = (dis_tutorial1__srv__AddTwoInts_Response *)allocator.allocate(sizeof(dis_tutorial1__srv__AddTwoInts_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(dis_tutorial1__srv__AddTwoInts_Response));
  bool success = dis_tutorial1__srv__AddTwoInts_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
dis_tutorial1__srv__AddTwoInts_Response__destroy(dis_tutorial1__srv__AddTwoInts_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    dis_tutorial1__srv__AddTwoInts_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
dis_tutorial1__srv__AddTwoInts_Response__Sequence__init(dis_tutorial1__srv__AddTwoInts_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dis_tutorial1__srv__AddTwoInts_Response * data = NULL;

  if (size) {
    data = (dis_tutorial1__srv__AddTwoInts_Response *)allocator.zero_allocate(size, sizeof(dis_tutorial1__srv__AddTwoInts_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = dis_tutorial1__srv__AddTwoInts_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        dis_tutorial1__srv__AddTwoInts_Response__fini(&data[i - 1]);
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
dis_tutorial1__srv__AddTwoInts_Response__Sequence__fini(dis_tutorial1__srv__AddTwoInts_Response__Sequence * array)
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
      dis_tutorial1__srv__AddTwoInts_Response__fini(&array->data[i]);
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

dis_tutorial1__srv__AddTwoInts_Response__Sequence *
dis_tutorial1__srv__AddTwoInts_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dis_tutorial1__srv__AddTwoInts_Response__Sequence * array = (dis_tutorial1__srv__AddTwoInts_Response__Sequence *)allocator.allocate(sizeof(dis_tutorial1__srv__AddTwoInts_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = dis_tutorial1__srv__AddTwoInts_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
dis_tutorial1__srv__AddTwoInts_Response__Sequence__destroy(dis_tutorial1__srv__AddTwoInts_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    dis_tutorial1__srv__AddTwoInts_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
dis_tutorial1__srv__AddTwoInts_Response__Sequence__are_equal(const dis_tutorial1__srv__AddTwoInts_Response__Sequence * lhs, const dis_tutorial1__srv__AddTwoInts_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!dis_tutorial1__srv__AddTwoInts_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
dis_tutorial1__srv__AddTwoInts_Response__Sequence__copy(
  const dis_tutorial1__srv__AddTwoInts_Response__Sequence * input,
  dis_tutorial1__srv__AddTwoInts_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(dis_tutorial1__srv__AddTwoInts_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    dis_tutorial1__srv__AddTwoInts_Response * data =
      (dis_tutorial1__srv__AddTwoInts_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!dis_tutorial1__srv__AddTwoInts_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          dis_tutorial1__srv__AddTwoInts_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!dis_tutorial1__srv__AddTwoInts_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
