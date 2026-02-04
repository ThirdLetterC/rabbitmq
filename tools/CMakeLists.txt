# Copyright 2007 - 2021, Alan Antonuk and the rabbitmq-c contributors.
# SPDX-License-Identifier: mit

set(PLATFORM_DIR unix)
set(RMQ_C_WARNING_FLAGS -Wall -Wextra -Wpedantic -Werror)

add_library(tools-common OBJECT)
target_sources(tools-common PRIVATE
  common.h
  common.c)
set_target_properties(tools-common PROPERTIES
  C_STANDARD 23
  C_STANDARD_REQUIRED YES
  C_EXTENSIONS NO)
target_compile_options(tools-common PRIVATE ${RMQ_C_WARNING_FLAGS})
if(ENABLE_SSL_SUPPORT)
  target_compile_definitions(tools-common PRIVATE -DWITH_SSL=1)
endif()
target_include_directories(tools-common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(tools-common PRIVATE rabbitmq::rabbitmq PUBLIC popt::popt)

add_executable(amqp-publish publish.c)
target_link_libraries(amqp-publish PRIVATE tools-common rabbitmq::rabbitmq)
set_target_properties(amqp-publish PROPERTIES
  C_STANDARD 23
  C_STANDARD_REQUIRED YES
  C_EXTENSIONS NO)
target_compile_options(amqp-publish PRIVATE ${RMQ_C_WARNING_FLAGS})

add_executable(amqp-get get.c)
target_link_libraries(amqp-get PRIVATE tools-common rabbitmq::rabbitmq)
set_target_properties(amqp-get PROPERTIES
  C_STANDARD 23
  C_STANDARD_REQUIRED YES
  C_EXTENSIONS NO)
target_compile_options(amqp-get PRIVATE ${RMQ_C_WARNING_FLAGS})

add_executable(amqp-consume consume.c ${PLATFORM_DIR}/process.h ${PLATFORM_DIR}/process.c)
target_include_directories(amqp-consume PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${PLATFORM_DIR})
target_link_libraries(amqp-consume PRIVATE tools-common rabbitmq::rabbitmq)
set_target_properties(amqp-consume PROPERTIES
  C_STANDARD 23
  C_STANDARD_REQUIRED YES
  C_EXTENSIONS NO)
target_compile_options(amqp-consume PRIVATE ${RMQ_C_WARNING_FLAGS})

add_executable(amqp-declare-queue declare_queue.c)
target_link_libraries(amqp-declare-queue PRIVATE tools-common rabbitmq::rabbitmq)
set_target_properties(amqp-declare-queue PROPERTIES
  C_STANDARD 23
  C_STANDARD_REQUIRED YES
  C_EXTENSIONS NO)
target_compile_options(amqp-declare-queue PRIVATE ${RMQ_C_WARNING_FLAGS})

add_executable(amqp-delete-queue delete_queue.c)
target_link_libraries(amqp-delete-queue PRIVATE tools-common rabbitmq::rabbitmq)
set_target_properties(amqp-delete-queue PROPERTIES
  C_STANDARD 23
  C_STANDARD_REQUIRED YES
  C_EXTENSIONS NO)
target_compile_options(amqp-delete-queue PRIVATE ${RMQ_C_WARNING_FLAGS})

install(TARGETS amqp-publish amqp-get amqp-consume amqp-declare-queue amqp-delete-queue
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
          COMPONENT rabbitmq-c-tools)

if (BUILD_TOOLS_DOCS)
  set(DOCS_SRCS
    doc/amqp-consume.xml
    doc/amqp-declare-queue.xml
    doc/amqp-delete-queue.xml
    doc/amqp-get.xml
    doc/amqp-publish.xml
    doc/librabbitmq-tools.xml
    )

  file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc)
  set(XMLTO_DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/doc/man-date.ent)
  STRING(TIMESTAMP BUILD_DATE "%Y-%m-%d" UTC)
  add_custom_command(
          OUTPUT ${XMLTO_DEPENDS}
         COMMAND echo ${BUILD_DATE} > ${XMLTO_DEPENDS}
          VERBATIM
          )

  set(XMLTO_COMMAND_ARGS --skip-validation --searchpath "${CMAKE_CURRENT_BINARY_DIR}/doc")

  XMLTO(${DOCS_SRCS}
    MODES man
    ALL)

  foreach(file ${XMLTO_FILES_man})
    get_filename_component(fileExt ${file} EXT)
    string( REGEX REPLACE "^[.]" "" fileExt ${fileExt} )
    install(
      FILES ${file}
      DESTINATION ${CMAKE_INSTALL_MANDIR}/man${fileExt}
      COMPONENT rabbitmq-c-tool-docs
      )
  endforeach()
endif()
