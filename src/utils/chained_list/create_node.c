/*
** EPITECH PROJECT, 2026
** my_llm
** File description:
** create_node.c
*/

#include "my.h"

vocab_node_t *create_node(vocab_node_t *head, int id, const char *token)
{
    vocab_node_t *temp = NULL;
    vocab_node_t *new_node = malloc(sizeof(vocab_node_t));

    if (!new_node)
        return NULL;
    new_node->id = id;
    new_node->token = strdup(token);
    if (!new_node->token)
    {
        free(new_node);
        return NULL;
    }
    new_node->next = NULL;
    if (!head)
        return new_node;
    temp = head;
    while (temp->next)
        temp = temp->next;
    temp->next = new_node;
    return head;
}
