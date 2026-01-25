/*
** EPITECH PROJECT, 2025
** Secured
** File description:
** new_hashtable.c
*/

#include "hashtable.h"

hashtable_t *new_hashtable(int (*hash) (char *, int), int len)
{
    hashtable_t *table = malloc(sizeof(hashtable_t));

    if (!table)
        return NULL;
    if (len < 0 || !hash) {
        free(table);
        return NULL;
    }
    table->buckets = malloc(len * sizeof(entry_t *));
    if (!table->buckets) {
        free(table);
        return NULL;
    }
    for (int i = 0; i < len; i++)
        table->buckets[i] = NULL;
    table->hash = hash;
    table->len = len;
    return table;
}
