#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include "hash_table.h"

struct ow_http_message {
  char *method;
  char *request_uri;
  char *major_version;
  char *minor_version;
  
  struct ow_hash_table *headers;
};

struct ow_http_message* ow_http_message_create(const char* p_buffer);
void ow_http_message_free(struct ow_http_message *p_http_message);

#endif // HTTP_MESSAGE_H
