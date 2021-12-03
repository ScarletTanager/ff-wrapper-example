#include "test.h"
#include "proto.h"

Describe(Proto);
BeforeEach(Proto) {}
AfterEach(Proto) {}

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
    add_test_with_context(suite, Proto, returns_payload_size);
    add_test_with_context(suite, Proto, returns_non_null_payload);
    add_test_with_context(suite, Proto, returns_payload);
    return suite;
}
