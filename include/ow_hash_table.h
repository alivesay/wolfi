#ifndef OW_HASH_TABLE_H 
#define OW_HASH_TABLE_H

#include "ow_common.h"


struct _ow_hash_table_entry {
  uint32_t   key;
  void       *data;
  struct _ow_hash_table_entry *next;
};

struct ow_hash_table {
    uint32_t          bucket_count;
    struct _ow_hash_table_entry  **buckets;
    bool              allow_duplicates;
    OWHashFunc        hash_func;
    OWCompareFunc     compare_func;
};

/*
struct _ow_hash_table_iterator {
    uint32                        i;
    struct ow_hash_table_node_t   *node;
    uint32                        key;
    void*                         value;
};

typedef struct _ow_hash_table_iterator ow_hash_tableIterator;

*/

struct ow_hash_table*   ow_hash_table_create    (const uint32_t p_bucket_count,
                                                 const bool p_allow_duplicates,
                                                 const OWHashFunc p_hash_func);

void                    ow_hash_table_free      (struct ow_hash_table *p_table);

bool                    ow_hash_table_insert     (const struct ow_hash_table *const p_table,
                                                 const char *const p_key,
                                                 void *const p_data);

bool                    ow_hash_table_inserti    (const struct ow_hash_table *const p_table,
                                                 const uint32_t p_key,
                                                 void *const p_data);

void                    ow_hash_table_remove    (const struct ow_hash_table *const p_table,
                                                 const char *const p_key);

void                    ow_hash_table_removei   (const struct ow_hash_table *const p_table,
                                                 const uint32_t p_key);
  
void*                   ow_hash_table_get       (const struct ow_hash_table *const p_table,
                                                 const char *const p_key);

void*                   ow_hash_table_geti      (const struct ow_hash_table *const p_table,
                                                 const uint32_t p_key);

int                     ow_hash_table_resize    (struct ow_hash_table *p_table,
                                                 size_t p_size);

void                    _ow_hash_table_entry_free_func    (void *p_data);

int                     _ow_hash_table_entry_compare_func (const void *p_a,
                                                          const void *p_b);


#endif //H_G2_HASHTABLE

