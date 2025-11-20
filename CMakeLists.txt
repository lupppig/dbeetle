cmake_minimum_required(VERSION 3.30)
set(CMAKE_C_STANDARD 99)
project(dbeetle_root C)

enable_testing()

# Build the real project as a library (exclude main.c)
file(GLOB SRC_FILES "src/*.c" "src/*/*.c")
list(FILTER SRC_FILES EXCLUDE REGEX ".*main\\.c")

add_library(dbeetle_core ${SRC_FILES})

# External libs
find_library(YAML_LIB yaml)
target_link_libraries(dbeetle_core PUBLIC ${YAML_LIB} m)

target_include_directories(dbeetle_core PUBLIC include)

# Tests
add_subdirectory(cmake)
add_subdirectory(cmake/tests)

