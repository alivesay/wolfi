#include "rfc3986.h"

int main(void)
{
  ow_rfc3986_uri_t *uri;
  uri = ow_rfc3986_uri_create("http:/test.com");
  ow_rfc3986_uri_free(uri);
}

