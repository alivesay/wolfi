#ifndef RFC3986_H
#define RFC3986_H

#include <stdlib.h>

typedef struct {
  char *scheme;
  char *userinfo;
  char *host;
  char *port;
  char *path;
  char *query;
  char *fragment;
} ow_rfc3986_uri_t;

ow_rfc3986_uri_t* ow_rfc3986_uri_create(const char *p_buffer);
void ow_rfc3986_uri_free(ow_rfc3986_uri_t *p_uri);

#endif // RFC3986_H
