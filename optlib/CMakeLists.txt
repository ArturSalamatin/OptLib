# https://habr.com/ru/articles/461817/
# https://habr.com/ru/articles/155467/
# https://cmake.org/cmake/help/book/mastering-cmake/cmake/Help/guide/tutorial/index.html#adding-usage-requirements-for-library-step-3

# As you start working with CMake, 
# you will run into a variety of concepts such as 
# targets, 
# generators, and 
# commands.

# Probably the most important item is targets. 
# Targets represent 
# executables, 
# libraries, and 
# utilities 
# built by CMake. 
# Every add_library, add_executable, and add_custom_target 
# command creates a target. 
# For example, the following command will create 
# a target named “foo” that is a static library, 
# with foo1.c and foo2.c as source files.
# add_library(foo STATIC foo1.c foo2.c)


# This allows projects to require a given version of CMake and, 
# in addition, allows CMake to be backwards compatible.
# cmake_minimum_required(VERSION 3.8.0)

# # The next line of any top level CMakeLists file should be 
# # the project command. 
# # This command sets the name of the project and 
# # may specify other options such as language or version.
# project(OptLib
# # set the build version
#     VERSION 0.1
# # set languages used in the project
#     LANGUAGES C CXX)

# # Sepcify standard ABOVE the call to add_executable
# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# # add a subdirectory containing
# # library
# # add_subdirectory(test) # here tests are stored
# # add_subdirectory(examples) # here examples are stored

# # Finally, use the add_executable command to add an executable 
# # to the project using the given source file(s).
# # add_executable(
# #     ${PROJECT_NAME} # target name (here it is same as project name) which is built from the executables
# #     # sepcified below
# #     main.cpp
# # )

# # a library may be lnked to the target 
# # target_link_libraries(${PROJECT_NAME} PUBLIC <LibraryName>)
    

# # Config.h.in is used to generate the Config.h file
# # Config.h is generated in the BUILD directory
# # configure_file(Config.h.in Config.h)

# # So, this directory must be added
# # to the list of include directories
# target_include_directories(${PROJECT_NAME} PUBLIC
#     "${PROJECT_BINARY_DIR}"
#     "${PROJECT_SOURCE_DIR}/src"
#     )

# # parallel build with MSVC compiler
# if(MSVC AND MSVC_VERSION GREATER 1400)
#     add_compile_options(/MP)
# endif()

# # message(MESSAGE ${PROJECT_BINARY_DIR})

# target_compile_features(
#     ${PROJECT_NAME}
#     PRIVATE
#         cxx_auto_type
# )


# set_property(
#     TARGET ${PROJECT_NAME} 
#     PROPERTY CXX_STANDARD 17
# )

# enable_testing()

# # does the application run
# add_test(NAME Runs COMMAND OptLib)