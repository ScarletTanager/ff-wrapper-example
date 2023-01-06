%module proto
%{
#include "lib/proto.h"
%}
int get_payload_size(char *payload);
char *build_payload(char *header, char *body);
%newobject channel_create;
channel channel_create(int num);
int channel_write(channel chan, const void *data, int num);
