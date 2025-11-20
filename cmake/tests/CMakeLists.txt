# All test files inside tests/src
cmake_minimum_required(VERSION 3.30)
project(dbeetle_test C)

file(GLOB TEST_FILES "src/*.c")

add_executable(test_config_loader ${TEST_FILES})
# Link against the project library

target_link_libraries(test_config_loader PRIVATE dbeetle_core)

add_test(NAME test_config_loader COMMAND test_config_loader ${CMAKE_SOURCE_DIR}/cmake/tests/config.yml)
