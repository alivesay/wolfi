#ifdef UNIT_TEST

#include <stdlib.h>
#include <check.h>
#include "uri.h"

#define TEST_URI_FIELD(field, expected) \
  fail_unless(uri->field == NULL || strcmp(uri->field, expected) == 0, #field " field check failed");

START_TEST (test_uri_create_0000)
{
  const char *buffer = "http://user:pass@example.com:8080/a/b/c/d/e.ext?key=value#top";
  struct ow_uri *uri = ow_uri_create(buffer);

  TEST_URI_FIELD(scheme,   "http");
  TEST_URI_FIELD(userinfo, "user:pass");
  TEST_URI_FIELD(host,     "example.com");
  TEST_URI_FIELD(port,     "8080");
  TEST_URI_FIELD(path,     "/a/b/c/d/e.ext");
  TEST_URI_FIELD(query,    "key=value");
  TEST_URI_FIELD(fragment, "top");

  ow_uri_free(uri);
}
END_TEST

START_TEST (test_uri_create_0001)
{
  const char *buffer = "/a/b/c/d/e/f/g";
  struct ow_uri *uri = ow_uri_create(buffer);

  TEST_URI_FIELD(scheme,   "");
  TEST_URI_FIELD(host,     "");
  TEST_URI_FIELD(port,     ""); 
  TEST_URI_FIELD(path,     "/a/b/c/d/e/f/g");
  TEST_URI_FIELD(query,    "");
  TEST_URI_FIELD(fragment, "");

  ow_uri_free(uri);
}
END_TEST

START_TEST (test_uri_create_0002)
{
  const char *buffer = "file:///path/to/a/share/doc.txt";
  struct ow_uri *uri = ow_uri_create(buffer);

  TEST_URI_FIELD(scheme,   "file");
  TEST_URI_FIELD(userinfo, "");
  TEST_URI_FIELD(host,     "");
  TEST_URI_FIELD(port,     "");
  TEST_URI_FIELD(path,     "/path/to/a/share/doc.txt");
  TEST_URI_FIELD(query,    "");
  TEST_URI_FIELD(fragment, "");

  ow_uri_free(uri);
}
END_TEST

START_TEST (test_uri_create_0003)
{
  const char *buffer = "https://test.example.com/a/b/c/d/e/f/g/h.i?k=v&a=b&c=d&1=2&3=4#fragment";
  struct ow_uri *uri = ow_uri_create(buffer);

  TEST_URI_FIELD(scheme,   "https");
  TEST_URI_FIELD(userinfo, "");
  TEST_URI_FIELD(host,     "test.example.com");
  TEST_URI_FIELD(port,     "");
  TEST_URI_FIELD(path,     "/a/b/c/d/e/f/g/h.i");
  TEST_URI_FIELD(query,    "k=v&a=b&c=d&1=2&3=4");
  TEST_URI_FIELD(fragment, "fragment");

  ow_uri_free(uri);
}
END_TEST

Suite* rfc3986_suite(void)
{
  Suite *s = suite_create("uri");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_uri_create_0000);
  tcase_add_test(tc_core, test_uri_create_0001);
  tcase_add_test(tc_core, test_uri_create_0002);
  tcase_add_test(tc_core, test_uri_create_0003);
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
