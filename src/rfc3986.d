module rfc3986;

struct rfc3986_uri_t {
  string scheme;
  string userinfo;
  string host;
  string port;
  string path;
  string query;
  string fragment;
}

void rfc3986_uri_pack(rfc3986_index_t* p_rfc3986_i, rfc3986_uri_t* p_rfc3986_uri) 
{
  p_rfc3986_uri.scheme   = p_rfc3986_i.scheme   [0..p_rfc3986_i.scheme_len].idup;
  p_rfc3986_uri.userinfo = p_rfc3986_i.userinfo [0..p_rfc3986_i.userinfo_len].idup;
  p_rfc3986_uri.host     = p_rfc3986_i.host     [0..p_rfc3986_i.host_len].idup;
  p_rfc3986_uri.port     = p_rfc3986_i.port     [0..p_rfc3986_i.port_len].idup;
  p_rfc3986_uri.path     = p_rfc3986_i.path     [0..p_rfc3986_i.path_len].idup;
  p_rfc3986_uri.query    = p_rfc3986_i.query    [0..p_rfc3986_i.query_len].idup;
  p_rfc3986_uri.fragment = p_rfc3986_i.fragment [0..p_rfc3986_i.fragment_len].idup;
}

extern (C):

struct rfc3986_index_t {
  const char *scheme;        size_t scheme_len;
  const char *userinfo;      size_t userinfo_len;
  const char *host;          size_t host_len;
  const char *port;          size_t port_len;
  const char *path;          size_t path_len;
  const char *query;         size_t query_len;
  const char *fragment;      size_t fragment_len;
};

void rfc3986_build_index(const char* p_buffer, rfc3986_index_t *p_rfc3986_i);
