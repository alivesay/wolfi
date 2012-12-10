#include <stdlib.h>
#include <check.h>
#include "rfc3986.h"

#define TEST_RFC3986_URI_FIELD(field, expected) \
  fail_unless(strcmp(uri->field, expected) == 0, #field " field check failed");

START_TEST (test_rfc3986_uri_parse)
{
  const char *buffer = "http://user:pass@example.com:8080/a/b/c/d/e.ext?key=value#top";
  rfc3986_uri_t *uri = rfc3986_uri_parse(buffer);

  TEST_RFC3986_URI_FIELD(scheme,   "http");
  TEST_RFC3986_URI_FIELD(userinfo, "user:pass");
  TEST_RFC3986_URI_FIELD(host,     "example.com");
  TEST_RFC3986_URI_FIELD(port,     "8080");
  TEST_RFC3986_URI_FIELD(path,     "/a/b/c/d/e.ext");
  TEST_RFC3986_URI_FIELD(query,    "key=value");
  TEST_RFC3986_URI_FIELD(fragment, "top");

  rfc3986_uri_free(uri);
}
END_TEST

Suite* rfc3986_suite(void)
{
  Suite *s = suite_create("rfc3986");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_rfc3986_uri_parse);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void)
{
  int fail_count;
  Suite *s = rfc3986_suite();
  SRunner *sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);

  fail_count = srunner_ntests_failed(sr);

  srunner_free(sr);
  
  return (fail_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
