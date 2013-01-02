
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
    if (*i > p_i) return *i;
  } while (4294967291u != *i++);

  return p_i;
}


struct ow_hash_table*
ow_hash_table_create(const uint32_t p_size)
{
  struct ow_hash_table *table;

  OW_CALLOC(table, 1, sizeof *table);
  if (!table) goto _error;

  OW_CALLOC(table->nodes, 1, sizeof *table->nodes);
  if (!table->nodes) goto _error;

  table->size = p_size;

  return table;

_error:
  free(table);
  return NULL;
}


void
ow_hash_table_free(struct ow_hash_table p_table)
{
  size_t n;
  ow_hash_table_node_t *node = NULL, *oldnode = NULL;

  for (n = 0; n < p_table->size; n++) {
    node = p_table->nodes[n];
    while (node) {
      oldnode = node;
    }
  }
  free(p_table->nodes);
  free(p_table);
}


int
ow_hash_table_insert(const ow_hash_table *const p_table,
                     const char *const p_key,
                     const void *const p_data)
{
  return ow_hash_table_inserti(p_table, SuperFastHash(p_key, strlen(p_key)), p_data);
}


int
ow_hash_table_inserti(const struct ow_hash_table *const p_table,
                      const uint32 p_key,
                      const void *const p_data)
{
    struct ow_hash_table_node *node = NULL;
    size_t hash = p_key % p_table->size;

    node = p_table->nodes[hash];
    while(node) {
        if (node->key == p_key) {
            node->data = p_data;
            return 0;
        }
        node = node->next;
    }

    OW_MALLOC(node, sizeof *node);
    if (!node) goto _error;

    node->key = p_key;
    node->data = p_data;
    node->next = p_table->nodes[hash];
    p_table->nodes[hash] = node;

    return 0;

_error:
    return -1;
}

void g2_hash_table_remove(g2_hash_table_t* p_table, const char* p_key) {
    g2_hash_table_removei(p_table, SuperFastHash(p_key, strlen(p_key)));
}

uint32 g2_hash_table_removei(g2_hash_table_t* p_table, uint32 p_key) {
    g2_hash_table_node_t *node = NULL, *prevnode = NULL;
    size_t hash = p_key % p_table->size;

    node = p_table->nodes[hash];
    while (node) {
        if (node->key == p_key) {
            if (prevnode) prevnode->next = node->next;
            else p_table->nodes[hash] = node->next;
            free(node);
            return 0;
        }
        prevnode = node;
        node = node->next;
     }

     return -1;
}

void* g2_hash_table_get(g2_hash_table_t *p_table, const char *p_key) {
    return g2_hash_table_geti(p_table, SuperFastHash(p_key, strlen(p_key)));
}

void* g2_hash_table_geti(g2_hash_table_t *p_table, uint32 p_key) {
    g2_hash_table_node_t *node = NULL;

    size_t hash = p_key % p_table->size;

    node = p_table->nodes[hash];
    while (node) {
        if (node->key == p_key) return node->data;
        node = node->next;
    }

    return NULL;
}

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
