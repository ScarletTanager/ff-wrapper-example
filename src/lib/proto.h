#ifndef LIB_PROTO_H
#define LIB_PROTO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct proto_channel {
    void *buf;
    int buf_size;
};

/*
 * Error return values
 */
#define ERROR_WRITE_TO_NULL_CHANNEL -5
#define ERROR_WRITE_TO_NULL_BUFFER -3

typedef struct proto_channel *channel;

extern channel channel_create(int num);
extern void channel_destroy(channel chan);
extern int channel_write(channel chan, const void *data, int num);
extern void *channel_read(channel chan, int num);

extern int get_payload_size(char *payload);
extern char *build_payload(char *header, char *body);


#endif
