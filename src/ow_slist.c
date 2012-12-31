#include <assert.h>
#include <stdlib.h>

#include "ow_log"
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
                     OWFreeFunc const p_free_func)
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
  
  p = malloc(sizeof *p);
  if (!p) goto _malloc_failed;

  p->data = p_data;
  p->next = p_slist;

  return p;

_malloc_failed:
  ow_log(OWLogLevel_EMERG, OW_LOG_BUILD_STR("malloc() failed"));
  return NULL;
}


struct ow_slist*
ow_slist_insert_end(struct ow_slist *const p_slist,
                    void *const p_data)
{
  struct ow_slist *p;
  struct ow_slist *last;

  p = malloc(sizeof *p);
  if (!p) goto _malloc_failed;

  last = p_slist;

  p->data = p_data;
  p->next = NULL;
 
  if (p_slist) {
    while (last->next) last = last->next;
    last->next = p;
    
    return p_slist;
  }
 
  return p;

_malloc_failed:
  ow_log(OWLogLevel_EMERG, OW_LOG_BUILD_STR("malloc() failed"));
  return NULL;
}


struct ow_slist*
ow_slist_remove(struct ow_slist *p_slist,
                void const *const p_data)
{
  struct ow_slist *p;
  struct ow_slist *prev;

  p = p_slist;
  preve = NULL;

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
ow_slist_remove_node(struct ow_slist *p_slist,
                     struct ow_slist const *p_node)
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
              void const *const p_data)
{
  while (p_slist && p_slist->data != p_data)
    p_slist = p_slist->next;

  return p_slist;
}


struct ow_slist*
ow_slist_find_custom(struct ow_slist *p_slist,
                     void const *const p_data,
                     OWCompareFunc const p_compare_func)
{
  assert(NULL != p_compare_func);

  while (p_slist && p_compare_func(p_slist->data, p_data) != 0)
    p_slist = p_slist->next;

  return p_slist;
}


_Bool
ow_slist_is_empty(struct ow_slist const *const p_slist)
{
  return ow_slist_length(p_slist) == 0;
}


unsigned int
ow_slist_length(struct ow_slist const *p_slist)
{
  unsigned int length;

  length = 0;

  while (p_slist) {
    p_slist = p_slist->next;
    length++;
  }

  return length;
}
