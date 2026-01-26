/*
** EPITECH PROJECT, 2025
** Secured
** File description:
** ht_search.c
*/

#include "hashtable.h"
#include "my.h"

char *search(entry_t *head_list, char *key)
{
    entry_t *temp = NULL;

    if (!head_list)
        return NULL;
    for (temp = head_list; temp != NULL; temp = temp->next) {
        if (!my_strcmp(temp->key, key))
            return temp->value;
    }
    return NULL;
}

char *ht_search(hashtable_t *ht, char *key)
{
    int index = 0;

    if (!ht || !key)
        return NULL;
    index = ((unsigned int)ht->hash(key, ht->len)) % ht->len;
    return search(ht->buckets[index], key);
}
