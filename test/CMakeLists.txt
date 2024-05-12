#
# This is a CMake makefile.  You can find the cmake utility and
# information about it at http://www.cmake.org
#

cmake_minimum_required(VERSION 3.14.0)

# create a variable called target_name and set it to the string "dtest"
set (target_name optlib_test)
PROJECT(${target_name})

# compile the dlib/all/source.cpp file into its own object just to make sure it compiles
# set(OPTLIB_TEST_COMPILE_ALL_SOURCE_CPP ON)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/..") 



include(CTest)

add_executable(point_test point_test.cpp)
add_test(NAME point_test
         COMMAND point_test)


include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)



