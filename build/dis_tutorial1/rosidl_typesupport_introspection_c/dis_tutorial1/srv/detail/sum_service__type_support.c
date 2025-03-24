// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from dis_tutorial1:srv/SumService.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "dis_tutorial1/srv/detail/sum_service__rosidl_typesupport_introspection_c.h"
#include "dis_tutorial1/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "dis_tutorial1/srv/detail/sum_service__functions.h"
#include "dis_tutorial1/srv/detail/sum_service__struct.h"


// Include directives for member types
// Member `request_text`
#include "rosidl_runtime_c/string_functions.h"
// Member `numbers`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void dis_tutorial1__srv__SumService_Request__rosidl_typesupport_introspection_c__SumService_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  dis_tutorial1__srv__SumService_Request__init(message_memory);
}

void dis_tutorial1__srv__SumService_Request__rosidl_typesupport_introspection_c__SumService_Request_fini_function(void * message_memory)
{
  dis_tutorial1__srv__SumService_Request__fini(message_memory);
}

size_t dis_tutorial1__srv__SumService_Request__rosidl_typesupport_introspection_c__size_function__SumService_Request__numbers(
  const void * untyped_member)
{
  const rosidl_runtime_c__int32__Sequence * member =
    (const rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return member->size;
}

const void * dis_tutorial1__srv__SumService_Request__rosidl_typesupport_introspection_c__get_const_function__SumService_Request__numbers(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__int32__Sequence * member =
    (const rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return &member->data[index];
}

void * dis_tutorial1__srv__SumService_Request__rosidl_typesupport_introspection_c__get_function__SumService_Request__numbers(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__int32__Sequence * member =
    (rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return &member->data[index];
}

void dis_tutorial1__srv__SumService_Request__rosidl_typesupport_introspection_c__fetch_function__SumService_Request__numbers(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const int32_t * item =
    ((const int32_t *)
    dis_tutorial1__srv__SumService_Request__rosidl_typesupport_introspection_c__get_const_function__SumService_Request__numbers(untyped_member, index));
  int32_t * value =
    (int32_t *)(untyped_value);
  *value = *item;
}

void dis_tutorial1__srv__SumService_Request__rosidl_typesupport_introspection_c__assign_function__SumService_Request__numbers(
  void * untyped_member, size_t index, const void * untyped_value)
{
  int32_t * item =
    ((int32_t *)
    dis_tutorial1__srv__SumService_Request__rosidl_typesupport_introspection_c__get_function__SumService_Request__numbers(untyped_member, index));
  const int32_t * value =
    (const int32_t *)(untyped_value);
  *item = *value;
}

bool dis_tutorial1__srv__SumService_Request__rosidl_typesupport_introspection_c__resize_function__SumService_Request__numbers(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__int32__Sequence * member =
    (rosidl_runtime_c__int32__Sequence *)(untyped_member);
  rosidl_runtime_c__int32__Sequence__fini(member);
  return rosidl_runtime_c__int32__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember dis_tutorial1__srv__SumService_Request__rosidl_typesupport_introspection_c__SumService_Request_message_member_array[2] = {
  {
    "request_text",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(dis_tutorial1__srv__SumService_Request, request_text),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "numbers",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(dis_tutorial1__srv__SumService_Request, numbers),  // bytes offset in struct
    NULL,  // default value
    dis_tutorial1__srv__SumService_Request__rosidl_typesupport_introspection_c__size_function__SumService_Request__numbers,  // size() function pointer
    dis_tutorial1__srv__SumService_Request__rosidl_typesupport_introspection_c__get_const_function__SumService_Request__numbers,  // get_const(index) function pointer
    dis_tutorial1__srv__SumService_Request__rosidl_typesupport_introspection_c__get_function__SumService_Request__numbers,  // get(index) function pointer
    dis_tutorial1__srv__SumService_Request__rosidl_typesupport_introspection_c__fetch_function__SumService_Request__numbers,  // fetch(index, &value) function pointer
    dis_tutorial1__srv__SumService_Request__rosidl_typesupport_introspection_c__assign_function__SumService_Request__numbers,  // assign(index, value) function pointer
    dis_tutorial1__srv__SumService_Request__rosidl_typesupport_introspection_c__resize_function__SumService_Request__numbers  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers dis_tutorial1__srv__SumService_Request__rosidl_typesupport_introspection_c__SumService_Request_message_members = {
  "dis_tutorial1__srv",  // message namespace
  "SumService_Request",  // message name
  2,  // number of fields
  sizeof(dis_tutorial1__srv__SumService_Request),
  dis_tutorial1__srv__SumService_Request__rosidl_typesupport_introspection_c__SumService_Request_message_member_array,  // message members
  dis_tutorial1__srv__SumService_Request__rosidl_typesupport_introspection_c__SumService_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  dis_tutorial1__srv__SumService_Request__rosidl_typesupport_introspection_c__SumService_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t dis_tutorial1__srv__SumService_Request__rosidl_typesupport_introspection_c__SumService_Request_message_type_support_handle = {
  0,
  &dis_tutorial1__srv__SumService_Request__rosidl_typesupport_introspection_c__SumService_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_dis_tutorial1
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dis_tutorial1, srv, SumService_Request)() {
  if (!dis_tutorial1__srv__SumService_Request__rosidl_typesupport_introspection_c__SumService_Request_message_type_support_handle.typesupport_identifier) {
    dis_tutorial1__srv__SumService_Request__rosidl_typesupport_introspection_c__SumService_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &dis_tutorial1__srv__SumService_Request__rosidl_typesupport_introspection_c__SumService_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "dis_tutorial1/srv/detail/sum_service__rosidl_typesupport_introspection_c.h"
// already included above
// #include "dis_tutorial1/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "dis_tutorial1/srv/detail/sum_service__functions.h"
// already included above
// #include "dis_tutorial1/srv/detail/sum_service__struct.h"


// Include directives for member types
// Member `response_text`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void dis_tutorial1__srv__SumService_Response__rosidl_typesupport_introspection_c__SumService_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  dis_tutorial1__srv__SumService_Response__init(message_memory);
}

void dis_tutorial1__srv__SumService_Response__rosidl_typesupport_introspection_c__SumService_Response_fini_function(void * message_memory)
{
  dis_tutorial1__srv__SumService_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember dis_tutorial1__srv__SumService_Response__rosidl_typesupport_introspection_c__SumService_Response_message_member_array[2] = {
  {
    "response_text",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(dis_tutorial1__srv__SumService_Response, response_text),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "sum",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(dis_tutorial1__srv__SumService_Response, sum),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers dis_tutorial1__srv__SumService_Response__rosidl_typesupport_introspection_c__SumService_Response_message_members = {
  "dis_tutorial1__srv",  // message namespace
  "SumService_Response",  // message name
  2,  // number of fields
  sizeof(dis_tutorial1__srv__SumService_Response),
  dis_tutorial1__srv__SumService_Response__rosidl_typesupport_introspection_c__SumService_Response_message_member_array,  // message members
  dis_tutorial1__srv__SumService_Response__rosidl_typesupport_introspection_c__SumService_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  dis_tutorial1__srv__SumService_Response__rosidl_typesupport_introspection_c__SumService_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t dis_tutorial1__srv__SumService_Response__rosidl_typesupport_introspection_c__SumService_Response_message_type_support_handle = {
  0,
  &dis_tutorial1__srv__SumService_Response__rosidl_typesupport_introspection_c__SumService_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_dis_tutorial1
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dis_tutorial1, srv, SumService_Response)() {
  if (!dis_tutorial1__srv__SumService_Response__rosidl_typesupport_introspection_c__SumService_Response_message_type_support_handle.typesupport_identifier) {
    dis_tutorial1__srv__SumService_Response__rosidl_typesupport_introspection_c__SumService_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &dis_tutorial1__srv__SumService_Response__rosidl_typesupport_introspection_c__SumService_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "dis_tutorial1/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "dis_tutorial1/srv/detail/sum_service__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers dis_tutorial1__srv__detail__sum_service__rosidl_typesupport_introspection_c__SumService_service_members = {
  "dis_tutorial1__srv",  // service namespace
  "SumService",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // dis_tutorial1__srv__detail__sum_service__rosidl_typesupport_introspection_c__SumService_Request_message_type_support_handle,
  NULL  // response message
  // dis_tutorial1__srv__detail__sum_service__rosidl_typesupport_introspection_c__SumService_Response_message_type_support_handle
};

static rosidl_service_type_support_t dis_tutorial1__srv__detail__sum_service__rosidl_typesupport_introspection_c__SumService_service_type_support_handle = {
  0,
  &dis_tutorial1__srv__detail__sum_service__rosidl_typesupport_introspection_c__SumService_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dis_tutorial1, srv, SumService_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dis_tutorial1, srv, SumService_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_dis_tutorial1
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dis_tutorial1, srv, SumService)() {
  if (!dis_tutorial1__srv__detail__sum_service__rosidl_typesupport_introspection_c__SumService_service_type_support_handle.typesupport_identifier) {
    dis_tutorial1__srv__detail__sum_service__rosidl_typesupport_introspection_c__SumService_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)dis_tutorial1__srv__detail__sum_service__rosidl_typesupport_introspection_c__SumService_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dis_tutorial1, srv, SumService_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dis_tutorial1, srv, SumService_Response)()->data;
  }

  return &dis_tutorial1__srv__detail__sum_service__rosidl_typesupport_introspection_c__SumService_service_type_support_handle;
}
