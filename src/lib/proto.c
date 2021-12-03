#include "proto.h"

int get_payload_size(char *payload) {
  return (int)strlen(payload); /* Don't do this in real code */
}

char *build_payload(char *header, char *body) {
  size_t l_header = strlen(header);
  size_t l_body = strlen(body);
  char *payload = malloc(l_header + l_body + 1);
  if (payload != NULL) {
    memcpy(payload, header, l_header);
    memcpy((payload + l_header), body, (l_body + 1));
  }
  return payload;
}
