cmake_minimum_required (VERSION 2.6)
project(test_mavros)

# Collect all sources
file(GLOB_RECURSE TEST_MAVROS_SOURCE_FILES "code/*.cpp" "code/*.h" "code/*.inl")

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

find_package(mavros REQUIRED)
include_directories(${MAVROS_INCLUDE_DIR})

message(STATUS ${MAVROS_INCLUDE_DIR})

## CHECK IF HAS MAVROS
add_definitions(-D_HAS_ROS_LIBRARIES)

add_executable(test_mavros ${TEST_MAVROS_SOURCE_FILES})

target_include_directories(test_mavros PUBLIC ${PROJECT_SOURCE_DIR}/code)
target_include_directories(test_mavros PUBLIC ${PROJECT_SOURCE_DIR}/../../../src/code)

target_link_libraries(test_mavros  LINK_PUBLIC DroneApplications)