// Copyright 2007 - 2021, Alan Antonuk and the rabbitmq-c contributors.
// SPDX-License-Identifier: mit

#include <assert.h>
#include <sys/time.h>

#include "rabbitmq/amqp.h"
#include "rabbitmq/amqp_time.h"

static void test_time_from_now_rejects_invalid_usec() {
  amqp_time_t deadline;
  struct timeval invalid_timeout = {0, 1'000'000};
  struct timeval valid_timeout = {0, 999'999};

  assert(amqp_time_from_now(&deadline, &invalid_timeout) ==
         AMQP_STATUS_INVALID_PARAMETER);
  assert(amqp_time_from_now(&deadline, &valid_timeout) == AMQP_STATUS_OK);
}

static void test_connection_timeout_setters_validate_usec() {
  amqp_connection_state_t state = amqp_new_connection();
  struct timeval invalid_timeout = {1, 1'000'000};
  struct timeval valid_timeout = {1, 999'999};

  assert(state != nullptr);

  assert(amqp_set_handshake_timeout(state, &invalid_timeout) ==
         AMQP_STATUS_INVALID_PARAMETER);
  assert(amqp_set_rpc_timeout(state, &invalid_timeout) ==
         AMQP_STATUS_INVALID_PARAMETER);

  assert(amqp_set_handshake_timeout(state, &valid_timeout) == AMQP_STATUS_OK);
  assert(amqp_set_rpc_timeout(state, &valid_timeout) == AMQP_STATUS_OK);

  assert(amqp_destroy_connection(state) == AMQP_STATUS_OK);
}

int main() {
  test_time_from_now_rejects_invalid_usec();
  test_connection_timeout_setters_validate_usec();
  return 0;
}
