cmake_minimum_required (VERSION 2.6)
project(test_mavros)

# Compiler specific options
if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++11)
endif()

## Automate adding of ros libs
set(ROS_INCLUDES /opt/ros/jade/include)
set(ROS_DEPENDENCIES	/opt/ros/jade/lib/libroscpp.so /opt/ros/jade/lib/libcpp_common.so /opt/ros/jade/lib/librostime.so /opt/ros/jade/lib/librosconsole.so /opt/ros/jade/lib/libroscpp_serialization.so )
## CHECK IF HAS MAVROS
add_definitions(-D_HAS_ROS_LIBRARIES_)


## Create executable for mavros_sensor test
add_executable(mavros_sensor ${PROJECT_SOURCE_DIR}/code/mavros_sensor.cpp)

target_include_directories(mavros_sensor PUBLIC ${PROJECT_SOURCE_DIR}/../../../src/code)
target_link_libraries(mavros_sensor  LINK_PUBLIC DroneApplications)

target_include_directories(mavros_sensor PUBLIC ${ROS_INCLUDES})
target_link_libraries(mavros_sensor  LINK_PUBLIC ${ROS_DEPENDENCIES})

## Create executable for mavros_controller test
add_executable(mavros_controller ${PROJECT_SOURCE_DIR}/code/mavros_controller.cpp)

target_include_directories(mavros_controller PUBLIC ${PROJECT_SOURCE_DIR}/../../../src/code)
target_link_libraries(mavros_controller  LINK_PUBLIC DroneApplications)

target_include_directories(mavros_controller PUBLIC ${ROS_INCLUDES})
target_link_libraries(mavros_controller  LINK_PUBLIC ${ROS_DEPENDENCIES})





