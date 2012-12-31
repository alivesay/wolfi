#ifndef OW_HASH_TABLE_H 
#define OW_HASH_TABLE_H

#include "ow_types.h"


struct _ow_hash_table_node {
    unsigned int                    key;
    void*                           data;
    struct _ow_hash_table_node_t*   next;
};

struct _ow_hash_table {
    unsigned int                   length;
    struct _ow_hash_table_node_t   **nodes;
    bool                           allows_duplicates;
    OWHashFunc                     hash_func;
};

typedef struct _ow_hash_table OWHashTable;

/*
struct _ow_hash_table_iterator {
    uint32                        i;
    struct ow_hash_table_node_t   *node;
    uint32                        key;
    void*                         value;
};

typedef struct _ow_hash_table_iterator OWHashTableIterator;

*/

OWHashTable*   ow_hash_table_create    (unsigned int const p_length);

void           ow_hash_table_free      (OWHashTable *p_table);

unsigned int   ow_hash_table_insert    (OWHashTable const *const p_table,
                                        char const *const p_key,
                                        void const *const p_data);

unsigned int   ow_hash_table_inserti   (OWHashTable *p_table,
                                        unsigned int p_key const,
                                        void const *const p_data);

void           ow_hash_table_remove    (OWHashTable *p_table,
                                        char consti *const p_key);

unsigned int   ow_hash_table_removei   (OWHashTable *p_table,
                                        unsigned int const p_key);

void*          ow_hash_table_get       (OWHashTable *p_table,
                                        const char *p_key);

void*          ow_hash_table_geti      (OWHashTable *p_table,
                                        unsigned int const p_key);

unsigned int   ow_hash_table_resize    (OWHashTable *p_table,
                                        size_t p_size);

/*
void           ow_hash_table_iterator_create(ow_hash_table_iterator_t *p_iterator);
void* ow_hash_table_iterator_next(ow_hash_table_t *p_table,
ow_hash_table_iterator_t *p_iterator);
*/

#undef get16bits
#if (defined(__GNUC__) && defined(__i386__)) || defined(__WATCOMC__) \
  || defined(_MSC_VER) || defined (__BORLANDC__) || defined (__TURBOC__)
#define get16bits(d) (*((const uint16_t *) (d)))
#endif

#if !defined (get16bits)
#define get16bits(d) ((((uint32_t)(((const uint8_t *)(d))[1])) << 8)\
                       +(uint32_t)(((const uint8_t *)(d))[0]) )
#endif


// replace with mummurhash


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

