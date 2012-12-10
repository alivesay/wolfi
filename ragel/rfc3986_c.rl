%%{
  machine rfc3986_c;

  action mark       { mark = fpc; }
  action scheme     { RFC3986_INDEX_SET_KEY(scheme,   mark, fpc); }
  action userinfo   { RFC3986_INDEX_SET_KEY(userinfo, mark, fpc); }
  action host       { RFC3986_INDEX_SET_KEY(host,     mark, fpc); }
  action port       { RFC3986_INDEX_SET_KEY(port,     mark, fpc); }
  action path       { RFC3986_INDEX_SET_KEY(path,     mark, fpc); }
  action query      { RFC3986_INDEX_SET_KEY(query,    mark, fpc); }
  action fragment   { RFC3986_INDEX_SET_KEY(fragment, mark, fpc); }
  
  include rfc3986 'rfc3986.rl';

  main := URI_reference;
}%%

#include <stdlib.h>
#include <string.h>
#include "rfc3986.h"

%% write data;

#define RFC3986_INDEX_SET_KEY(key, offset, end) \
  p_index->key       = offset; \
  p_index->key##_len = end - offset; 
 
void rfc3986_index_build(rfc3986_index_t *p_index, const char* p_buffer)
{
  int cs;
  const char *p, *pe, *mark, *eof;
  
  p = p_buffer;
  mark = p;
  eof = pe = p + strlen(p);

  %% write init;
  %% write exec;
}

void rfc3986_uri_free(rfc3986_uri_t *p_uri)
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

#define RFC3986_URI_SET_FIELD(field, index, uri) \
  if (index.field) { \
    uri->field = malloc(index.field##_len * sizeof(*index.field) + 1); \
    memcpy(uri->field, index.field, index.field##_len * sizeof(*index.field)); \
    uri->field[index.field##_len] = '\0'; \
  } 

rfc3986_uri_t* rfc3986_uri_parse(const char* p_buffer)
{
  rfc3986_index_t index;
  memset(&index, 0, sizeof(index));

  rfc3986_uri_t *uri = malloc(sizeof(*uri)); 
  memset(uri, 0, sizeof(*uri));

  // TODO: need error handling somewhere
  rfc3986_index_build(&index, p_buffer);

  RFC3986_URI_SET_FIELD(scheme,   index, uri); 
  RFC3986_URI_SET_FIELD(userinfo, index, uri); 
  RFC3986_URI_SET_FIELD(host,     index, uri); 
  RFC3986_URI_SET_FIELD(port,     index, uri); 
  RFC3986_URI_SET_FIELD(path,     index, uri); 
  RFC3986_URI_SET_FIELD(query,    index, uri); 
  RFC3986_URI_SET_FIELD(fragment, index, uri); 

  return uri;
}
