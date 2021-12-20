#include "proto.h"

void *read_data(channel chan, int num);

channel channel_create(int num) {
  channel chan = (channel)malloc(sizeof(struct proto_channel));
  chan->buf = malloc(num);
  memset(chan->buf, '\0', 1);
  chan->buf_size = num;
  return chan;
}

void channel_destroy(channel chan) {
  if (chan != NULL) {
    if (chan->buf != NULL) {
      free(chan->buf);
    }
    free(chan);
  }
}

int channel_write(channel chan, const void *data, int num) {
  if (chan == NULL) {
    return ERROR_WRITE_TO_NULL_CHANNEL;
  }

  if (chan->buf == NULL) {
    return ERROR_WRITE_TO_NULL_BUFFER;
  }

  void *first_NUL = memchr(chan->buf, '\0', chan->buf_size);
  if (first_NUL == NULL) {
    /* Buffer appears to be full */
    return 0;
  }

  /* How much space do we have? */
  int free_space_len = (chan->buf + chan->buf_size - first_NUL);
  if (num < free_space_len) {
    memcpy(first_NUL, data, num);
    memset(first_NUL + num + 1, '\0', 1);
    return num;
  }

  memcpy(first_NUL, data, free_space_len);
  return free_space_len;
}

void *channel_read(channel chan, int num) {
  /* Is there data to be read? */
  void *first_NUL = memchr(chan->buf, '\0', chan->buf_size);

  if ((first_NUL == chan->buf) || (num == 0)) {
    return NULL;
  }

  int data_len, remaining_len, currently_used = first_NUL - chan->buf;
  void *data;
  if (currently_used < num) {
    data_len = currently_used;
  } else {
    data_len = num;
  }

  remaining_len = currently_used - data_len;

  /* Read and shift */
  data = read_data(chan, data_len);
  memmove(chan->buf, chan->buf + data_len, remaining_len);
  memset(chan->buf + remaining_len, '\0', 1);

  return data;
}

void *read_data(channel chan, int num) {
  void *data = malloc(num);
  return memcpy(data, chan->buf, num);
}

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
