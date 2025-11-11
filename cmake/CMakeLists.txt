cmake_minimum_required(VERSION 3.30)
project(dbeetle C)

# Set default compiler to GCC if not specified
if(NOT CMAKE_C_COMPILER)
    set(CMAKE_C_COMPILER gcc)
endif()

# Collect all C source files
file(GLOB SRC_FILES "../src/*.c")



# Create the executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ../include)
# Compiler flags (applies to all targets)
add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wconversion
    -Wformat=2
    -std=c11
)


install(TARGETS ${PROJECT_NAME} DESTINATION /usr/bin)

