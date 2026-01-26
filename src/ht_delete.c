/*
** EPITECH PROJECT, 2025
** Secured
** File description:
** ht_delete.c
*/

#include "hashtable.h"
#include "my.h"

void delete_first_node(entry_t **head)
{
    free((*head)->key);
    free((*head)->value);
    *head = (*head)->next;
}

void delete_other_node(entry_t **node)
{
    entry_t *keeper = (*node)->next->next;

    free((*node)->next->key);
    free((*node)->next->value);
    free((*node)->next);
    *node = keeper;
}

int ht_delete(hashtable_t *ht, char *key)
{
    int index = 0;
    int match_found = 0;
    entry_t *temp = NULL;

    if (!ht || !ht->buckets[index] || !key)
        return 84;
    index = ((unsigned int)ht->hash(key, ht->len)) % ht->len;
    if (!my_strcmp(key, ht->buckets[index]->key)) {
        delete_first_node(&(ht->buckets[index]));
        return 0;
    }
    for (temp = ht->buckets[index]; temp != NULL; temp = temp->next) {
        if (my_strcmp(key, temp->next->key)) {
            match_found = 1;
            delete_other_node(&temp);
        }
    }
    if (!match_found)
        return 84;
    return 0;
}
