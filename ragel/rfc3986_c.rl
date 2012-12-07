%%{
  machine rfc3986_c;

  action mark       { mark = fpc; }
  action scheme     { RFC3986_SET_INDEX(scheme,   mark, fpc); }
  action userinfo   { RFC3986_SET_INDEX(userinfo, mark, fpc); }
  action host       { RFC3986_SET_INDEX(host,     mark, fpc); }
  action path       { RFC3986_SET_INDEX(path,     mark, fpc); }
  action query      { RFC3986_SET_INDEX(query,    mark, fpc); }
  action fragment   { RFC3986_SET_INDEX(fragment, mark, fpc); }
  
  include rfc3986 'rfc3986.rl';

  main := URI_reference;
}%%

#include <stdio.h>
#include <string.h>

%% write data;

typedef struct {
  char *scheme;        size_t scheme_len;
  char *userinfo;      size_t userinfo_len;
  char *host;          size_t host_len;
  char *path;          size_t path_len;
  char *query;         size_t query_len;
  char *fragment;      size_t fragment_len;
} rfc3986_index_t;

#define RFC3986_SET_INDEX(key, offset, end) \
  p_rfc3986_i->key       = offset; \
  p_rfc3986_i->key##_len = end - offset; 

void parse_rfc3986(char *p_buffer, size_t p_buflen, rfc3986_index_t *p_rfc3986_i) {
  int cs;
  char *p, *pe, *mark, *eof;
  
  p = p_buffer;
  mark = p;
  eof = pe = p + p_buflen;

  %% write init;
  %% write exec;
}

#define RFC3986_DUMP_KEY(name) \
  printf(#name "->["); fwrite(p_rfc3986_i->name, sizeof(char), p_rfc3986_i->name##_len, stdout); printf("]\n");
  
void rfc3986_dump(rfc3986_index_t *p_rfc3986_i) {
  RFC3986_DUMP_KEY(scheme);
  RFC3986_DUMP_KEY(userinfo);
  RFC3986_DUMP_KEY(host);
  RFC3986_DUMP_KEY(path);
  RFC3986_DUMP_KEY(query);
  RFC3986_DUMP_KEY(fragment);
  fflush(stdout);
}

int main() {
  char *uri = "http://admin:pass1234@test.com/index.php?store=cheese#inventory";

  rfc3986_index_t rfc3986_index = {0};

  parse_rfc3986(uri, strlen(uri), &rfc3986_index);

  rfc3986_dump(&rfc3986_index);

  return 0;
}
