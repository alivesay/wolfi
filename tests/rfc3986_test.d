import rfc3986;
import std.string: toStringz;

mixin template rfc3986_test_uri(alias uri,
                                alias scheme,
                                alias userinfo,
                                alias host,
                                alias port,
                                alias path,
                                alias query,
                                alias fragment)
{
  unittest
  {
    const char* uri_z = toStringz(uri);
    
    rfc3986_index_t rfc3986_i;
    rfc3986_uri_t rfc3986_uri;
   
    rfc3986_build_index(uri_z, &rfc3986_i);
    rfc3986_uri_pack(&rfc3986_i, &rfc3986_uri);
   
    assert(rfc3986_uri.scheme   == scheme);
    assert(rfc3986_uri.userinfo == userinfo);
    assert(rfc3986_uri.host     == host);
    assert(rfc3986_uri.port     == port);
    assert(rfc3986_uri.path     == path);
    assert(rfc3986_uri.query    == query);
    assert(rfc3986_uri.fragment == fragment);
  }
}


mixin rfc3986_test_uri!(
  "http://username:password@test.com:8080/x/y/z/index.php?i=j&k=l#top",
  "http",
  "username:password",
  "test.com",
  "8080",
  "/x/y/z/index.php",
  "i=j&k=l",
  "top"
);

mixin rfc3986_test_uri!(
  "/a/b/c/d",
  "",
  "",
  "",
  "",
  "/a/b/c/d",
  "",
  ""
);

mixin rfc3986_test_uri!(
  "/a/b/c/d/e.txt?key=value/;#fragment",
  "",
  "",
  "",
  "",
  "/a/b/c/d/e.txt",
  "key=value/;",
  "fragment"
);

mixin rfc3986_test_uri!(
  "http://a.b.c.d.e.f.g:12345/a/b/c/d/e/f/g/",
  "http",
  "",
  "a.b.c.d.e.f.g",
  "12345",
  "/a/b/c/d/e/f/g/",
  "",
  ""
);
