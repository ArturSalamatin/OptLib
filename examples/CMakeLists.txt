cmake_minimum_required(VERSION 3.8.0)
# Every project needs a name.  We call this the "examples" project.
project(examples)
# Header files are located in the following folder.
# So, <optlib/xxx.h> can be called within te examples project
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/..") 

# Tell cmake we will need dlib.  This command will pull in dlib and compile it
# into your project.  Note that you don't need to compile or install dlib.  All
# cmake needs is the dlib source code folder and it will take care of everything.
# add_subdirectory(../optlib optlib_build)

# Since there are a lot of examples I'm going to use a macro to simplify this
# CMakeLists.txt file. However, usually you will create only one executable in
# your cmake projects and use the syntax shown above.
macro(add_example name)
   add_executable(${name} ${name}.cpp)
 #  target_link_libraries(${name} optlib::optlib)
   target_include_directories(${name} PUBLIC "${PROJECT_SOURCE_DIR}/..")

   # if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.13.0") 
   # # And strip symbols to make your binary smaller if you like.  Certainly not
   # # required though.
   #     target_link_options(${name} PRIVATE $<$<CONFIG:RELEASE>:-s>)
   # endif()
endmacro()

add_example(points_ex)
add_example(pointvals_ex)
add_example(setofpoints_ex)
add_example(setofpointvals_ex)
add_example(functions_ex)
add_example(state_ex)
add_example(optimizer_ex)