#include "g2_hashtable.h"
#include "g2_base.h"

g2_hash_table_t* g2_hash_table_create(size_t p_size) {
    g2_hash_table_t *table = NULL;

    p_size = MAX(p_size, G2_DEFAULT_HASH_TABLE_SIZE);

    CALLOC(table, 1, g2_hash_table_t);
    if (!table) goto _fail;

    CALLOC(table->nodes, p_size, g2_hash_table_node_t*);
    if (!table->nodes) goto _fail;

    table->size = p_size;

    return table;

_fail:
    if (table->nodes) free(table->nodes);
    if (table) free(table);
    return NULL;
}

void g2_hash_table_release(g2_hash_table_t* p_table) {
    size_t n;
    g2_hash_table_node_t *node = NULL, *oldnode = NULL;

    for (n = 0; n < p_table->size; n++) {
        node = p_table->nodes[n];
        while (node) {
            oldnode = node;
            node = node->next;
            free(oldnode);
        }
    }
    free(p_table->nodes);
    free(p_table);
    p_table = NULL;
}

uint32 g2_hash_table_insert(g2_hash_table_t* p_table, const char* p_key,
void *p_data) {
    return g2_hash_table_inserti(p_table, SuperFastHash(p_key,
strlen(p_key)), p_data);
}

uint32 g2_hash_table_inserti(g2_hash_table_t* p_table, uint32 p_key, void
*p_data) {
    g2_hash_table_node_t* node = NULL;
    size_t hash = p_key % p_table->size;

    node = p_table->nodes[hash];
    while(node) {
        if (node->key == p_key) {
            node->data = p_data;
            return 0;
        }
        node = node->next;
    }

    MALLOC(node, sizeof(g2_hash_table_node_t));
    if (!node) goto _fail;

    node->key = p_key;
    node->data = p_data;
    node->next = p_table->nodes[hash];
    p_table->nodes[hash] = node;

    return 0;

_fail:
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