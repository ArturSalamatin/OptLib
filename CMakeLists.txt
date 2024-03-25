cmake_minimum_required(VERSION 3.0)

# set the project name
project(OptLib
# set the build version
    VERSION 0.1
# set languages used in the project
    LANGUAGES C CXX)

# gives the name to the target and sets its dependence on code files
add_executable(
    ${PROJECT_NAME} # target name (here it is same as project name) which is built from the executables
    # sepcified below
    main.cpp)