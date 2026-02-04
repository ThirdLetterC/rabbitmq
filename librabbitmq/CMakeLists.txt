# Copyright 2007 - 2021, Alan Antonuk and the rabbitmq-c contributors.
# SPDX-License-Identifier: mit

if (ENABLE_SSL_SUPPORT)
  SET(AMQP_SSL_SOCKET_SHIM_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../include/amqp_ssl_socket.h)
  set(AMQP_SSL_SOCKET_H_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../include/rabbitmq-c/ssl_socket.h)

  set(AMQP_SSL_SRCS
      amqp_openssl.c
      amqp_openssl_bio.c
      amqp_openssl_bio.h
      unix/threads.h
  )
  set(AMQP_SSL_LIBS OpenSSL::SSL)
  set(SSL_INCLUDE_DIRS unix)
  if (APPLE)
    # Apple has deprecated OpenSSL in 10.7+. This disables that warning.
    set_source_files_properties(${AMQP_SSL_SRCS}
      PROPERTIES COMPILE_FLAGS -Wno-deprecated-declarations)
  endif()
endif()

set(PUBLIC_INCLUDE_DIRS
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/../include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set(PRIVATE_INCLUDE_DIRS
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${SSL_INCLUDE_DIRS}
)

set(RMQ_C_WARNING_FLAGS -Wall -Wextra -Wpedantic -Werror)

set(RMQ_SOURCES
  ../include/amqp.h
  ../include/amqp_framing.h
  ${AMQP_SSL_SOCKET_SHIM_PATH}
  ../include/amqp_tcp_socket.h
  ../include/rabbitmq-c/amqp.h
  ../include/rabbitmq-c/framing.h
  ${AMQP_SSL_SOCKET_H_PATH}
  ../include/rabbitmq-c/tcp_socket.h
  amqp_api.c
  amqp_connection.c
  amqp_consumer.c
  amqp_framing.c
  amqp_mem.c
  ${AMQP_SSL_SRCS}
  amqp_private.h
  amqp_socket.c
  amqp_socket.h
  amqp_table.c
  amqp_table.h
  amqp_tcp_socket.c
  amqp_time.c
  amqp_time.h
  amqp_url.c
)

set(RMQ_LIBRARIES ${AMQP_SSL_LIBS} ${SOCKET_LIBRARIES} ${LIBRT} ${CMAKE_THREAD_LIBS_INIT})

if(BUILD_SHARED_LIBS)
  if (NOT APPLE)
    set(CMAKE_INSTALL_RPATH $ORIGIN)
  endif()

  add_library(rabbitmq SHARED)
  set(RMQ_GEN_EXPORT_TARGET rabbitmq)

  target_sources(rabbitmq PRIVATE ${RMQ_SOURCES})

  target_include_directories(rabbitmq
    PUBLIC ${PUBLIC_INCLUDE_DIRS}
    PRIVATE ${PRIVATE_INCLUDE_DIRS}
  )

  target_compile_definitions(rabbitmq PRIVATE -DHAVE_CONFIG_H)

  target_link_libraries(rabbitmq PRIVATE ${RMQ_LIBRARIES})
  target_compile_options(rabbitmq PRIVATE ${RMQ_C_WARNING_FLAGS})

  set_target_properties(rabbitmq PROPERTIES
    VERSION ${RMQ_VERSION}
    SOVERSION ${RMQ_SOVERSION}
    C_STANDARD 23
    C_STANDARD_REQUIRED YES
    C_EXTENSIONS NO
  )

  if (APPLE)
    set_target_properties(rabbitmq PROPERTIES
      MACHO_CURRENT_VERSION ${RMQ_SOVERSION}.${RMQ_SOVERSION_AGE}.${RMQ_SOVERSION_REVISION}
      MACHO_COMPATIBILITY_VERSION ${RMQ_SOVERSION}
    )
  endif()

  install(TARGETS rabbitmq EXPORT "${targets_export_name}"
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            COMPONENT rabbitmq-c-runtime
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT rabbitmq-c-runtime
            NAMELINK_COMPONENT rabbitmq-c-development
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT rabbitmq-c-development
  )

  add_library(rabbitmq::rabbitmq ALIAS rabbitmq)
endif()

if(BUILD_STATIC_LIBS)
  add_library(rabbitmq-static STATIC)

  target_sources(rabbitmq-static PRIVATE ${RMQ_SOURCES})
  if (NOT BUILD_SHARED_LIBS)
    set(RMQ_GEN_EXPORT_TARGET rabbitmq-static)
  endif()

  target_include_directories(rabbitmq-static
    PUBLIC ${PUBLIC_INCLUDE_DIRS}
    PRIVATE ${PRIVATE_INCLUDE_DIRS}
  )

  target_compile_definitions(rabbitmq-static
    PUBLIC -DAMQP_STATIC
    PRIVATE -DHAVE_CONFIG_H
  )

  target_link_libraries(rabbitmq-static PRIVATE ${RMQ_LIBRARIES})
  target_compile_options(rabbitmq-static PRIVATE ${RMQ_C_WARNING_FLAGS})

  set_target_properties(rabbitmq-static PROPERTIES
    VERSION ${RMQ_VERSION}
    SOVERSION ${RMQ_SOVERSION}
    C_STANDARD 23
    C_STANDARD_REQUIRED YES
    C_EXTENSIONS NO
  )

  if (APPLE)
    set_target_properties(rabbitmq-static PROPERTIES
      MACHO_CURRENT_VERSION ${RMQ_SOVERSION}.${RMQ_SOVERSION_AGE}.${RMQ_SOVERSION_REVISION}
      MACHO_COMPATIBILITY_VERSION ${RMQ_SOVERSION}
    )
  endif()

  set_target_properties(rabbitmq-static PROPERTIES OUTPUT_NAME rabbitmq)

  if(INSTALL_STATIC_LIBS)
    install(TARGETS rabbitmq-static EXPORT "${targets_export_name}"
      ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT rabbitmq-c-development
    )
  endif()

  add_library(rabbitmq::rabbitmq-static ALIAS rabbitmq-static)
endif()

include(GenerateExportHeader)
generate_export_header(${RMQ_GEN_EXPORT_TARGET}
  BASE_NAME AMQP
  EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/../include/rabbitmq-c/export.h
  STATIC_DEFINE AMQP_STATIC
  INCLUDE_GUARD_NAME RABBITMQ_C_EXPORT_H
)

install(FILES
  ../include/amqp.h
  ../include/amqp_framing.h
  ../include/amqp_tcp_socket.h
  ${AMQP_SSL_SOCKET_SHIM_PATH}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  COMPONENT rabbitmq-c-development
)

install(FILES
  ../include/rabbitmq-c/amqp.h
  ../include/rabbitmq-c/framing.h
  ../include/rabbitmq-c/tcp_socket.h
  ${AMQP_SSL_SOCKET_H_PATH}
  ${CMAKE_CURRENT_BINARY_DIR}/../include/rabbitmq-c/export.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/rabbitmq-c
  COMPONENT rabbitmq-c-development
)
