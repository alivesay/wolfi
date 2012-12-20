#ifndef H_G2HASHTABLE
#define H_G2HASHTABLE

#include "g2_types.h"
#include <stddef.h>
#include <stdint.h>

#define G2_DEFAULT_HASH_TABLE_SIZE 128

typedef struct _g2_hash_table_node_t {
    uint32 key;
    void* data;
    struct _g2_hash_table_node_t* next;
} g2_hash_table_node_t;

typedef struct {
    size_t size;
    g2_hash_table_node_t **nodes;
    size_t (*hash_function)(const char*);
    bool allows_duplicates;
} g2_hash_table_t;

typedef struct {
    uint32 i;
    g2_hash_table_node_t * node;
    uint32 key;
    void* value;
} g2_hash_table_iterator_t;

g2_hash_table_t* g2_hash_table_create(size_t p_size);
void g2_hash_table_release(g2_hash_table_t *p_table);
uint32 g2_hash_table_insert(g2_hash_table_t *p_table, const char* p_key,
void *p_data);
uint32 g2_hash_table_inserti(g2_hash_table_t *p_table, uint32 p_key, void*
p_data);
void g2_hash_table_remove(g2_hash_table_t *p_table, const char* p_key);
uint32 g2_hash_table_removei(g2_hash_table_t *p_table, uint32 p_key);
void* g2_hash_table_get(g2_hash_table_t *p_table, const char *p_key);
void* g2_hash_table_geti(g2_hash_table_t *p_table, uint32 p_key);
uint32 g2_hash_table_resize(g2_hash_table_t *p_table, size_t p_size);
void g2_hash_table_iterator_create(g2_hash_table_iterator_t *p_iterator);
void* g2_hash_table_iterator_next(g2_hash_table_t *p_table,
g2_hash_table_iterator_t *p_iterator);

#undef get16bits
#if (defined(__GNUC__) && defined(__i386__)) || defined(__WATCOMC__) \
  || defined(_MSC_VER) || defined (__BORLANDC__) || defined (__TURBOC__)
#define get16bits(d) (*((const uint16_t *) (d)))
#endif

#if !defined (get16bits)
#define get16bits(d) ((((uint32_t)(((const uint8_t *)(d))[1])) << 8)\
                       +(uint32_t)(((const uint8_t *)(d))[0]) )
#endif



/* by Paul Hsieh */
/* http://www.azillionmonkeys.com/qed/hash.html */
static inline uint32_t SuperFastHash (const char * data, int len) {
uint32_t hash = len, tmp;
int rem;

    if (len <= 0 || data == NULL) return 0;

    rem = len & 3;
    len >>= 2;

    /* Main loop */
    for (;len > 0; len--) {
        hash  += get16bits (data);
        tmp    = (get16bits (data+2) << 11) ^ hash;
        hash   = (hash << 16) ^ tmp;
        data  += 2*sizeof (uint16_t);
        hash  += hash >> 11;
    }

    /* Handle end cases */
    switch (rem) {
        case 3: hash += get16bits (data);
                hash ^= hash << 16;
                hash ^= data[sizeof (uint16_t)] << 18;
                hash += hash >> 11;
                break;
        case 2: hash += get16bits (data);
                hash ^= hash << 11;
                hash += hash >> 17;
                break;
        case 1: hash += *data;
                hash ^= hash << 10;
                hash += hash >> 1;
    }

    /* Force "avalanching" of final 127 bits */
    hash ^= hash << 3;
    hash += hash >> 5;
    hash ^= hash << 4;
    hash += hash >> 17;
    hash ^= hash << 25;
    hash += hash >> 6;

    return hash;
}
#endif //H_G2_HASHTABLE

