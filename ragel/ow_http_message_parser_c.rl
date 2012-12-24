%%{
  machine http_message_parser_c;
  
  action mark          { mark = fpc; }
  action method        { OW_HTTP_MESSAGE_SET_FIELD(method,        mark, fpc - mark); }
  action request_uri   { OW_HTTP_MESSAGE_SET_FIELD(request_uri,   mark, fpc - mark); }
  action major_version { OW_HTTP_MESSAGE_SET_FIELD(major_version, mark, fpc - mark); }
  action minor_version { OW_HTTP_MESSAGE_SET_FIELD(minor_version, mark, fpc - mark); }
  action header_name
  { 
    prev_header = http_message->headers;
    http_message->headers = calloc(1, sizeof(*http_message->headers));
  
    OW_HTTP_MESSAGE_SET_FIELD(headers->name, fpc, fpc - mark);

    http_message->headers->next = prev_header;
  }
  action header_value { OW_HTTP_MESSAGE_SET_FIELD(headers->value, fpc, fpc - mark); }

  include http_message_parser 'ow_http_message_parser.rl';

  main := HTTP_message;
}%%

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ow_http_message.h"
#include "ow_uri.h"

%% write data;

#define OW_HTTP_MESSAGE_SET_FIELD(field, offset, len)                          \
  do {                                                                         \
    if (http_message->field) free(http_message->field);                        \
    http_message->field = malloc((len) * sizeof(*http_message->field) + 1);    \
    memcpy(http_message->field, offset, (len) * sizeof(*http_message->field)); \
    http_message->field[len] = '\0';                                           \
  } while(0)

struct ow_http_message* ow_http_message_create(const char* p_buffer)
{
  int cs;
  const char *p, *pe, *mark, *eof;
  struct ow_http_message *http_message;
  struct ow_http_message_header *prev_header;

  mark = p = p_buffer;
  eof = pe = p + strlen(p);

  http_message = calloc(1, sizeof(*http_message));
  if (!http_message) goto _fail;

  %% write init;
  %% write exec;

  return http_message;

_fail:
  ow_http_message_free(http_message);
  return NULL;
}

void ow_http_message_free(struct ow_http_message *p_http_message)
{
  if (p_http_message) {
    struct ow_http_message_header *p = p_http_message->headers;

    while (p_http_message->headers) {
      p = p_http_message->headers->next;

      free(p_http_message->headers->name);
      free(p_http_message->headers->value);
      free(p_http_message->headers);
      
      p_http_message->headers = p;
    }
    
    free(p_http_message->method);
    free(p_http_message->request_uri);
    free(p_http_message->major_version);
    free(p_http_message->minor_version);
  } 

  free(p_http_message);

  p_http_message = NULL;
}
