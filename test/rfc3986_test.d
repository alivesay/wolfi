import rfc3986;
import std.string: toStringz;

unittest
{
  string uri = "http://username:password@test.com:8080/x/y/z/index.php?i=j&k=l#top";
  const char* uri_z = toStringz(uri);
  
  rfc3986_index_t rfc3986_i;
  rfc3986_uri_t rfc3986_uri;
 
  rfc3986_build_index(uri_z, &rfc3986_i);
  rfc3986_uri_pack(&rfc3986_i, &rfc3986_uri);
 
  assert(rfc3986_uri.scheme == "http");
  assert(rfc3986_uri.userinfo == "username:password");
  assert(rfc3986_uri.host == "test.com");
  assert(rfc3986_uri.port == "8080");
  assert(rfc3986_uri.path == "/x/y/z/index.php");
  assert(rfc3986_uri.query == "i=j&k=l");
  assert(rfc3986_uri.fragment == "top");
}

unittest
{
  string uri = "/a/b/c/d";
  const char* uri_z = toStringz(uri);
  
  rfc3986_index_t rfc3986_i;
  rfc3986_uri_t rfc3986_uri;
 
  rfc3986_build_index(uri_z, &rfc3986_i);
  rfc3986_uri_pack(&rfc3986_i, &rfc3986_uri);
 
  assert(rfc3986_uri.scheme == "");
  assert(rfc3986_uri.userinfo == "");
  assert(rfc3986_uri.host == "");
  assert(rfc3986_uri.port == "");
  assert(rfc3986_uri.path == "/a/b/c/d");
  assert(rfc3986_uri.query == "");
  assert(rfc3986_uri.fragment == "");
}

