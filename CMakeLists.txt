# https://coderefinery.github.io/cmake-workshop/
# https://cliutils.gitlab.io/modern-cmake/
# https://cmake.org/cmake/help/v3.19/index.html

cmake_minimum_required(VERSION 3.14.0)

project(OptLib
# set the build version
    VERSION 0.1
# set languages used in the project
    LANGUAGES C CXX)

# Sepcify standard ABOVE the call to add_executable
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# specify where to place binaries and libraries
# so they end up in standard places with "make install"
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})


# parallel build with MSVC compiler
# if(MSVC AND MSVC_VERSION GREATER 1400)
#     add_compile_options(/MP)
# endif()

# process examples/CMakeLists.txt
add_subdirectory(examples)

# enable testing
enable_testing()
# process test/CMakeLists.txt
add_subdirectory(test)
