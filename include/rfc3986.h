#ifndef RFC3986_H
#define RFC3986_H

#include <stdlib.h>

typedef struct {
  const char *scheme;   size_t scheme_len;
  const char *userinfo; size_t userinfo_len;
  const char *host;     size_t host_len;
  const char *port;     size_t port_len;
  const char *path;     size_t path_len;
  const char *query;    size_t query_len;
  const char *fragment; size_t fragment_len;
} ow_rfc3986_index_t;

typedef struct {
  char *scheme;
  char *userinfo;
  char *host;
  char *port;
  char *path;
  char *query;
  char *fragment;
} ow_rfc3986_uri_t;

ow_rfc3986_uri_t* ow_rfc3986_uri_parse(const char *p_buffer);
void ow_rfc3986_uri_free(ow_rfc3986_uri_t *p_uri);

#endif // RFC3986_H
