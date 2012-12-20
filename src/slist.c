#include <assert.h>
#include <stdlib.h>

#include "slist.h"


void
ow_slist_free(struct ow_slist* p_slist)
{
  struct ow_slist* p;
  
  while ((p = p_slist)) {
    p_slist = p_slist->next;
    free(p);
  }
}


struct ow_slist*
ow_slist_insert(struct ow_slist* p_slist, void* p_data)
{
  struct ow_slist* p = malloc(sizeof(*p));
  if (!p) goto _fail;

  p->data = p_data;
  p->next = p_slist;

  return p;

_fail:
  return NULL;
}


struct ow_slist*
ow_slist_remove(struct ow_slist *p_slist, void* p_data)
{
  assert(NULL != p_slist);
  
  struct ow_slist *p = p_slist;
  struct ow_slist *prev = NULL;

  while (p && p->data != p_data) {
    prev = p;
    p = p->next;
  }

  if (p) {
    if (prev)
      prev->next = p->next;
    else
      p_slist = p->next;

    free(p);
  }

  return p_slist;
}


struct ow_slist*
ow_slist_remove_node(struct ow_slist *p_slist, struct ow_slist* p_node)
{
  assert(NULL != p_slist);
  assert(NULL != p_node);
  
  struct ow_slist *p = p_slist;
  struct ow_slist *prev = NULL;

  while (p && p != p_node) {
    prev = p;
    p = p->next;
  }

  if (p) {
    if (prev) prev->next = p->next;
    free(p);
  }

  return p_slist;
}


_Bool
ow_slist_is_empty(struct ow_slist *p_slist)
{
  return ow_slist_length(p_slist) == 0;
}


unsigned int
ow_slist_length(struct ow_slist *p_slist)
{
  unsigned int length = 0;

  while (p_slist) {
    p_slist = p_slist->next;
    length++;
  }

  return length;
}
