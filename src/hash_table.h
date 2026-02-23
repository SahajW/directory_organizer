#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define TABLE_SIZE 1024

typedef struct HashNode {
    char filepath[1024];
    unsigned long hash;
    struct HashNode *next;
} HashNode;

typedef struct {
    HashNode *buckets[TABLE_SIZE];
} HashTable;

void ht_init(HashTable *ht);
unsigned long ht_hash_file(const char *filepath);
int ht_insert(HashTable *ht, const char *filepath);
void ht_free(HashTable *ht);

#endif