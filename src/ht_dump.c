/*
** EPITECH PROJECT, 2025
** Secured
** File description:
** ht_dump.c
*/

#include "hashtable.h"
#include "my.h"

void list_dump(entry_t *node, hashtable_t *ht)
{
    entry_t *temp = NULL;
    int key_hash = 0;

    if (!node)
        return;
    for (temp = node; temp != NULL; temp = temp->next) {
        key_hash = ht->hash(node->key, ht->len);
        mini_printf("> %d - %s\n", key_hash, node->value);
    }
}

void ht_dump(hashtable_t *ht)
{
    if (!ht)
        return;
    for (int i = 0; i < ht->len; i++) {
        mini_printf("[%d]:\n", i);
        list_dump(ht->buckets[i], ht);
    }
}
