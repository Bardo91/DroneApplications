cmake_minimum_required (VERSION 2.6)
project(test_mavros)

# Compiler specific options
if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++11)
endif()


## Automate adding of ros libs
find_package(catkin COMPONENTS
	roscpp
	std_msgs
	sensor_msgs
	std_srvs
	message_generation
)

if(catkin_FOUND)
	add_definitions(-D_HAS_ROS_LIBRARIES_)
endif()


## Create executable for mavros_sensor test
add_executable(testMavrosSensor ${PROJECT_SOURCE_DIR}/src/testMavrosSensor.cpp)

target_include_directories(testMavrosSensor PUBLIC ${PROJECT_SOURCE_DIR}/../../../src/code)
target_link_libraries(testMavrosSensor  LINK_PUBLIC DroneApplications)
target_link_libraries(testMavrosSensor LINK_PUBLIC ${catkin_LIBRARIES} )

add_test(testMavrosSensorUnit testMavrosSensor)

## Create executable for mavros_controller test
add_executable(testMavrosController ${PROJECT_SOURCE_DIR}/src/testMavrosController.cpp)

target_include_directories(testMavrosController PUBLIC ${PROJECT_SOURCE_DIR}/../../../src/code)
target_link_libraries(testMavrosController  LINK_PUBLIC DroneApplications)
target_link_libraries(testMavrosController LINK_PUBLIC ${catkin_LIBRARIES} )

add_test(testMavrosControllerUnit testMavrosController)