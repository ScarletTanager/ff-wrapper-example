#include "test.h"
#include "proto.h"

Describe(Proto);
BeforeEach(Proto) {}
AfterEach(Proto) {}

#define CHANNEL_SIZE 10
#define DATA_SHORT "Payload"
#define DATA_LONG "This is a payload longer than the channel buffer"

Ensure(Proto, creates_channel) {
  channel chan = channel_create(CHANNEL_SIZE);
  assert_that(chan, is_non_null);
  channel_destroy(chan);
}

Ensure(Proto, writes_to_channel) {
  channel chan = channel_create(CHANNEL_SIZE);
  assert_that(chan, is_non_null);
  int written = channel_write(chan, DATA_SHORT, strlen(DATA_SHORT));
  assert_that(written, is_equal_to((int)strlen(DATA_SHORT)));
  channel_destroy(chan);
}

Ensure(Proto, write_to_channel_data_longer_than_buffer) {
  channel chan = channel_create(CHANNEL_SIZE);
  assert_that(chan, is_non_null);
  int written = channel_write(chan, DATA_LONG, strlen(DATA_LONG));
  assert_that(written, is_equal_to(CHANNEL_SIZE));
  channel_destroy(chan);
}

Ensure(Proto, write_to_channel_writes_only_as_many_bytes_as_are_free) {
  channel chan = channel_create(CHANNEL_SIZE);
  channel_write(chan, DATA_SHORT, strlen(DATA_SHORT));
  int written = channel_write(chan, DATA_LONG, strlen(DATA_LONG));
  assert_that(written, is_equal_to(CHANNEL_SIZE - strlen(DATA_SHORT)));
  channel_destroy(chan);
}

Ensure(Proto, write_to_full_channel_writes_zero_bytes) {
  channel chan = channel_create(CHANNEL_SIZE);
  int written = channel_write(chan, DATA_LONG, strlen(DATA_LONG));
  assert_that(written, is_equal_to(CHANNEL_SIZE));
  written = channel_write(chan, DATA_SHORT, strlen(DATA_SHORT));
  assert_that(written, is_equal_to(0));
}

Ensure(Proto, write_to_null_channel_returns_negative) {
  channel chan = NULL;
  int written = channel_write(chan, DATA_SHORT, strlen(DATA_SHORT));
  assert_that(written, is_equal_to(ERROR_WRITE_TO_NULL_CHANNEL));
}

Ensure(Proto, write_to_channel_with_null_buffer_returns_negative) {
  channel chan;
  int written = channel_write(chan, DATA_SHORT, strlen(DATA_SHORT));
  assert_that(written, is_equal_to(ERROR_WRITE_TO_NULL_BUFFER));
}

#define EXPECTED_PAYLOAD_SIZE 22

Ensure(Proto, returns_payload_size) {
  char *payload = strdup("Pit me an olive, knave");
  int payload_size = get_payload_size(payload);
  assert_that(payload_size, is_equal_to(EXPECTED_PAYLOAD_SIZE));
  free(payload);
}

Ensure(Proto, returns_non_null_payload) {
  char *payload = build_payload("asdfasdfasdfasdf", "thisispayloaddata");
  assert_that(payload, is_non_null);
  if (payload != NULL) {
    free(payload);
  }
}

Ensure(Proto, returns_payload) {
  char *payload = build_payload("asdfasdfasdfasdf", "thisispayloaddata");
  int comparison = memcmp("asdfasdfasdfasdfthisispayloaddata", payload, strlen(payload));
  assert_that(comparison, is_equal_to(0));
  if (payload != NULL) {
    free(payload);
  }
}

TestSuite *proto_tests() {
    TestSuite *suite = create_test_suite();
    add_test_with_context(suite, Proto, creates_channel);
    add_test_with_context(suite, Proto, writes_to_channel);
    add_test_with_context(suite, Proto, write_to_null_channel_returns_negative);
    add_test_with_context(suite, Proto, write_to_channel_with_null_buffer_returns_negative);
    add_test_with_context(suite, Proto, write_to_channel_data_longer_than_buffer);
    add_test_with_context(suite, Proto, write_to_channel_writes_only_as_many_bytes_as_are_free);
    add_test_with_context(suite, Proto, write_to_full_channel_writes_zero_bytes);
    add_test_with_context(suite, Proto, returns_payload_size);
    add_test_with_context(suite, Proto, returns_non_null_payload);
    add_test_with_context(suite, Proto, returns_payload);
    return suite;
}
