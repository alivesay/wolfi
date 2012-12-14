#ifndef URI_H
#define URI_H

#include <stdlib.h>

struct ow_uri {
  char *scheme;
  char *userinfo;
  char *host;
  char *port;
  char *path;
  char *query;
  char *fragment;
} ;

struct ow_uri* ow_uri_create(const char *p_buffer);
void ow_uri_free(struct ow_uri *p_uri);

#endif // URI_H
