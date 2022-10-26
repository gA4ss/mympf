cmake_minimum_required (VERSION 3.5)
project(mympf_test VERSION 1.0)

# -g allows for gdb debugging
# turn on -03 for best performance
# add_definitions(-std=c++11 -g -O0 -Wunused-variable)
add_definitions(-std=c++11 -g -O0 -DDEBUG -Wunused-variable)
# add_definitions(-std=c++11 -O3 -Wunused-variable)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "${CXX_FLAGS}")

#
# Sub modules directories
#
set(SRC_DIRECTORY .)

#
# Mympz include path
#
include_directories(
  ../src
)

#
# System include path and link path
#
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

#
# Main Test
#
add_executable(test_create ${SRC_DIRECTORY}/test_create.cc)
target_link_libraries(test_create mympf gtest pthread)
add_executable(test_addsub ${SRC_DIRECTORY}/test_addsub.cc)
target_link_libraries(test_addsub mympf gtest pthread)


#
# Misc Test
#
add_executable(test_misc ${SRC_DIRECTORY}/misc/test_misc.cc)
target_link_libraries(test_misc mympf)