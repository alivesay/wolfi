#ifndef OW_SLIST_H
#define OW_SLIST_H

#include "ow_types.h"


struct ow_slist {
  void              *data;
  struct ow_slist   *next;
};

void               ow_slist_free          (struct ow_slist *const p_slist);

void               ow_slist_free_custom   (struct ow_slist *p_slist, 
                                           const OWFreeFunc p_free_func);

struct ow_slist*   ow_slist_insert        (struct ow_slist *const p_slist,
                                           void *const p_data);

struct ow_slist*   ow_slist_insert_end    (struct ow_slist *const p_slist,
                                           void *const p_data);

struct ow_slist*   ow_slist_remove        (struct ow_slist *p_slist,
                                           const void *const p_data);

struct ow_slist*   ow_slist_remove_node   (struct ow_slist *p_slist,
                                           struct ow_slist const *p_node);

struct ow_slist*   ow_slist_find          (struct ow_slist *p_slist,
                                           const void *const p_data);

struct ow_slist*   ow_slist_find_custom   (struct ow_slist *p_slist,
                                           const void *const p_data,
                                           const OWCompareFunc p_compare_func);

_Bool              ow_slist_is_empty      (const struct ow_slist *const p_slist);

unsigned int       ow_slist_length        (const struct ow_slist *p_slist);

//remove custom
#endif /* OW_SLIST_H */
