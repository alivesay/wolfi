#include "rfc3986.h"

int main(void)
{
  rfc3986_uri_t *uri;
  uri = rfc3986_uri_parse("http:/test.com");
  rfc3986_uri_free(uri);
}

