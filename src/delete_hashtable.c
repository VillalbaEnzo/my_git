/*
** EPITECH PROJECT, 2026
** delete_hastable.c
** File description:
** delete_hashtable
*/
#include "hashtable.h"

void delete_hashtable(hashtable_t *ht)
{
    entry_t *next_node = NULL;

    if (!ht)
        return;
    for (int i = 0; i < ht->len; i++) {
        while (ht->buckets[i]) {
            next_node = ht->buckets[i]->next;
            free(ht->buckets[i]->key);
            free(ht->buckets[i]->value);
            free(ht->buckets[i]);
            ht->buckets[i] = next_node;
        }
    }
    free(ht->buckets);
    free(ht);
}
