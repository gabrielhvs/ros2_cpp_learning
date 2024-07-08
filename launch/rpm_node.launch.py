from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import ExecuteProcess


def generate_launch_description():
    return LaunchDescription([
        Node(
            package="ros2_cpp_learning",
            executable="rpm_pub",
            name="rpm_pub_node",
            parameters=[
                {"rpm_val": 5.0}#, ....
            ]
        ),
        Node(
            package="ros2_cpp_learning",
            executable="converter_rpm2speed",
            name="speed_calculator_node",
            parameters=[
                {"wheel_radios": 10.0}#, ....
            ]
        ),
        ExecuteProcess(
            cmd=['ros2','topic','list'],
            output='screen'
        ),
        ExecuteProcess(
            cmd=['ros2','topic','echo', '/speed'],
            output='screen'
        )
    ])