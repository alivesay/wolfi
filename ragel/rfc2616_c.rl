%%{
  machine rfc2616_c;
  
  action mark { printf("MARK!\n"); mark = fpc; }
  action pchar { printf("%c", fc); }
  action request_uri{ printf("request_uri:"); fwrite(mark, fpc - mark, 1, stdout); printf("\n");}
  action method{ printf("method:"); fwrite(mark, fpc - mark, 1, stdout); printf("\n");}
  action major_version{ printf("http_major_version:"); fwrite(mark, fpc - mark, 1, stdout); printf("\n");}
  action minor_version{ printf("http_minor_version:"); fwrite(mark, fpc - mark, 1, stdout); printf("\n");}


  include rfc2616 'rfc2616.rl';

  main := HTTP_message;
}%%

#include <stdio.h>
#include <string.h>
#include "rfc3986.h"

%% write data;

typedef struct {
  const char *method;           size_t scheme_len;
  const char *status_code;      size_t status_code_len;
  const char *major_version;    size_t major_version_len;
  const char *minor_version;    size_t minor_version_len;
  const ow_rfc3986_uri_t uri;   size_t uri_len;
} ow_rfc2616_index_t;

int main()
{
  const char *request = "GET /index.html HTTP/1.0\r\n" \
                        "Host: example.com" \
                        "User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux; x86_64; rv:14.0)" \
                        "Accept: text/html" \
                        "Accept-Language: en-us" \
                        "Connection: keep-alive";

  int cs;
  const char *p, *pe, *mark, *eof;

  p = request;
  mark = p;
  eof = pe = p + strlen(p);

  %% write init;
  %% write exec;
}
