%module proto
%{
#define SWIG_FILE_WITH_INIT
#include "../../lib/proto.h"
%}
int get_payload_size(char *payload);
char *build_payload(char *header, char *body);
channel channel_create(int num);
int channel_write(channel chan, const void *data, int num);
