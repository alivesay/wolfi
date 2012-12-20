#ifndef SLIST_H
#define SLIST_H

struct ow_slist {
  void              *data;
  struct ow_slist   *next;
};

void               ow_slist_free          (struct ow_slist *p_slist);
struct ow_slist*   ow_slist_insert        (struct ow_slist *p_slist, void *p_data);
struct ow_slist*   ow_slist_insert_end    (struct ow_slist *p_slist, void *p_data);
struct ow_slist*   ow_slist_remove        (struct ow_slist *p_slist, void *p_data);
struct ow_slist*   ow_slist_remove_node   (struct ow_slist *p_slist, struct ow_slist *p_node);
_Bool              ow_slist_is_empty      (struct ow_slist *p_slist);
unsigned int       ow_slist_length        (struct ow_slist *p_slist);

// ow_slist_free_custom
// find
// find_custom
//
//

#endif /* SLIST_H */
