// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from hwpub:srv/Customserv.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "hwpub/srv/detail/customserv__rosidl_typesupport_introspection_c.h"
#include "hwpub/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "hwpub/srv/detail/customserv__functions.h"
#include "hwpub/srv/detail/customserv__struct.h"


// Include directives for member types
// Member `s`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void hwpub__srv__Customserv_Request__rosidl_typesupport_introspection_c__Customserv_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  hwpub__srv__Customserv_Request__init(message_memory);
}

void hwpub__srv__Customserv_Request__rosidl_typesupport_introspection_c__Customserv_Request_fini_function(void * message_memory)
{
  hwpub__srv__Customserv_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember hwpub__srv__Customserv_Request__rosidl_typesupport_introspection_c__Customserv_Request_message_member_array[2] = {
  {
    "s",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(hwpub__srv__Customserv_Request, s),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "time",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(hwpub__srv__Customserv_Request, time),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers hwpub__srv__Customserv_Request__rosidl_typesupport_introspection_c__Customserv_Request_message_members = {
  "hwpub__srv",  // message namespace
  "Customserv_Request",  // message name
  2,  // number of fields
  sizeof(hwpub__srv__Customserv_Request),
  hwpub__srv__Customserv_Request__rosidl_typesupport_introspection_c__Customserv_Request_message_member_array,  // message members
  hwpub__srv__Customserv_Request__rosidl_typesupport_introspection_c__Customserv_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  hwpub__srv__Customserv_Request__rosidl_typesupport_introspection_c__Customserv_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t hwpub__srv__Customserv_Request__rosidl_typesupport_introspection_c__Customserv_Request_message_type_support_handle = {
  0,
  &hwpub__srv__Customserv_Request__rosidl_typesupport_introspection_c__Customserv_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_hwpub
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, hwpub, srv, Customserv_Request)() {
  if (!hwpub__srv__Customserv_Request__rosidl_typesupport_introspection_c__Customserv_Request_message_type_support_handle.typesupport_identifier) {
    hwpub__srv__Customserv_Request__rosidl_typesupport_introspection_c__Customserv_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &hwpub__srv__Customserv_Request__rosidl_typesupport_introspection_c__Customserv_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "hwpub/srv/detail/customserv__rosidl_typesupport_introspection_c.h"
// already included above
// #include "hwpub/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "hwpub/srv/detail/customserv__functions.h"
// already included above
// #include "hwpub/srv/detail/customserv__struct.h"


// Include directives for member types
// Member `st`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void hwpub__srv__Customserv_Response__rosidl_typesupport_introspection_c__Customserv_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  hwpub__srv__Customserv_Response__init(message_memory);
}

void hwpub__srv__Customserv_Response__rosidl_typesupport_introspection_c__Customserv_Response_fini_function(void * message_memory)
{
  hwpub__srv__Customserv_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember hwpub__srv__Customserv_Response__rosidl_typesupport_introspection_c__Customserv_Response_message_member_array[1] = {
  {
    "st",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(hwpub__srv__Customserv_Response, st),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers hwpub__srv__Customserv_Response__rosidl_typesupport_introspection_c__Customserv_Response_message_members = {
  "hwpub__srv",  // message namespace
  "Customserv_Response",  // message name
  1,  // number of fields
  sizeof(hwpub__srv__Customserv_Response),
  hwpub__srv__Customserv_Response__rosidl_typesupport_introspection_c__Customserv_Response_message_member_array,  // message members
  hwpub__srv__Customserv_Response__rosidl_typesupport_introspection_c__Customserv_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  hwpub__srv__Customserv_Response__rosidl_typesupport_introspection_c__Customserv_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t hwpub__srv__Customserv_Response__rosidl_typesupport_introspection_c__Customserv_Response_message_type_support_handle = {
  0,
  &hwpub__srv__Customserv_Response__rosidl_typesupport_introspection_c__Customserv_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_hwpub
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, hwpub, srv, Customserv_Response)() {
  if (!hwpub__srv__Customserv_Response__rosidl_typesupport_introspection_c__Customserv_Response_message_type_support_handle.typesupport_identifier) {
    hwpub__srv__Customserv_Response__rosidl_typesupport_introspection_c__Customserv_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &hwpub__srv__Customserv_Response__rosidl_typesupport_introspection_c__Customserv_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "hwpub/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "hwpub/srv/detail/customserv__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers hwpub__srv__detail__customserv__rosidl_typesupport_introspection_c__Customserv_service_members = {
  "hwpub__srv",  // service namespace
  "Customserv",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // hwpub__srv__detail__customserv__rosidl_typesupport_introspection_c__Customserv_Request_message_type_support_handle,
  NULL  // response message
  // hwpub__srv__detail__customserv__rosidl_typesupport_introspection_c__Customserv_Response_message_type_support_handle
};

static rosidl_service_type_support_t hwpub__srv__detail__customserv__rosidl_typesupport_introspection_c__Customserv_service_type_support_handle = {
  0,
  &hwpub__srv__detail__customserv__rosidl_typesupport_introspection_c__Customserv_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, hwpub, srv, Customserv_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, hwpub, srv, Customserv_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_hwpub
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, hwpub, srv, Customserv)() {
  if (!hwpub__srv__detail__customserv__rosidl_typesupport_introspection_c__Customserv_service_type_support_handle.typesupport_identifier) {
    hwpub__srv__detail__customserv__rosidl_typesupport_introspection_c__Customserv_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)hwpub__srv__detail__customserv__rosidl_typesupport_introspection_c__Customserv_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, hwpub, srv, Customserv_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, hwpub, srv, Customserv_Response)()->data;
  }

  return &hwpub__srv__detail__customserv__rosidl_typesupport_introspection_c__Customserv_service_type_support_handle;
}
