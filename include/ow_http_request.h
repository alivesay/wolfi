#ifndef OW_HTTP_REQUEST_H
#define OW_HTTP_REQUEST_H


//#include "ow_hash_table.h"

struct ow_http_request {
  char *method;
  char *request_uri;
  char *major_version;
  char *minor_version;
  
//  struct ow_hash_table *headers;
};

struct ow_http_request*   ow_http_request_create   (void);

void                      ow_http_request_free     (struct ow_http_request const *p_http_request);


#endif // OW_HTTP_REQUEST_H
