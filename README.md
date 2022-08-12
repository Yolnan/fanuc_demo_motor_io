# End-effector Motor I/O
This package contains the code needed to setup and run the motor attached to the end-effector of the FANUC Scan-N-Plan demo at SwRI

This package utilizes tf2_ros and tf2_geometry_msgs to get tool position data. The tool position data is obtained from ROS2 via ROS bridge to set the arduino motor control signal I/O pin. 

There are two nodes. One node obtains tool position data and publishes a boolean topic indicating whether the motor should be turn on or off. The second node runs via rosserial and subscribes to the boolean topic and sets I/O pin accordingly.
## Install/Setup
Download and install Arduino IDE from [here](https://www.arduino.cc/en/software)

After installing the Arduino IDE, follow these [instructions](http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup)

Clone this repository to your ROS1 workspace source folder:
```bash
git clone https://github.com/Yolnan/fanuc_demo_motor_io.git
```

If necessary, install ROS package dependencies:
```bash
rosdep install --rosdistro noetic --ignore-src --from-paths .
```

The ee_motor_io.yaml contains the following parameters: 
- `target_frame_name` for lookupTransform
- `source_frame_name` for lookupTransform 
- `trigger_height` to turn motor on/off in meters


## Build Package
```bash
source /opt/ros/noetic/setup.bash
catkin build ee_motor_io
```

## Running System
```bash
source /opt/ros/noetic/setup.bash
roslaunch ee_motor_io ee_motor_io.launch
```