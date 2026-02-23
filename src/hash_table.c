#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

void ht_init(HashTable *ht)
{
    int i;
    for (i = 0; i < TABLE_SIZE; i++)
        ht->buckets[i] = NULL;
}

unsigned long ht_hash_file(const char *filepath)
{
    FILE *f = fopen(filepath, "rb");
    if (!f)
    {
        printf("couldnt open: %s\n", filepath);
        return 0;
    }

    unsigned long hash = 5381;
    int c;
    while ((c = fgetc(f)) != EOF)
        hash = hash * 33 + c;

    fclose(f);
    return hash;
}

int ht_insert(HashTable *ht, const char *filepath)
{
    unsigned long hash = ht_hash_file(filepath);
    if (hash == 0)
        return 0;

    int slot = hash % TABLE_SIZE;
    HashNode *curr = ht->buckets[slot];

    while (curr != NULL)
    {
        if (curr->hash == hash)
        {
            printf("duplicate -> %s\n", filepath);
            return 1;
        }
        curr = curr->next;
    }

    HashNode *node = (HashNode *)malloc(sizeof(HashNode));
    strncpy(node->filepath, filepath, 1023);
    node->hash = hash;
    node->next = ht->buckets[slot];
    ht->buckets[slot] = node;

    return 0;
}

void ht_free(HashTable *ht)
{
    int i;
    for (i = 0; i < TABLE_SIZE; i++)
    {
        HashNode *curr = ht->buckets[i];
        while (curr != NULL)
        {
            HashNode *tmp = curr;
            curr = curr->next;
            free(tmp);
        }
        ht->buckets[i] = NULL;
    }
}