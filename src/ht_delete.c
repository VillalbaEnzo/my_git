/*
** EPITECH PROJECT, 2025
** Secured
** File description:
** ht_delete.c
*/

#include "hashtable.h"
#include "my.h"

int check_error(hashtable_t *ht, char *key)
{
    int index = 0;

    if (!ht || !key)
        return -1;
    index = ((unsigned int)ht->hash(key, ht->len)) % ht->len;
    if (!ht->buckets[index])
        return -1;
    return index;
}

entry_t *delete_first_node(entry_t *head)
{
    entry_t *keeper = head->next;

    free(head->key);
    free(head->value);
    free(head);
    head = keeper;
    return head;
}

void delete_other_node(entry_t *node)
{
    entry_t *keeper = node->next->next;

    free(node->next->key);
    free(node->next->value);
    free(node->next);
    node->next = keeper;
}

int ht_delete(hashtable_t *ht, char *key)
{
    int index = 0;
    entry_t *temp = NULL;

    index = check_error(ht, key);
    if (index == -1)
        return 84;
    if (!my_strcmp(key, ht->buckets[index]->key)) {
        ht->buckets[index] = delete_first_node(ht->buckets[index]);
        return 0;
    }
    for (temp = ht->buckets[index]; temp->next != NULL; temp = temp->next) {
        if (!my_strcmp(key, temp->next->key)) {
            delete_other_node(temp);
            return 0;
        }
    }
    return 84;
}
