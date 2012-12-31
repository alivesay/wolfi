#ifndef OW_HASH_TABLE_H 
#define OW_HASH_TABLE_H

#include "ow_common.h"


struct _ow_hash_table_node {
    uint32_t                    key;
    void*                           data;
    struct _ow_hash_table_node_t*   next;
};

struct ow_hash_table {
    uint32_t                   length;
    struct _ow_hash_table_node_t   **nodes;
    bool                           allows_duplicates;
    OWHashFunc                     hash_func;
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

ow_hash_table*   ow_hash_table_create    (const uint32_t p_length);

void             ow_hash_table_free      (ow_hash_table *p_table);

uint32_t         ow_hash_table_insert    (const ow_hash_table *const p_table,
                                          const char *const p_key,
                                          const void *const p_data);

uint32_t         ow_hash_table_inserti   (ow_hash_table *p_table,
                                          const uint32_t p_key,
                                          const void *const p_data);

void             ow_hash_table_remove    (ow_hash_table *p_table,
                                          const char *const p_key);

uint32_t         ow_hash_table_removei   (ow_hash_table *p_table,
                                          const uint32_t p_key);
  
void*            ow_hash_table_get       (ow_hash_table *p_table,
                                          const char *p_key);

void*            ow_hash_table_geti      (ow_hash_table *p_table,
                                          const uint32_t p_key);

uint32_t         ow_hash_table_resize    (ow_hash_table *p_table,
                                          size_t p_size);


#endif //H_G2_HASHTABLE

