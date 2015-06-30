cmake_minimum_required (VERSION 2.6)
project(test_mavros)

# Compiler specific options
if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++11)
endif()


## Automate adding of ros libs
if(UNIX)
	set(ROS_INCLUDES /opt/ros/jade/include)
	set(ROS_DEPENDENCIES	/opt/ros/jade/lib/libroscpp.so /opt/ros/jade/lib/libcpp_common.so /opt/ros/jade/lib/librostime.so /opt/ros/jade/lib/librosconsole.so /opt/ros/jade/lib/libroscpp_serialization.so )
	## CHECK IF HAS MAVROS
	add_definitions(-D_HAS_ROS_LIBRARIES_)
endif()

## Create executable for mavros_sensor test
add_executable(testMavrosSensor ${PROJECT_SOURCE_DIR}/src/mavros_sensor.cpp)

target_include_directories(testMavrosSensor PUBLIC ${PROJECT_SOURCE_DIR}/../../../src/code)
target_include_directories(testMavrosSensor PUBLIC ${ROS_INCLUDES})
target_link_libraries(testMavrosSensor  LINK_PUBLIC DroneApplications)
target_link_libraries(testMavrosSensor  LINK_PUBLIC ${ROS_DEPENDENCIES})

add_test(testMavrosSensorUnit testMavrosSensor)

## Create executable for mavros_controller test
add_executable(testMavrosController ${PROJECT_SOURCE_DIR}/src/mavros_controller.cpp)

target_include_directories(testMavrosController PUBLIC ${PROJECT_SOURCE_DIR}/../../../src/code)
target_include_directories(testMavrosController PUBLIC ${ROS_INCLUDES})
target_link_libraries(testMavrosController  LINK_PUBLIC DroneApplications)
target_link_libraries(testMavrosController  LINK_PUBLIC ${ROS_DEPENDENCIES})

add_test(testMavrosControllerUnit testMavrosController)