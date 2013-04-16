
#include <assert.h>
#include <stdlib.h>

#include "ow_log.h"
#include "ow_hash_table.h"


static inline uint32_t
_ow_hash_table_next_prime_modulus(const uint32_t p_n)
{
  static const uint32_t prime_modull[] = {
             7u,
            13u,
            31u,
            61u,
           127u,
           251u,
           509u,
          1021u,
          2039u,
          4093u,
          8191u,
         16381u,
         32749u,
         65521u,
        131071u,
        262139u,
        524287u,
       1048573u,
       2097143u,
       4194301u,
       8388593u,
      16777213u,
      33554393u,
      67108859u,
     134217689u,
     268435399u,
     536870909u,
    1073741789u,
    2147483647u,
    4294967291u
  };
 
  const uint32_t *i = prime_modull;

  do {
    if (*i > p_n) return *i;
  } while (4294967291u != *i++);

  return p_n;
}


struct ow_hash_table*
ow_hash_table_create(const uint32_t p_bucket_count,
                     const bool p_allow_duplicates)
{
  struct ow_hash_table *table;

  OW_CALLOC(table, 1, sizeof *table);
  if (!table) goto _error;

  OW_CALLOC(table->buckets, p_bucket_count, sizeof *table->buckets);
  if (!table->buckets) goto _error;

  table->allow_duplicates = p_allow_duplicates;
  table->bucket_count = p_bucket_count;

  return table;

_error:
  if (table) free(table->buckets);
  free(table);
  return NULL;
}


void
ow_hash_table_free(struct ow_hash_table *p_table)
{
  size_t n;

  for (n = 0; n < p_table->bucket_count; ++n)
    if (p_table->buckets[n]) ow_slist_free(p_table->buckets[n]);

  free(p_table->buckets);
  free(p_table);
}


bool
ow_hash_table_insert(const struct ow_hash_table *const p_table,
                     const char *const p_key,
                     const void *const p_data)
{
  return ow_hash_table_inserti(p_table, SuperFastHash(p_key, strlen(p_key)), p_data);
}


bool
ow_hash_table_inserti(const struct ow_hash_table *const p_table,
                      const uint32_t p_key,
                      const void *const p_data)
{
  struct _ow_hash_table_entry *entry = NULL;
  size_t index = p_key % p_table->bucket_count;

  if (p_table->buckets[index] && !p_table->allow_duplicates)
        ow_hash_table_removei(p_table, p_key);

  OW_CALLOC(entry, 1, sizeof *entry);
  if (!entry) goto _error;

  entry->key = p_key;
  entry->data = p_data;

  p_table->buckets[index] = ow_slist_insert(p_table->buckets[index], entry);
  if (!p_table->buckets[index]) goto _error;
  
  return true;

_error:
  free(entry);
  return false;
}


void
ow_hash_table_remove(const struct ow_hash_table *const p_table,
                     const char *const p_key)
{
  ow_hash_table_removei(p_table, SuperFastHash(p_key, strlen(p_key)));
}


void
ow_hash_table_removei(const struct ow_hash_table *const p_table,
                      const uint32_t p_key)
{
  size_t index = p_key % p_table->bucket_count;

  if (!p_table->buckets[index]) return;

  ow_slist_remove_custom(p_table->buckets[index],
                         p_key,
                         &_ow_hash_table_entry_compare_func);
                                                  
  if (p_table->allow_duplicates) 
    while(ow_slist_remove_custom(p_table->buckets[index],
                                 p_key,
                                 &_ow_hash_table_entry_compare_func));
}


void*
ow_hash_table_get(const struct ow_hash_table *const p_table,
                  const char *const p_key)
{
  return ow_hash_table_geti(p_table, SuperFastHash(p_key, strlen(p_key)));
}

void*
ow_hash_table_geti(const struct ow_hash_table *p_table,
                   const uint32_t p_key)
{
  // TODO: handle allow_duplicates here?  always return iterator?

  struct ow_slist *list_node = NULL;
  size_t index = p_key % p_table->bucket_count;
 
  if (!p_table->buckets[index]) return NULL;

  list_node = ow_slist_find_custom(p_table->buckets[index],
                                   p_key,
                                   _ow_hash_table_entry_compare_func);
  
  if (list_node)
    return list_node->data;
  else
    return NULL;
}

/*
uint32 g2_hash_table_resize(g2_hash_table_t *p_table, size_t p_size) {
    size_t n;
    g2_hash_table_t new_table;
    g2_hash_table_node_t *node = NULL, *next = NULL;

    new_table.size = p_size;

  CALLOC(new_table.nodes, p_size, g2_hash_table_node_t*);
    if (!new_table.nodes) goto _fail;

    for (n = 0; n < p_table->size; n++) {
        for (node = p_table->nodes[n]; node; node = next) {
            next = node->next;
            g2_hash_table_inserti(&new_table, node->key, node->data);
            g2_hash_table_removei(p_table, node->key);
        }
    }

    free(p_table->nodes);
    p_table->size = new_table.size;
    p_table->nodes = new_table.nodes;

    return 0;

_fail:
    return -1;
}

void g2_hash_table_iterator_create(g2_hash_table_iterator_t *p_iterator) {
    p_iterator->i = 0;
    p_iterator->node = NULL;
    p_iterator->key = 0;
}

void* g2_hash_table_iterator_next(g2_hash_table_t *p_table,
g2_hash_table_iterator_t *p_iterator) {
    if (p_iterator->i >= p_table->size) {
        p_iterator->key = 0;
        return NULL;
    }

    if (p_iterator->node) {
        if ((p_iterator->node = p_iterator->node->next)) {
            return p_iterator->node->data;
        } else {
            p_iterator->i++;
        }
    }

    while ((p_iterator->i < p_table->size) && !(p_iterator->node =
p_table->nodes[p_iterator->i])) { p_iterator->i++; }

    return (p_iterator->node ? p_iterator->node->data : NULL);
}

*/

int
_ow_hash_table_entry_compare_func(const void *p_a,
                                  const void *p_b)
{
  return (uint32_t)p_a == ((struct _ow_hash_table_entry*)p_b)->key;
}
