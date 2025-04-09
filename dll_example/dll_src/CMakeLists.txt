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
add_library(OperatorManagerWrapper STATIC ${HEADER_FILES} ${SOURCE_FILES})
target_compile_definitions(OperatorManagerWrapper PRIVATE MYLIBRARY_EXPORT)