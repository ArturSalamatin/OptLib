# useful links
# https://cgold.readthedocs.io/en/latest/tutorials/libraries/static-shared.html
# https://cgold.readthedocs.io/en/latest/overview/cmake-can.html
# https://stackoverflow.com/questions/17511496/how-to-create-a-shared-library-with-cmake
# https://vector-of-bool.github.io/docs/vscode-cmake-tools/configuring.html
# https://coderefinery.github.io/cmake-workshop/
# https://coderefinery.github.io/cmake-workshop/flags-definitions-debugging/
# https://cmake.org/cmake/help/latest/guide/tutorial/Packaging%20Debug%20and%20Release.html
# https://coderefinery.github.io/cmake-workshop/fetch-content/

# https://cmake.org/cmake/help/latest/variable/CMAKE_BUILD_TYPE.html
# https://stackoverflow.com/questions/7724569/debug-vs-release-in-cmake
# https://stackoverflow.com/questions/7724569/debug-vs-release-in-cmake

# https://github.com/esufaev/Parallel-Operations-Toolkit
# https://github.com/Data-Analysis-Department/temp_calc/blob/py/build.cmd

# https://ps-group.github.io/cxx/cmake_cheatsheet
# https://batuhankoc.medium.com/use-cmake-to-create-and-use-dynamic-libraries-5f6498417b3c

# https://coderefinery.github.io/cmake-workshop/
# https://cliutils.gitlab.io/modern-cmake/
# https://cmake.org/cmake/help/v3.19/index.html

# to add submodule
# git submodule add https://github.com/google/googletest deps/gtest/
# git submodule add https://gitlab.com/libeigen/eigen deps/eigen/

cmake_minimum_required(VERSION 3.14.0)

# operator for solution in VS
project(OptLib
# set the build version
    VERSION 0.1
# set languages used in the project
    LANGUAGES C CXX)

# Specify standard ABOVE the call to add_executable
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenMP)
    if (OPENMP_FOUND)
            message(STATUS "OpenMP Found") 
            set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
            set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
            set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
            list(APPEND GPN_USE_LIST OPENMP) # GPN_USE_LIST may be required...
    else()
            message(STATUS "OpenMP NOT Found") 
    endif()

# build CMakeLists in subdirectories
add_subdirectory(deps/eigen)

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
