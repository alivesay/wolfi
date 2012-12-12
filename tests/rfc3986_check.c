#ifdef UNIT_TEST

#include <stdlib.h>
#include <check.h>
#include "rfc3986.h"

#define TEST_RFC3986_URI_FIELD(field, expected) \
  fail_unless(uri->field == NULL || strcmp(uri->field, expected) == 0, #field " field check failed");

START_TEST (test_rfc3986_uri_parse_0000)
{
  const char *buffer = "http://user:pass@example.com:8080/a/b/c/d/e.ext?key=value#top";
  ow_rfc3986_uri_t *uri = ow_rfc3986_uri_parse(buffer);

  TEST_RFC3986_URI_FIELD(scheme,   "http");
  TEST_RFC3986_URI_FIELD(userinfo, "user:pass");
  TEST_RFC3986_URI_FIELD(host,     "example.com");
  TEST_RFC3986_URI_FIELD(port,     "8080");
  TEST_RFC3986_URI_FIELD(path,     "/a/b/c/d/e.ext");
  TEST_RFC3986_URI_FIELD(query,    "key=value");
  TEST_RFC3986_URI_FIELD(fragment, "top");

  ow_rfc3986_uri_free(uri);
}
END_TEST

START_TEST (test_rfc3986_uri_parse_0001)
{
  const char *buffer = "/a/b/c/d/e/f/g";
  ow_rfc3986_uri_t *uri = ow_rfc3986_uri_parse(buffer);

  TEST_RFC3986_URI_FIELD(scheme,   "");
  TEST_RFC3986_URI_FIELD(host,     "");
  TEST_RFC3986_URI_FIELD(port,     ""); 
  TEST_RFC3986_URI_FIELD(path,     "/a/b/c/d/e/f/g");
  TEST_RFC3986_URI_FIELD(query,    "");
  TEST_RFC3986_URI_FIELD(fragment, "");

  ow_rfc3986_uri_free(uri);
}
END_TEST

START_TEST (test_rfc3986_uri_parse_0002)
{
  const char *buffer = "file:///path/to/a/share/doc.txt";
  ow_rfc3986_uri_t *uri = ow_rfc3986_uri_parse(buffer);

  TEST_RFC3986_URI_FIELD(scheme,   "file");
  TEST_RFC3986_URI_FIELD(userinfo, "");
  TEST_RFC3986_URI_FIELD(host,     "");
  TEST_RFC3986_URI_FIELD(port,     "");
  TEST_RFC3986_URI_FIELD(path,     "/path/to/a/share/doc.txt");
  TEST_RFC3986_URI_FIELD(query,    "");
  TEST_RFC3986_URI_FIELD(fragment, "");

  ow_rfc3986_uri_free(uri);
}
END_TEST

START_TEST (test_rfc3986_uri_parse_0003)
{
  const char *buffer = "https://test.example.com/a/b/c/d/e/f/g/h.i?k=v&a=b&c=d&1=2&3=4#fragment";
  ow_rfc3986_uri_t *uri = ow_rfc3986_uri_parse(buffer);

  TEST_RFC3986_URI_FIELD(scheme,   "https");
  TEST_RFC3986_URI_FIELD(userinfo, "");
  TEST_RFC3986_URI_FIELD(host,     "test.example.com");
  TEST_RFC3986_URI_FIELD(port,     "");
  TEST_RFC3986_URI_FIELD(path,     "/a/b/c/d/e/f/g/h.i");
  TEST_RFC3986_URI_FIELD(query,    "k=v&a=b&c=d&1=2&3=4");
  TEST_RFC3986_URI_FIELD(fragment, "fragment");

  ow_rfc3986_uri_free(uri);
}
END_TEST

Suite* rfc3986_suite(void)
{
  Suite *s = suite_create("rfc3986");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_rfc3986_uri_parse_0000);
  tcase_add_test(tc_core, test_rfc3986_uri_parse_0001);
  tcase_add_test(tc_core, test_rfc3986_uri_parse_0002);
  tcase_add_test(tc_core, test_rfc3986_uri_parse_0003);
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

#endif // UNIT_TEST
