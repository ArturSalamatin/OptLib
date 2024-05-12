cmake_minimum_required(VERSION 3.14.0)
# Every project needs a name.  We call this the "examples" project.
project(examples)

# Tell cmake we will need dlib.  This command will pull in dlib and compile it
# into your project.  Note that you don't need to compile or install dlib.  All
# cmake needs is the dlib source code folder and it will take care of everything.
# add_subdirectory(../optlib optlib_build)

# Since there are a lot of examples I'm going to use a macro to simplify this
# CMakeLists.txt file. However, usually you will create only one executable in
# your cmake projects and use the syntax shown above.
macro(add_example name)
   add_executable(${name} ${name}.cpp)
  # Header files are located in the following folder.
  # So, <optlib/xxx.h> can be called within te examples project
  # include_directories("${CMAKE_CURRENT_SOURCE_DIR}/..") 
   target_include_directories(${name} PUBLIC "${PROJECT_SOURCE_DIR}/..")

   # this is here because the config.h will be generated in PROJECT_BINARY_DIR
   target_include_directories(${name}
  PRIVATE
    ${PROJECT_BINARY_DIR}
  )

  # let the preprocessor know about the system name
  # let the preprocessor know about the system name
  if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  target_compile_definitions(${name} PUBLIC "IS_LINUX")
  endif()
  if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  target_compile_definitions(${name} PUBLIC "IS_MACOS")
  endif()
  if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  target_compile_definitions(${name} PUBLIC "IS_WINDOWS")
  endif()


  
find_package(OpenMP REQUIRED COMPONENTS CXX)

endmacro()

# include(CMakePrintHelpers)
# foreach(key
#   IN ITEMS
#     NUMBER_OF_LOGICAL_CORES
#     NUMBER_OF_PHYSICAL_CORES
#     IS_64BIT
#     HAS_SSE2
#     OS_NAME
#     OS_RELEASE
#   )
#   # query the item ${key} and save its value in the variable _${key}
#   cmake_host_system_information(RESULT _${key} QUERY ${key})
#   cmake_print_variables(_${key})
# endforeach()

# configure_file(config-template.h config.h @ONLY)

add_example(points_ex)
add_example(pointvals_ex)
add_example(setofpoints_ex)
add_example(setofpointvals_ex)
add_example(functions_ex)
add_example(state_ex)
add_example(optimizer_ex)