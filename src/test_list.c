#include <stdio.h>
#include <stdlib.h>

#include "slist.h"

inline dump(struct ow_slist *p_list)
{
  struct ow_slist_node *p = p_list->head;
  
  while (p) {
    printf("%s\n", (char *)p->data);
    p = p->next;
  }
}

void main()
{

  struct ow_slist *list = ow_slist_create();

  ow_slist_insert(list, "Hello");
  ow_slist_insert(list, "World");
  struct ow_slist_node *x = ow_slist_insert(list, "FART");

  ow_slist_remove(list, "Hello");
  
  dump(list);

  ow_slist_free(list);
}
