# generated from rosidl_generator_py/resource/_idl.py.em
# with input from hwpub:srv/Customserv.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_Customserv_Request(type):
    """Metaclass of message 'Customserv_Request'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('hwpub')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'hwpub.srv.Customserv_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__customserv__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__customserv__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__customserv__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__customserv__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__customserv__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Customserv_Request(metaclass=Metaclass_Customserv_Request):
    """Message class 'Customserv_Request'."""

    __slots__ = [
        '_s',
        '_time',
    ]

    _fields_and_field_types = {
        's': 'string',
        'time': 'int64',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('int64'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.s = kwargs.get('s', str())
        self.time = kwargs.get('time', int())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.s != other.s:
            return False
        if self.time != other.time:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def s(self):
        """Message field 's'."""
        return self._s

    @s.setter
    def s(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 's' field must be of type 'str'"
        self._s = value

    @builtins.property
    def time(self):
        """Message field 'time'."""
        return self._time

    @time.setter
    def time(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'time' field must be of type 'int'"
            assert value >= -9223372036854775808 and value < 9223372036854775808, \
                "The 'time' field must be an integer in [-9223372036854775808, 9223372036854775807]"
        self._time = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_Customserv_Response(type):
    """Metaclass of message 'Customserv_Response'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('hwpub')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'hwpub.srv.Customserv_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__customserv__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__customserv__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__customserv__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__customserv__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__customserv__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Customserv_Response(metaclass=Metaclass_Customserv_Response):
    """Message class 'Customserv_Response'."""

    __slots__ = [
        '_st',
    ]

    _fields_and_field_types = {
        'st': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.st = kwargs.get('st', str())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.st != other.st:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def st(self):
        """Message field 'st'."""
        return self._st

    @st.setter
    def st(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'st' field must be of type 'str'"
        self._st = value


class Metaclass_Customserv(type):
    """Metaclass of service 'Customserv'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('hwpub')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'hwpub.srv.Customserv')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__customserv

            from hwpub.srv import _customserv
            if _customserv.Metaclass_Customserv_Request._TYPE_SUPPORT is None:
                _customserv.Metaclass_Customserv_Request.__import_type_support__()
            if _customserv.Metaclass_Customserv_Response._TYPE_SUPPORT is None:
                _customserv.Metaclass_Customserv_Response.__import_type_support__()


class Customserv(metaclass=Metaclass_Customserv):
    from hwpub.srv._customserv import Customserv_Request as Request
    from hwpub.srv._customserv import Customserv_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
