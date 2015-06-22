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
find_package( OpenCV REQUIRED )

add_library(DroneApplications STATIC ${DRONE_APPLICATIONS_SOURCE_FILES})

target_include_directories(DroneApplications PUBLIC ${PROJECT_SOURCE_DIR}/code)
target_include_directories(DroneApplications PUBLIC ${PROJECT_SOURCE_DIR}/../lib/bovil/src/code)
target_include_directories(DroneApplications PUBLIC ${PROJECT_SOURCE_DIR}/../lib/ardrone-pp/src/code)
target_link_libraries(DroneApplications LINK_PUBLIC BOViL)
target_link_libraries(DroneApplications LINK_PUBLIC ARdronepp)
target_link_libraries(DroneApplications LINK_PUBLIC ${OpenCV_LIBS} )