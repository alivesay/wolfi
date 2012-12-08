%%{
  machine rfc3986_c;

  action mark       { mark = fpc; }
  action scheme     { RFC3986_SET_INDEX(scheme,   mark, fpc); }
  action userinfo   { RFC3986_SET_INDEX(userinfo, mark, fpc); }
  action host       { RFC3986_SET_INDEX(host,     mark, fpc); }
  action port       { RFC3986_SET_INDEX(port,     mark, fpc); }
  action path       { RFC3986_SET_INDEX(path,     mark, fpc); }
  action query      { RFC3986_SET_INDEX(query,    mark, fpc); }
  action fragment   { RFC3986_SET_INDEX(fragment, mark, fpc); }
  
  include rfc3986 'rfc3986.rl';

  main := URI_reference;
}%%

#include <stdlib.h>
#include <string.h>

%% write data;

typedef struct {
  const char *scheme;        size_t scheme_len;
  const char *userinfo;      size_t userinfo_len;
  const char *host;          size_t host_len;
  const char *port;          size_t port_len;
  const char *path;          size_t path_len;
  const char *query;         size_t query_len;
  const char *fragment;      size_t fragment_len;
} rfc3986_index_t;

#define RFC3986_SET_INDEX(key, offset, end) \
  p_rfc3986_i->key       = offset; \
  p_rfc3986_i->key##_len = end - offset; 
 
void rfc3986_build_index(const char* p_buffer, rfc3986_index_t *p_rfc3986_i)
{
  int cs;
  const char *p, *pe, *mark, *eof;
  
  p = p_buffer;
  mark = p;
  eof = pe = p + strlen(p);

  %% write init;
  %% write exec;
}
