# All test files inside tests/src
cmake_minimum_required(VERSION 3.30)
set(CMAKE_C_STANDARD 99)
project(dbeetle_test C)

file(GLOB TEST_A "src/test_config_loader.c")
file(GLOB TEST_B "src/test_config_arg_parser.c")

add_executable(test_config_loader ${TEST_A})
add_executable(test_config_arg_parser ${TEST_B})
# Link against the project library

target_link_libraries(test_config_loader PRIVATE dbeetle_core)
target_link_libraries(test_config_arg_parser PRIVATE dbeetle_core)

add_test(NAME test_config_loader COMMAND test_config_loader "${CMAKE_SOURCE_DIR}/cmake/tests/config.yml")
add_test(NAME test_config_arg_parser COMMAND test_config_arg_parser "--config_path=${CMAKE_SOURCE_DIR}/cmake/tests/config.yml"  "--db_timeout_seconds=10" "--storage_compression=deflate2" "--runtime_log_level=8" "--storage_remote_target=https://cloudflare.com/connect")
