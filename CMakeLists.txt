cmake_minimum_required (VERSION 3.5)
project(mympf VERSION 1.0)

if(DEBUG)
message(STATUS "compile debug version.")
add_definitions(-std=c++14 -g -O0 -DDEBUG -Wunused-variable)
else()
message(STATUS "compile release version.")
add_definitions(-std=c++14 -O3 -Wunused-variable)
endif(DEBUG)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "${CXX_FLAGS}")

#
# Sub modules directories
#
set(SRC_DIRECTORY ./src)

#
# Mympz include path
#
include_directories(
  ./
)

#
# System include path and link path
#
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

#
# Mympf public header file
#
set(MYMPF_HEADERS
  ${SRC_DIRECTORY}/mympf.h
  ${SRC_DIRECTORY}/compile.h
  ${SRC_DIRECTORY}/exception.h
  ${SRC_DIRECTORY}/debug.h
)

#
# Library Build
#
add_library(${PROJECT_NAME} STATIC
  ${SRC_DIRECTORY}/create.cc
  ${SRC_DIRECTORY}/print.cc
  ${SRC_DIRECTORY}/add.cc
  ${SRC_DIRECTORY}/sub.cc
  ${SRC_DIRECTORY}/mul.cc
  ${SRC_DIRECTORY}/sqr.cc
  ${SRC_DIRECTORY}/div.cc
  ${SRC_DIRECTORY}/mod.cc
  ${SRC_DIRECTORY}/exp.cc
  ${SRC_DIRECTORY}/cmp.cc
  ${SRC_DIRECTORY}/mympf.cc
  ${SRC_DIRECTORY}/constant.cc
  ${SRC_DIRECTORY}/debug.cc
  ${SRC_DIRECTORY}/floor.cc
  ${SRC_DIRECTORY}/ceil.cc
  ${SRC_DIRECTORY}/round.cc
)
target_link_libraries(${PROJECT_NAME} mympz my)

#
# Test Build
#
set(BUILD_TEST TRUE)
if(BUILD_TEST)

#
# Add SubDirectory
#
add_subdirectory(test)

#
# Enable Test
#
enable_testing()
add_test(NAME test_create COMMAND test_create)
set_tests_properties(test_create PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
add_test(NAME test_addsub COMMAND test_addsub)
set_tests_properties(test_addsub PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
add_test(NAME test_cmp COMMAND test_cmp)
set_tests_properties(test_cmp PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
add_test(NAME test_mul COMMAND test_mul)
set_tests_properties(test_mul PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
add_test(NAME test_exp COMMAND test_exp)
set_tests_properties(test_exp PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
add_test(NAME test_div COMMAND test_div)
set_tests_properties(test_div PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
add_test(NAME test_mod COMMAND test_mod)
set_tests_properties(test_mod PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")

#
# Auto Test
#
set(BUILD_AUTOTEST FALSE)
if(BUILD_AUTOTEST)
endif(BUILD_AUTOTEST)

endif(BUILD_TEST)

#
# Install Set
#
INSTALL(TARGETS mympf ARCHIVE DESTINATION lib)
INSTALL(FILES ${MYMPF_HEADERS} DESTINATION include/mympf)