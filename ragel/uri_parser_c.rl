%%{
  machine uri_parser_c;

  action mark       { mark = fpc; }
  action scheme     { OW_URI_SET_FIELD(scheme,   mark, fpc - mark); }
  action userinfo   { OW_URI_SET_FIELD(userinfo, mark, fpc - mark); }
  action host       { OW_URI_SET_FIELD(host,     mark, fpc - mark); }
  action port       { OW_URI_SET_FIELD(port,     mark, fpc - mark); }
  action path       { OW_URI_SET_FIELD(path,     mark, fpc - mark); }
  action query      { OW_URI_SET_FIELD(query,    mark, fpc - mark); }
  action fragment   { OW_URI_SET_FIELD(fragment, mark, fpc - mark); }
  
  include uri_parser 'uri_parser.rl';

  main := URI_reference;
}%%

#include <stdlib.h>
#include <string.h>

#include "uri.h"

%% write data;
 
#define OW_URI_SET_FIELD(field, offset, len)                 \
  do {                                                       \
    if (uri->field) free(uri->field);                        \
    uri->field = malloc((len) * sizeof(*uri->field) + 1);    \
    memcpy(uri->field, offset, (len) * sizeof(*uri->field)); \
    uri->field[len] = '\0';                                  \
  } while(0)


struct ow_uri* ow_uri_create(const char* p_buffer)
{
  int cs;
  const char *p, *pe, *mark, *eof;
  struct ow_uri *uri;
  
  mark = p = p_buffer;
  eof = pe = p + strlen(p);

  uri = calloc(1, sizeof(*uri));
  if (!uri) goto _fail;

  %% write init;
  %% write exec;

  return uri;

_fail:
  ow_uri_free(uri);
  return NULL;
}

void ow_uri_free(struct ow_uri *p_uri)
{
  free(p_uri->scheme);
  free(p_uri->userinfo);
  free(p_uri->host);
  free(p_uri->port);
  free(p_uri->path);
  free(p_uri->query);
  free(p_uri->fragment);
  free(p_uri);

  p_uri = NULL;
}


