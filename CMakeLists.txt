cmake_minimum_required(VERSION 3.15)

# set the project name
project(OptLib
# set the build version
    VERSION 0.1
# set languages used in the project
    LANGUAGES C CXX)

# parallel build with MSVC compiler
if(MSVC AND MSVC_VERSION GREATER 1400)
    add_compile_options(/MP)
endif()

# message(MESSAGE ${PROJECT_BINARY_DIR})

# gives the name to the target and sets its dependence on code files
add_executable(
    ${PROJECT_NAME} # target name (here it is same as project name) which is built from the executables
    # sepcified below
    main.cpp)

target_compile_features(
    ${PROJECT_NAME}
    PRIVATE
        cxx_auto_type
)

set_property(
    TARGET ${PROJECT_NAME} 
    PROPERTY CXX_STANDARD 17
)