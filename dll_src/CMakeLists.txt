# https://batuhankoc.medium.com/use-cmake-to-create-and-use-dynamic-libraries-5f6498417b3c

cmake_minimum_required(VERSION 3.14.0)

project(MyDllWrapper)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the source files to the project
set(SOURCE_FILES
    Operator.cpp
    Manager.cpp
    Wrapper.cpp
)

# Add the header files to the project
set(HEADER_FILES
    Operator.h
    Manager.h
    Wrapper.h
)

# Create the shared library (DLL)
add_library(OperatorManagerWrapper SHARED ${HEADER_FILES} ${SOURCE_FILES})

target_compile_definitions(OperatorManagerWrapper PRIVATE MYLIBRARY_EXPORT)



project(AnExample)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(MyApp main.cpp)

target_link_libraries(MyApp ${CMAKE_SOURCE_DIR}/OperatorManagerWrapper.lib)