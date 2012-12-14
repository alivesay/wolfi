#include "uri.h"

int main(void)
{
  struct ow_uri *uri;
  uri = ow_uri_create("http:/test.com");
  ow_uri_free(uri);
}

