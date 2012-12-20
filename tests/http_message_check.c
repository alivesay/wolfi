#ifdef UNIT_TEST

#include <stdlib.h>
#include <check.h>

#include "ow_http_message.h"

#define TEST_HTTP_MESSAGE_FIELD(field, expected) \
  fail_unless(http_message->field == NULL || strcmp(http_message->field, expected) == 0, #field " field check failed");

START_TEST (test_http_message_create_0000)
{ 
  const char *buffer = "GET /index.html HTTP/1.1\r\n" \
                       "Host: example.com\r\n" \
                       "Accept-Language: en-us\r\n" \
                       "Accept: text/html\r\n" \
                       "User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux; x86_64; rv:14.0)\r\n" \
                       "Connection: keep-alive\r\n\r\n";

  struct ow_http_message *http_message = ow_http_message_create(buffer);

  TEST_HTTP_MESSAGE_FIELD(method,         "GET");
  TEST_HTTP_MESSAGE_FIELD(request_uri,    "/index.html");
  TEST_HTTP_MESSAGE_FIELD(major_version,  "1");
  TEST_HTTP_MESSAGE_FIELD(minor_version,  "1");

  ow_http_message_free(http_message);
}
END_TEST

Suite* rfc3986_suite(void)
{
  Suite *s = suite_create("http_message");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_http_message_create_0000);
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
