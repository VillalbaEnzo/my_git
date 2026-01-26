/*
** EPITECH PROJECT, 2025
** Secured
** File description:
** ht_insert.c
*/

#include "hashtable.h"
#include "my.h"

static entry_t *create_node(char *key, char *value)
{
    entry_t *node = malloc(sizeof(entry_t));

    if (!node)
        return NULL;
    node->value = my_strdup(value);
    if (!node->value) {
        free(node);
        return NULL;
    }
    node->key = my_strdup(key);
    if (!node->key) {
        free(node->value);
        free(node);
        return NULL;
    }
    node->next = NULL;
    return node;
}

static int update_node(entry_t *node, char *value)
{
    char *temp = my_strdup(value);

    if (!temp)
        return 84;
    free(node->value);
    node->value = temp;
    return 0;
}

int ht_insert(hashtable_t *ht, char *key, char *value)
{
    int index = 0;
    entry_t *temp = NULL;
    entry_t *new_node = NULL;

    if (!ht || !key || !value)
        return 84;
    index = ((unsigned int)ht->hash(key, ht->len)) % ht->len;
    temp = ht->buckets[index];
    while (temp) {
        if (my_strcmp(temp->key, key) == 0)
            return update_node(temp, value);
        temp = temp->next;
    }
    new_node = create_node(key, value);
    if (!new_node)
        return 84;
    new_node->next = ht->buckets[index];
    ht->buckets[index] = new_node;
    return 0;
}
