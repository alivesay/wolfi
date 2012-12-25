%%{
  machine http_request_parser_c;
  
  action mark          { mark = fpc; }
  action method        { OW_HTTP_REQUEST_SET_FIELD(method,        mark, fpc - mark); }
  action request_uri   { OW_HTTP_REQUEST_SET_FIELD(request_uri,   mark, fpc - mark); }
  action major_version { OW_HTTP_REQUEST_SET_FIELD(major_version, mark, fpc - mark); }
  action minor_version { OW_HTTP_REQUEST_SET_FIELD(minor_version, mark, fpc - mark); }
  action header_name
  { 
    prev_header = p_http_request->headers;
    p_http_request->headers = calloc(1, sizeof(*http_request->headers));
    if (!p_http_request->headers) {
      OW_BUILD_LOG_STR("OW_HTTP_REQUEST_SET_FIELD malloc() failed")); 
      exit(EXIT_FAILURE);
    }

    OW_HTTP_REQUEST_SET_FIELD(headers->name, fpc, fpc - mark);

    http_request->headers->next = prev_header;
  }
  action header_value { OW_HTTP_REQUEST_SET_FIELD(headers->value, fpc, fpc - mark); }

  include http_request_parser 'ow_http_request_parser.rl';

  main := HTTP_request;
}%%

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ow_common.h"
#include "ow_http_request.h"
#include "ow_log.h"

%% write data;


// TODO: make field alloc func
#define OW_HTTP_REQUEST_SET_FIELD(field, offset, len)                          \
  do {                                                                         \
    if (p_http_request->field) free(p_http_request->field);                        \
    p_http_request->field = malloc((len) * sizeof(*p_http_request->field) + 1);    \
    if (!p_http_request->field) {                                                \
      ow_log(OWLogLevel_EMERG,                                                 \
             OW_LOG_BUILD_STR("OW_HTTP_REQUEST_SET_FIELD malloc() failed"));   \
      exit(EXIT_FAILURE);                                                      \
    }                                                                          \
    memcpy(p_http_request->field, offset, (len) * sizeof(*p_http_request->field)); \
    p_http_request->field[len] = '\0';                                           \
  } while(0)


struct ow_http_request*
ow_http_request_parse(struct ow_http_request *const p_http_request,
                      const char* p_buffer)
{
  int cs;
  const char *p, *pe, *mark, *eof;
  struct ow_http_request_header *prev_header;

  mark = p = p_buffer;
  eof = pe = p + strlen(p);

  %% write init;
  %% write exec;

  return p_http_request;
}



