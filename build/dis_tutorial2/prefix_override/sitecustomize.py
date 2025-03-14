import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/ilija/ros2_ws/src/RINS/install/dis_tutorial2'
