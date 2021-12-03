#ifndef LIB_PROTO_H
#define LIB_PROTO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int get_payload_size(char *payload);
extern char *build_payload(char *header, char *body);

#endif
