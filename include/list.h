#ifndef SLIST_H
#define SLIST_H

struct ow_slist_node {
  void              *data;
  struct ow_slist   *next;
};

struct ow_slist {
  struct ow_slist   *head;
  
  int   (*func_compare)   (void *p_data_a, void *p_data_b);
};

struct ow_slist          ow_slist_create           (void);
void                     ow_slist_free             (struct ow_slist *p_slist);
struct ow_slist_node*    ow_slist_insert           (struct ow_slist *p_slist, void *p_data);
//int                      ow_slist_remove           (struct ow_slist *p_slist, void *p_data);
int                      ow_slist_remove_node      (struct ow_slist *p_slist, struct ow_slist_node *p_node);

#endif // SLIST_H
