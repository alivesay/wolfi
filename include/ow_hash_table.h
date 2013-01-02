#ifndef OW_HASH_TABLE_H 
#define OW_HASH_TABLE_H

#include "ow_common.h"


struct _ow_hash_table_node {
    uint32_t                      key;
    void*                         data;
    struct _ow_hash_table_node*   next;
};

struct ow_hash_table {
    uint32_t                     length;
    struct _ow_hash_table_node   **buckets;
    bool                         allows_duplicates;
    OWHashFunc                   hash_func;
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

struct ow_hash_table*   ow_hash_table_create    (const uint32_t p_length);

void                    ow_hash_table_free      (struct ow_hash_table *p_table);

int                     ow_hash_table_insert    (const ow_hash_table *const p_table,
                                                 const char *const p_key,
                                                 const void *const p_data);

int                     ow_hash_table_inserti   (const ow_hash_table *p_table,
                                                 const uint32_t p_key,
                                                 const void *const p_data);

void                    ow_hash_table_remove    (ow_hash_table *p_table,
                                                 const char *const p_key);

int                     ow_hash_table_removei   (ow_hash_table *p_table,
                                                 const uint32_t p_key);
  
void*                   ow_hash_table_get       (ow_hash_table *p_table,
                                                 const char *p_key);

void*                   ow_hash_table_geti      (ow_hash_table *p_table,
                                                 const uint32_t p_key);

int                     ow_hash_table_resize    (ow_hash_table *p_table,
                                                 size_t p_size);


#endif //H_G2_HASHTABLE

