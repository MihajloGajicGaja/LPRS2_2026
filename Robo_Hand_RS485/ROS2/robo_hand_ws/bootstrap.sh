#!/bin/bash

#source /opt/ros/humble/setup.bash
source /opt/ros/jazzy/setup.bash

pushd src/
# 0c3eabf56711b5b95e9edaba5600b86d99fe4229
git clone https://github.com/xArm-Developer/xarm_ros2.git --recursive -b ${ROS_DISTRO}
popd

# Make patch with:
#pushd src/xarm_ros2
#git diff > ../../patches/xarm_ros2__jazzy.patch
#popd

patch -p1 -d src/xarm_ros2/ < patches/xarm_ros2__${ROS_DISTRO}.patch


#pushd src/
#git clone https://github.com/moveit/moveit2
#mv moveit2/moveit_ros/moveit_servo .
#rm -rf moveit2
#popd