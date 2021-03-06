cmake_minimum_required (VERSION 2.6)
project(DroneApplications)

# Collect all sources
file(GLOB_RECURSE DRONE_APPLICATIONS_SOURCE_FILES "code/*.cpp" "code/*.h" "code/*.inl")

# Clasify sources according to folder structure.
# This creates a nice layout for the project in visual studio
# This macro is courtesy of http://www.cmake.org/pipermail/cmake/2013-November/056336.html
macro(GroupSources curdir)
	file(GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${curdir}
		${PROJECT_SOURCE_DIR}/${curdir}/*)
	foreach(child ${children})
		if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${curdir}/${child})
			GroupSources(${curdir}/${child})
		else()
			string(REPLACE "/" "\\" groupname ${curdir})
			source_group(${groupname} FILES ${PROJECT_SOURCE_DIR}/${curdir}/${child})
		endif()
	endforeach()
endmacro()

GroupSources(code)

# Compiler specific options
if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++11)
endif()

# Find 3rd party packages
find_package(OpenCV 3 REQUIRED core imgproc ml highgui features2d xfeatures2d calib3d objdetect)
set_target_properties(${OpenCV_LIBS} PROPERTIES MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE)
LINK_DIRECTORIES(${OpenCV_LIB_DIR})

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

# Library
add_library(DroneApplications STATIC ${DRONE_APPLICATIONS_SOURCE_FILES})
target_include_directories(DroneApplications PUBLIC ${OpenCV_INCLUDE_DIRS})
target_include_directories(DroneApplications PUBLIC ${PROJECT_SOURCE_DIR}/code)
target_include_directories(DroneApplications PUBLIC ${PROJECT_SOURCE_DIR}/../lib/bovil/src/code)
#target_include_directories(DroneApplications PUBLIC ${PROJECT_SOURCE_DIR}/../lib/ardrone-pp/src/code)

target_link_libraries(DroneApplications LINK_PUBLIC ${OpenCV_LIBS})
target_link_libraries(DroneApplications LINK_PUBLIC BOViL)
#target_link_libraries(DroneApplications LINK_PUBLIC ARdronepp)
target_link_libraries(DroneApplications LINK_PUBLIC ${OpenCV_LIBS} )
target_link_libraries(DroneApplications LINK_PUBLIC ${catkin_LIBRARIES} )