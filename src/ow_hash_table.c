
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "ow_log.h"
#include "ow_hash_table.h"

static const uint32_t prime_modull_count = 32; 

static const uint32_t prime_modull[] =
{
  0u,          3u,          11u,         23u,         53u,
  97u,         193u,        389u,        769u,        1543u,
  3079u,       6151u,       12289u,      24593u,      49157u,
  98317u,      196613u,     393241u,     786433u,     1572869u,
  3145739u,    6291469u,    12582917u,   25165843u,   50331653u,
  100663319u,  201326611u,  402653189u,  805306457u,  1610612741u,
  3221225473u, 4294967291u
};


static inline uint32_t
ow_hash_table_next_prime_modulus(const uint32_t p_n)
{
 const uint32_t *i = prime_modull;

  do {
    if (*i > p_n) return *i;
  } while (4294967291u != *i++);

  return p_n;
}


struct ow_hash_table*
ow_hash_table_create(const uint32_t p_bucket_count,
                     const bool p_allow_duplicates,
                     const OWHashFunc p_hash_func)
{
  struct ow_hash_table *table;

  OW_CALLOC(table, 1, sizeof *table);
  if (!table) goto _error;

  OW_CALLOC(table->buckets, p_bucket_count, sizeof *table->buckets);
  if (!table->buckets) goto _error;

  table->allow_duplicates = p_allow_duplicates;
  table->bucket_count = p_bucket_count;
  table->hash_func = p_hash_func;

  return table;

_error:
  if (table) OW_FREE(table->buckets);
  OW_FREE(table);
  return NULL;
}


void
ow_hash_table_free(struct ow_hash_table *p_table)
{
  size_t n;
  struct ow_hash_table_entry *entry = NULL;

  for (n = 0; n < p_table->bucket_count; ++n) {
    while ((entry = p_table->buckets[n])) {
      p_table->buckets[n] = p_table->buckets[n]->next;
      OW_FREE(entry);
    }
  }

  OW_FREE(p_table->buckets);
  OW_FREE(p_table);
}


struct ow_hash_table_entry*
ow_hash_table_insert(const struct ow_hash_table *const p_table,
                     const char *const p_key,
                     void *const p_data)
{
  struct ow_hash_table_entry *entry = NULL;
  uint32_t hash; 
  size_t index;
 
  hash = p_table->hash_func(p_key);
  index = hash % p_table->bucket_count;

  // TODO: allow optional overwrite vs error
  if (p_table->buckets[index] && !p_table->allow_duplicates)
    ow_hash_table_removei(p_table, hash);

  OW_CALLOC(entry, 1, sizeof *entry);
  if (!entry) goto _error;

  entry->hash = hash;
  entry->key = p_key;
  entry->data = p_data;
  entry->next = p_table->buckets[index];

  p_table->buckets[index] = entry;

  return entry;

_error:
  OW_FREE(entry);
  return NULL;
}


void
ow_hash_table_remove(const struct ow_hash_table *const p_table,
                     const char *const p_key)
{
  ow_hash_table_removei(p_table, p_table->hash_func(p_key));
}


void
ow_hash_table_removei(const struct ow_hash_table *const p_table,
                      const uint32_t p_hash)
{
  size_t index = p_hash % p_table->bucket_count;
  struct ow_hash_table_entry *p = NULL, *prev = NULL;
  
  p = p_table->buckets[index];
  do {
    while (p && p->hash != p_hash) {
      prev = p;
      p = p->next;
    }
    
    if (p) {
      if (prev) {
        prev->next = p->next;
        OW_FREE(p);
        p = prev->next;
      } else {
        p_table->buckets[index] = p->next;
        OW_FREE(p);
        p = p_table->buckets[index];
      }
    }
  } while (p_table->allow_duplicates && p);
}


void*
ow_hash_table_get(const struct ow_hash_table *const p_table,
                  const char *const p_key)
{
  return ow_hash_table_geti(p_table, p_table->hash_func(p_key));
}

void*
ow_hash_table_geti(const struct ow_hash_table *p_table,
                   const uint32_t p_hash)
{
  // TODO: handle allow_duplicates here?  always return iterator?

  size_t index = p_hash % p_table->bucket_count;
  struct ow_hash_table_entry *p = NULL;

  p = p_table->buckets[index];

  while (p && p->hash != p_hash)
    p = p->next;
   
  return p ? p->data : NULL;
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

    OW_FREE(p_table->nodes);
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

