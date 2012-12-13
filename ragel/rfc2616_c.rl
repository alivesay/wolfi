%%{
  machine rfc2616_c;
  
  action mark { printf(""); mark = fpc; }
  action pchar { printf("%c", fc); }
  action test { printf("test\n");}
  action method{ printf("method:"); fwrite(mark, fpc - mark, 1, stdout); printf("\n");}
  action request_uri{ printf("request_uri:"); fwrite(mark, fpc - mark, 1, stdout); printf("\n");}
  action major_version{ printf("http_major_version:"); fwrite(mark, fpc - mark, 1, stdout); printf("\n");}
  action minor_version{ printf("http_minor_version:"); fwrite(mark, fpc - mark, 1, stdout); printf("\n");}
  action header_name {
//    p_index = malloc(
  
  printf("header_name:"); fwrite(mark, fpc - mark, 1, stdout); printf("\n");}
  action header_value { printf("header_value:"); fwrite(mark, fpc - mark, 1, stdout); printf("\n");}
  action header_set{}

  include rfc2616 'rfc2616.rl';

  main := HTTP_message;
}%%

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rfc3986.h"

%% write data;

typedef struct {
  const char *name;    size_t name_len;
  const char *value;   size_t value_len;

  struct ow_rfc2616_header_index_t *next;

} ow_rfc2616_header_index_t;

//#define OW_RFC2616_HEADER_INDEX_SET(

typedef struct {
  const char *method;           size_t scheme_len;
  const char *request_uri;      size_t request_uri_len;
  const char *major_version;    size_t major_version_len;
  const char *minor_version;    size_t minor_version_len;

  ow_rfc2616_header_index_t *headers;

} ow_rfc2616_index_t;

#define OW_RFC2616_INDEX_SET_KEY(key, offset, end) \
  p_index->key       = offset; \
  p_index->key##_len = end - offset;


int main()
{
  const char *request = "GET /index.html HTTP/1.0\r\n" \
                        "Host: example.com\r\n" \
                        "Accept-Language: en-us\r\n" \
                        "Accept: text/html\r\n" \
                        "User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux; x86_64; rv:14.0)\r\n" \
                        "Connection: keep-alive\r\n\r\n";

  int cs;
  const char *p, *pe, *mark, *eof;

  p = request;
  mark = p;
  eof = pe = p + strlen(p);

  %% write init;
  %% write exec;
}
