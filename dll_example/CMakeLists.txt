# https://batuhankoc.medium.com/use-cmake-to-create-and-use-dynamic-libraries-5f6498417b3c

cmake_minimum_required(VERSION 3.14.0)

project(MyDllExample 
    LANGUAGES C CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(dll_src)
# which calls 
# add_library(OperatorManagerWrapper SHARED ${HEADER_FILES} ${SOURCE_FILES})
# target_compile_definitions(OperatorManagerWrapper PRIVATE MYLIBRARY_EXPORT)

add_executable(MyApp main.cpp)

# target_link_libraries(MyApp ${CMAKE_SOURCE_DIR}/OperatorManagerWrapper.lib)

# a library may be lnked to the target 
target_link_libraries(MyApp PUBLIC OperatorManagerWrapper)

target_include_directories(MyApp PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/dll_src/"
                          )

# message(PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")

# target_include_directories(MyApp PUBLIC
#                            "${PROJECT_BINARY_DIR}"
#                            )