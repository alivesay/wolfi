#ifdef UNIT_TEST

#include <stdlib.h>
#include <check.h>

#include "ow_slist.h"

void array_match_test(char *p_array, unsigned int p_array_len, struct ow_slist *p_slist)
{
  for(unsigned int i = 0; i < p_array_len; i++, p_slist = p_slist->next)
    fail_unless(*(char*)p_slist->data == p_array[i], "p_slist does not match array");
}

START_TEST (test_slist_0000)
{ 
  struct ow_slist *l = NULL;
  char a = 'A', b = 'B', c = 'C', d = 'D', e = 'E';
  char x[5] = { 'E', 'D', 'C', 'B', 'A' };

  l = ow_slist_insert(l, &a);  
  l = ow_slist_insert(l, &b);
  l = ow_slist_insert(l, &c);
  l = ow_slist_insert(l, &d);
  l = ow_slist_insert(l, &e);

  array_match_test(x, 5, l);
}
END_TEST

START_TEST (test_slist_0001)
{ 
  struct ow_slist *l = NULL;
  char a = 'A', b = 'B', c = 'C', d = 'D', e = 'E';
  char x[5] = { 'A', 'B', 'C', 'D', 'E' };

  l = ow_slist_insert_end(l, &a);  
  l = ow_slist_insert_end(l, &b);
  l = ow_slist_insert_end(l, &c);
  l = ow_slist_insert_end(l, &d);
  l = ow_slist_insert_end(l, &e);

  array_match_test(x, 5, l);
}
END_TEST


Suite* slist_suite(void)
{
  Suite *s = suite_create("slist");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_slist_0000);
  tcase_add_test(tc_core, test_slist_0001);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void)
{
  int fail_count;
  Suite *s = slist_suite();
  SRunner *sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);

  fail_count = srunner_ntests_failed(sr);

  srunner_free(sr);
  
  return (fail_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

#endif // UNIT_TEST
