// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from dis_tutorial1:srv/SumService.idl
// generated code does not contain a copyright notice
#include "dis_tutorial1/srv/detail/sum_service__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `request_text`
#include "rosidl_runtime_c/string_functions.h"
// Member `numbers`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
dis_tutorial1__srv__SumService_Request__init(dis_tutorial1__srv__SumService_Request * msg)
{
  if (!msg) {
    return false;
  }
  // request_text
  if (!rosidl_runtime_c__String__init(&msg->request_text)) {
    dis_tutorial1__srv__SumService_Request__fini(msg);
    return false;
  }
  // numbers
  if (!rosidl_runtime_c__int32__Sequence__init(&msg->numbers, 0)) {
    dis_tutorial1__srv__SumService_Request__fini(msg);
    return false;
  }
  return true;
}

void
dis_tutorial1__srv__SumService_Request__fini(dis_tutorial1__srv__SumService_Request * msg)
{
  if (!msg) {
    return;
  }
  // request_text
  rosidl_runtime_c__String__fini(&msg->request_text);
  // numbers
  rosidl_runtime_c__int32__Sequence__fini(&msg->numbers);
}

bool
dis_tutorial1__srv__SumService_Request__are_equal(const dis_tutorial1__srv__SumService_Request * lhs, const dis_tutorial1__srv__SumService_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // request_text
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->request_text), &(rhs->request_text)))
  {
    return false;
  }
  // numbers
  if (!rosidl_runtime_c__int32__Sequence__are_equal(
      &(lhs->numbers), &(rhs->numbers)))
  {
    return false;
  }
  return true;
}

bool
dis_tutorial1__srv__SumService_Request__copy(
  const dis_tutorial1__srv__SumService_Request * input,
  dis_tutorial1__srv__SumService_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // request_text
  if (!rosidl_runtime_c__String__copy(
      &(input->request_text), &(output->request_text)))
  {
    return false;
  }
  // numbers
  if (!rosidl_runtime_c__int32__Sequence__copy(
      &(input->numbers), &(output->numbers)))
  {
    return false;
  }
  return true;
}

dis_tutorial1__srv__SumService_Request *
dis_tutorial1__srv__SumService_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dis_tutorial1__srv__SumService_Request * msg = (dis_tutorial1__srv__SumService_Request *)allocator.allocate(sizeof(dis_tutorial1__srv__SumService_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(dis_tutorial1__srv__SumService_Request));
  bool success = dis_tutorial1__srv__SumService_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
dis_tutorial1__srv__SumService_Request__destroy(dis_tutorial1__srv__SumService_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    dis_tutorial1__srv__SumService_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
dis_tutorial1__srv__SumService_Request__Sequence__init(dis_tutorial1__srv__SumService_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dis_tutorial1__srv__SumService_Request * data = NULL;

  if (size) {
    data = (dis_tutorial1__srv__SumService_Request *)allocator.zero_allocate(size, sizeof(dis_tutorial1__srv__SumService_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = dis_tutorial1__srv__SumService_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        dis_tutorial1__srv__SumService_Request__fini(&data[i - 1]);
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
dis_tutorial1__srv__SumService_Request__Sequence__fini(dis_tutorial1__srv__SumService_Request__Sequence * array)
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
      dis_tutorial1__srv__SumService_Request__fini(&array->data[i]);
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

dis_tutorial1__srv__SumService_Request__Sequence *
dis_tutorial1__srv__SumService_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dis_tutorial1__srv__SumService_Request__Sequence * array = (dis_tutorial1__srv__SumService_Request__Sequence *)allocator.allocate(sizeof(dis_tutorial1__srv__SumService_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = dis_tutorial1__srv__SumService_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
dis_tutorial1__srv__SumService_Request__Sequence__destroy(dis_tutorial1__srv__SumService_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    dis_tutorial1__srv__SumService_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
dis_tutorial1__srv__SumService_Request__Sequence__are_equal(const dis_tutorial1__srv__SumService_Request__Sequence * lhs, const dis_tutorial1__srv__SumService_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!dis_tutorial1__srv__SumService_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
dis_tutorial1__srv__SumService_Request__Sequence__copy(
  const dis_tutorial1__srv__SumService_Request__Sequence * input,
  dis_tutorial1__srv__SumService_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(dis_tutorial1__srv__SumService_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    dis_tutorial1__srv__SumService_Request * data =
      (dis_tutorial1__srv__SumService_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!dis_tutorial1__srv__SumService_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          dis_tutorial1__srv__SumService_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!dis_tutorial1__srv__SumService_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `response_text`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

bool
dis_tutorial1__srv__SumService_Response__init(dis_tutorial1__srv__SumService_Response * msg)
{
  if (!msg) {
    return false;
  }
  // response_text
  if (!rosidl_runtime_c__String__init(&msg->response_text)) {
    dis_tutorial1__srv__SumService_Response__fini(msg);
    return false;
  }
  // sum
  return true;
}

void
dis_tutorial1__srv__SumService_Response__fini(dis_tutorial1__srv__SumService_Response * msg)
{
  if (!msg) {
    return;
  }
  // response_text
  rosidl_runtime_c__String__fini(&msg->response_text);
  // sum
}

bool
dis_tutorial1__srv__SumService_Response__are_equal(const dis_tutorial1__srv__SumService_Response * lhs, const dis_tutorial1__srv__SumService_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // response_text
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->response_text), &(rhs->response_text)))
  {
    return false;
  }
  // sum
  if (lhs->sum != rhs->sum) {
    return false;
  }
  return true;
}

bool
dis_tutorial1__srv__SumService_Response__copy(
  const dis_tutorial1__srv__SumService_Response * input,
  dis_tutorial1__srv__SumService_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // response_text
  if (!rosidl_runtime_c__String__copy(
      &(input->response_text), &(output->response_text)))
  {
    return false;
  }
  // sum
  output->sum = input->sum;
  return true;
}

dis_tutorial1__srv__SumService_Response *
dis_tutorial1__srv__SumService_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dis_tutorial1__srv__SumService_Response * msg = (dis_tutorial1__srv__SumService_Response *)allocator.allocate(sizeof(dis_tutorial1__srv__SumService_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(dis_tutorial1__srv__SumService_Response));
  bool success = dis_tutorial1__srv__SumService_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
dis_tutorial1__srv__SumService_Response__destroy(dis_tutorial1__srv__SumService_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    dis_tutorial1__srv__SumService_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
dis_tutorial1__srv__SumService_Response__Sequence__init(dis_tutorial1__srv__SumService_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dis_tutorial1__srv__SumService_Response * data = NULL;

  if (size) {
    data = (dis_tutorial1__srv__SumService_Response *)allocator.zero_allocate(size, sizeof(dis_tutorial1__srv__SumService_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = dis_tutorial1__srv__SumService_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        dis_tutorial1__srv__SumService_Response__fini(&data[i - 1]);
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
dis_tutorial1__srv__SumService_Response__Sequence__fini(dis_tutorial1__srv__SumService_Response__Sequence * array)
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
      dis_tutorial1__srv__SumService_Response__fini(&array->data[i]);
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

dis_tutorial1__srv__SumService_Response__Sequence *
dis_tutorial1__srv__SumService_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dis_tutorial1__srv__SumService_Response__Sequence * array = (dis_tutorial1__srv__SumService_Response__Sequence *)allocator.allocate(sizeof(dis_tutorial1__srv__SumService_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = dis_tutorial1__srv__SumService_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
dis_tutorial1__srv__SumService_Response__Sequence__destroy(dis_tutorial1__srv__SumService_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    dis_tutorial1__srv__SumService_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
dis_tutorial1__srv__SumService_Response__Sequence__are_equal(const dis_tutorial1__srv__SumService_Response__Sequence * lhs, const dis_tutorial1__srv__SumService_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!dis_tutorial1__srv__SumService_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
dis_tutorial1__srv__SumService_Response__Sequence__copy(
  const dis_tutorial1__srv__SumService_Response__Sequence * input,
  dis_tutorial1__srv__SumService_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(dis_tutorial1__srv__SumService_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    dis_tutorial1__srv__SumService_Response * data =
      (dis_tutorial1__srv__SumService_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!dis_tutorial1__srv__SumService_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          dis_tutorial1__srv__SumService_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!dis_tutorial1__srv__SumService_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
