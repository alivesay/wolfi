#include <stdio.h>
#include <stdlib.h>

#include "slist.h"

static inline void dump(struct ow_slist *p_slist)
{
  while (p_slist) {
    printf("%s\n", (char *)p_slist->data);
    p_slist = p_slist->next;
  }
}

int main()
{
  struct ow_slist *list = NULL;

  printf("empty?: %d\n", ow_slist_is_empty(list));

  list = ow_slist_insert(list, "Hello");
  list = ow_slist_insert(list, "World");
  list = ow_slist_insert(list, "XXXX");

  list = ow_slist_remove(list, "XXXX");
  
  printf("empty?: %d\n", ow_slist_is_empty(list));

  dump(list);

  ow_slist_free(list);

  return 0;
}
