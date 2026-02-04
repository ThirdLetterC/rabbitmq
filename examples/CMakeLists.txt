# Copyright 2007 - 2021, Alan Antonuk and the rabbitmq-c contributors.
# SPDX-License-Identifier: mit

add_library(examples-common OBJECT)
target_sources(examples-common PRIVATE
  utils.h
  utils.c)
target_sources(examples-common PRIVATE unix/platform_utils.c)
target_link_libraries(examples-common PRIVATE rabbitmq::rabbitmq)
set_target_properties(examples-common PROPERTIES
  C_STANDARD 23
  C_STANDARD_REQUIRED YES
  C_EXTENSIONS NO)
set(RMQ_C_WARNING_FLAGS -Wall -Wextra -Wpedantic -Werror)
target_compile_options(examples-common PRIVATE ${RMQ_C_WARNING_FLAGS})

add_executable(amqp_sendstring amqp_sendstring.c)
target_link_libraries(amqp_sendstring PRIVATE examples-common rabbitmq::rabbitmq)
set_target_properties(amqp_sendstring PROPERTIES
  C_STANDARD 23
  C_STANDARD_REQUIRED YES
  C_EXTENSIONS NO)
target_compile_options(amqp_sendstring PRIVATE ${RMQ_C_WARNING_FLAGS})

add_executable(amqp_rpc_sendstring_client amqp_rpc_sendstring_client.c)
target_link_libraries(amqp_rpc_sendstring_client PRIVATE examples-common rabbitmq::rabbitmq)
set_target_properties(amqp_rpc_sendstring_client PROPERTIES
  C_STANDARD 23
  C_STANDARD_REQUIRED YES
  C_EXTENSIONS NO)
target_compile_options(amqp_rpc_sendstring_client PRIVATE ${RMQ_C_WARNING_FLAGS})

add_executable(amqp_exchange_declare amqp_exchange_declare.c)
target_link_libraries(amqp_exchange_declare PRIVATE examples-common rabbitmq::rabbitmq)
set_target_properties(amqp_exchange_declare PROPERTIES
  C_STANDARD 23
  C_STANDARD_REQUIRED YES
  C_EXTENSIONS NO)
target_compile_options(amqp_exchange_declare PRIVATE ${RMQ_C_WARNING_FLAGS})

add_executable(amqp_listen amqp_listen.c)
target_link_libraries(amqp_listen PRIVATE examples-common rabbitmq::rabbitmq)
set_target_properties(amqp_listen PROPERTIES
  C_STANDARD 23
  C_STANDARD_REQUIRED YES
  C_EXTENSIONS NO)
target_compile_options(amqp_listen PRIVATE ${RMQ_C_WARNING_FLAGS})

add_executable(amqp_producer amqp_producer.c)
target_link_libraries(amqp_producer PRIVATE examples-common rabbitmq::rabbitmq)
set_target_properties(amqp_producer PROPERTIES
  C_STANDARD 23
  C_STANDARD_REQUIRED YES
  C_EXTENSIONS NO)
target_compile_options(amqp_producer PRIVATE ${RMQ_C_WARNING_FLAGS})

add_executable(amqp_confirm_select amqp_confirm_select.c)
target_link_libraries(amqp_confirm_select PRIVATE examples-common rabbitmq::rabbitmq)
set_target_properties(amqp_confirm_select PROPERTIES
  C_STANDARD 23
  C_STANDARD_REQUIRED YES
  C_EXTENSIONS NO)
target_compile_options(amqp_confirm_select PRIVATE ${RMQ_C_WARNING_FLAGS})

add_executable(amqp_connect_timeout amqp_connect_timeout.c)
target_link_libraries(amqp_connect_timeout PRIVATE examples-common rabbitmq::rabbitmq)
set_target_properties(amqp_connect_timeout PROPERTIES
  C_STANDARD 23
  C_STANDARD_REQUIRED YES
  C_EXTENSIONS NO)
target_compile_options(amqp_connect_timeout PRIVATE ${RMQ_C_WARNING_FLAGS})

add_executable(amqp_consumer amqp_consumer.c)
target_link_libraries(amqp_consumer PRIVATE examples-common rabbitmq::rabbitmq)
set_target_properties(amqp_consumer PROPERTIES
  C_STANDARD 23
  C_STANDARD_REQUIRED YES
  C_EXTENSIONS NO)
target_compile_options(amqp_consumer PRIVATE ${RMQ_C_WARNING_FLAGS})

add_executable(amqp_unbind amqp_unbind.c)
target_link_libraries(amqp_unbind PRIVATE examples-common rabbitmq::rabbitmq)
set_target_properties(amqp_unbind PROPERTIES
  C_STANDARD 23
  C_STANDARD_REQUIRED YES
  C_EXTENSIONS NO)
target_compile_options(amqp_unbind PRIVATE ${RMQ_C_WARNING_FLAGS})

add_executable(amqp_bind amqp_bind.c)
target_link_libraries(amqp_bind PRIVATE examples-common rabbitmq::rabbitmq)
set_target_properties(amqp_bind PROPERTIES
  C_STANDARD 23
  C_STANDARD_REQUIRED YES
  C_EXTENSIONS NO)
target_compile_options(amqp_bind PRIVATE ${RMQ_C_WARNING_FLAGS})

add_executable(amqp_listenq amqp_listenq.c)
target_link_libraries(amqp_listenq PRIVATE examples-common rabbitmq::rabbitmq)
set_target_properties(amqp_listenq PROPERTIES
  C_STANDARD 23
  C_STANDARD_REQUIRED YES
  C_EXTENSIONS NO)
target_compile_options(amqp_listenq PRIVATE ${RMQ_C_WARNING_FLAGS})

if (ENABLE_SSL_SUPPORT)
  add_executable(amqp_ssl_connect amqp_ssl_connect.c)
  target_link_libraries(amqp_ssl_connect PRIVATE examples-common rabbitmq::rabbitmq)
  set_target_properties(amqp_ssl_connect PROPERTIES
    C_STANDARD 23
    C_STANDARD_REQUIRED YES
    C_EXTENSIONS NO)
  target_compile_options(amqp_ssl_connect PRIVATE ${RMQ_C_WARNING_FLAGS})
endif (ENABLE_SSL_SUPPORT)
