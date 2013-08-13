#ifndef OW_HASH_TABLE_H 
#define OW_HASH_TABLE_H

#include "ow_common.h"


struct ow_hash_table_entry {
  uint32_t                    hash;
  const char                  *key;
  void                        *data;
  struct ow_hash_table_entry  *next;
};

struct ow_hash_table {
    uint32_t                     bucket_count;
    struct ow_hash_table_entry  **buckets;
    bool                         allow_duplicates;
    OWHashFunc                   hash_func;
    OWCompareFunc                compare_func;
};

/*
struct ow_hash_table_iterator {
    uint32                        i;
    struct ow_hash_table_node_t   *node;
    uint32                        hash;
    void*                         value;
};

typedef struct ow_hash_table_iterator ow_hash_tableIterator;

*/

struct ow_hash_table*   ow_hash_table_create    (const uint32_t p_bucket_count,
                                                 const bool p_allow_duplicates,
                                                 const OWHashFunc p_hash_func);

void                    ow_hash_table_free      (struct ow_hash_table *p_table);

struct
ow_hash_table_entry*    ow_hash_table_insert    (const struct ow_hash_table *const p_table,
                                                 const char *const p_key,
                                                 void *const p_data);

void                    ow_hash_table_remove    (const struct ow_hash_table *const p_table,
                                                 const char *const p_key);

void                    ow_hash_table_removei   (const struct ow_hash_table *const p_table,
                                                 const uint32_t p_hash);
  
void*                   ow_hash_table_get       (const struct ow_hash_table *const p_table,
                                                 const char *const p_key);

void*                   ow_hash_table_geti      (const struct ow_hash_table *const p_table,
                                                 const uint32_t p_hash);

int                     ow_hash_table_resize    (struct ow_hash_table *p_table,
                                                 size_t p_size);

#endif //H_G2_HASHTABLE

