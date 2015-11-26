cmake_minimum_required (VERSION 2.6)
project(DroneApplications)

# Library Project
add_subdirectory(src)

# Dependencies
add_subdirectory(lib/bovil/src)
#add_subdirectory(lib/ardrone-pp/src)

# Test cases
add_subdirectory(tests)