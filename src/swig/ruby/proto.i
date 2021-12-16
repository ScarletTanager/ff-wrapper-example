%module proto
%{
#include "lib/proto.h"
%}
int get_payload_size(char *payload);
char *build_payload(char *header, char *body);
