# Copyright 2007 - 2021, Alan Antonuk and the rabbitmq-c contributors.
# SPDX-License-Identifier: mit

include_directories(
  ${LIBRABBITMQ_INCLUDE_DIRS}
  ${CMAKE_CURRENT_BINARY_DIR}/../librabbitmq/
  ${CMAKE_CURRENT_SOURCE_DIR}/../librabbitmq/)

add_definitions(-DHAVE_CONFIG_H)
add_definitions(-DAMQP_STATIC)

set(RMQ_C_WARNING_FLAGS -Wall -Wextra -Wpedantic -Werror)

add_executable(test_parse_url test_parse_url.c)
target_link_libraries(test_parse_url rabbitmq-static)
set_target_properties(test_parse_url PROPERTIES
  C_STANDARD 23
  C_STANDARD_REQUIRED YES
  C_EXTENSIONS NO)
target_compile_options(test_parse_url PRIVATE ${RMQ_C_WARNING_FLAGS})
add_test(parse_url test_parse_url)

add_executable(test_tables test_tables.c)
target_link_libraries(test_tables rabbitmq-static)
set_target_properties(test_tables PROPERTIES
  C_STANDARD 23
  C_STANDARD_REQUIRED YES
  C_EXTENSIONS NO)
target_compile_options(test_tables PRIVATE ${RMQ_C_WARNING_FLAGS})
add_test(tables test_tables)
configure_file(test_tables.expected ${CMAKE_CURRENT_BINARY_DIR}/tests/test_tables.expected COPYONLY)

add_executable(test_status_enum
               test_status_enum.c)
target_link_libraries(test_status_enum rabbitmq-static)
set_target_properties(test_status_enum PROPERTIES
  C_STANDARD 23
  C_STANDARD_REQUIRED YES
  C_EXTENSIONS NO)
target_compile_options(test_status_enum PRIVATE ${RMQ_C_WARNING_FLAGS})
add_test(status_enum test_status_enum)

add_executable(test_basic
               test_basic.c)
target_link_libraries(test_basic rabbitmq-static)
set_target_properties(test_basic PROPERTIES
  C_STANDARD 23
  C_STANDARD_REQUIRED YES
  C_EXTENSIONS NO)
target_compile_options(test_basic PRIVATE ${RMQ_C_WARNING_FLAGS})

if (RUN_SYSTEM_TESTS)
  if (NOT APPLE)
    add_test(basic test_basic)
  endif()
endif(RUN_SYSTEM_TESTS)

add_executable(test_sasl_mechanism test_sasl_mechanism.c)
target_link_libraries(test_sasl_mechanism rabbitmq-static)
set_target_properties(test_sasl_mechanism PROPERTIES
  C_STANDARD 23
  C_STANDARD_REQUIRED YES
  C_EXTENSIONS NO)
target_compile_options(test_sasl_mechanism PRIVATE ${RMQ_C_WARNING_FLAGS})
add_test(sasl_mechanism test_sasl_mechanism)

add_executable(test_merge_capabilities test_merge_capabilities.c)
target_link_libraries(test_merge_capabilities rabbitmq-static)
set_target_properties(test_merge_capabilities PROPERTIES
  C_STANDARD 23
  C_STANDARD_REQUIRED YES
  C_EXTENSIONS NO)
target_compile_options(test_merge_capabilities PRIVATE ${RMQ_C_WARNING_FLAGS})
add_test(merge_capabilities test_merge_capabilities)
