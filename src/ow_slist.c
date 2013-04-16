#include <assert.h>
#include <stdlib.h>

#include "ow_common.h"
#include "ow_slist.h"


void
ow_slist_free(struct ow_slist *p_slist)
{
  struct ow_slist *p;
  
  while ((p = p_slist)) {
    p_slist = p_slist->next;
    free(p);
  }
}


void
ow_slist_free_custom(struct ow_slist *p_slist,
                     const OWFreeFunc p_free_func)
{
  assert(NULL != p_free_func);

  struct ow_slist *p;
  
  while ((p = p_slist)) {
    p_slist = p_slist->next;
    p_free_func(p->data);
    free(p);
  }
}


struct ow_slist*
ow_slist_insert(struct ow_slist *const p_slist,
                void *const p_data)
{
  struct ow_slist *p;

  OW_MALLOC(p, sizeof *p);
  if (!p) goto _error;

  p->data = p_data;
  p->next = p_slist;

  return p;

_error:
  return NULL;
}


struct ow_slist*
ow_slist_insert_end(struct ow_slist *const p_slist,
                    void *const p_data)
{
  struct ow_slist *p;
  struct ow_slist *last;

  OW_MALLOC(p, sizeof *p);
  if (!p) goto _error;

  last = p_slist;

  p->data = p_data;
  p->next = NULL;
 
  if (p_slist) {
    while (last->next) last = last->next;
    last->next = p;
    
    return p_slist;
  }
 
  return p;

_error:
  return NULL;
}


struct ow_slist*
ow_slist_remove(struct ow_slist *p_slist,
                const void *const p_data)
{
  struct ow_slist *p;
  struct ow_slist *prev;

  p = p_slist;
  prev = NULL;

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
ow_slist_remove_custom(struct ow_slist *p_list,
                       const void *const p_data,
                       const OWCompareFunc p_compare_func)
{
  struct ow_slist *p;
  struct ow_slist *prev;

  p = p_slist;
  prev = NULL;

  while (p && p_compare_func(p->data, p_data) != 0) {
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
ow_slist_remove_node(struct ow_slist *p_slist,
                     const struct ow_slist *p_node)
{
  struct ow_slist *p;
  struct ow_slist *prev;

  p = p_slist;
  prev = NULL;

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


struct ow_slist*
ow_slist_find(struct ow_slist *p_slist,
              const void *const p_data)
{
  while (p_slist && p_slist->data != p_data)
    p_slist = p_slist->next;

  return p_slist;
}


struct ow_slist*
ow_slist_find_custom(struct ow_slist *p_slist,
                     const void *const p_data,
                     const OWCompareFunc p_compare_func)
{
  assert(NULL != p_compare_func);

  while (p_slist && p_compare_func(p_slist->data, p_data) != 0)
    p_slist = p_slist->next;

  return p_slist;
}


bool
ow_slist_is_empty(const struct ow_slist *const p_slist)
{
  return ow_slist_length(p_slist) == 0;
}


uint32_t
ow_slist_length(const struct ow_slist *p_slist)
{
  unsigned int length;

  length = 0;

  while (p_slist) {
    p_slist = p_slist->next;
    length++;
  }

  return length;
}
