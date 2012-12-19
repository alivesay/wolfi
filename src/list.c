#include "base.h"
#include "slist.h"

struct ow_slist* ow_slist_create(void)
{
  struct ow_slist* slist = calloc(sizeof(*slist));
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
}

struct ow_slist* ow_slist_insert(struct ow_slist* p_slist, void* p_data)
{
  assert(NULL != p_slist);

  struct ow_slist* p = ow_slist_create();
  if (!p) goto _fail;

  p->data = p_data;
  p->next = p_slist->head;

  /* maintain pointer to next to last node */
  if (p->next && !p->next->next) p_slist->penultimate = p;

  p_slist->head = p;

  return p;

_fail:
  return NULL;
}

int ow_slist_remove(struct ow_slist *p_slist, struct ow_slist_node* p_node)
{
  assert(NULL != p_slist);
  assert(NULL != p_node);
  
  struct ow_slist_node *p;

  if (p_node == p_slist->head) {   /* head node */a

    free(p_node);
    p_slist->head = NULL;

  } else if (p_node->next) {       /* intermediate node */
    
    /* O(n) if p_node is penultimate node */
    if (!p_node->next->next) {   
      p = p_slist->head;
      while (p->next != p_slist->penultimate) p = p->next;
      p_slist->penultimate = p;
    }

    p = p_node->next;
    p_node->data = p->data;
    p_node->next = p->next;
    free(p);

  } else {                         /* last node */

    p = p_slist->head;
    while (p = p->next)
      if (p->next)) {
        
      }
    } while (p = p->next);
      
    }
  }

  if (p_slist == p_node) 

  while (p_slist->next && p_slist-> != p_node) p_slist = p_slist->next;

  if (p_slist) {
    
  p_slist->next = p_node->next;

}

