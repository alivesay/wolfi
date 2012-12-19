#include <stdlib.h>

#include "base.h"
#include "slist.h"

struct ow_slist* ow_slist_create(void)
{
  struct ow_slist* slist = calloc(1, sizeof(*slist));
  if (!slist) goto _fail;

  return slist;

_fail:
  return NULL;
}

void ow_slist_free(struct ow_slist* p_slist)
{
  assert(NULL != p_slist);

  struct ow_slist_node* p = p_slist->head;

  while (p_slist->head) {
    p = p_slist->head->next;
    free(p_slist->head);
    p_slist->head = p;
  }

  free(p_slist);
}

struct ow_slist_node* ow_slist_insert(struct ow_slist* p_slist, void* p_data)
{
  assert(NULL != p_slist);

  struct ow_slist_node* p = calloc(1, sizeof(*p));
  if (!p) goto _fail;

  p->data = p_data;
  p->next = p_slist->head;

  p_slist->head = p;

  return p;

_fail:
  return NULL;
}

void ow_slist_remove_node(struct ow_slist *p_slist, struct ow_slist_node* p_node)
{
  assert(NULL != p_slist);
  assert(NULL != p_node);
  
  struct ow_slist_node *p;

  if (p_node == p_slist->head) {   /* head node - O(1) */

    p_slist->head = p_slist->head->next;
    free(p_node);

  } else if (p_node->next) {       /* intermediate node  - O(1) */

    p = p_node->next;
    p_node->data = p->data;
    p_node->next = p->next;
    free(p);

  } else {                         /* last node - O(n) */
    
    p = p_slist->head;
    while (p->next && p->next->next) p = p->next;
    free(p->next);
    p->next = NULL;
  
  }
}

int ow_slist_remove(struct ow_slist *p_slist, void* p_data)
{
  assert(NULL != p_slist);
  
  struct ow_slist_node *p = p_slist->head;
  struct ow_slist_node *prev;

  while (p && p->data != p_data) {
    prev = p;
    p = p->next;
  }

  if (p) {
    prev->next = p->next;
    free(p);
    return 0;
  }

 return -1;
}
