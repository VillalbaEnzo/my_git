/*
** EPITECH PROJECT, 2026
** my_llm
** File description:
** free_list.c
*/

#include "my.h"

void free_list(vocab_node_t *head)
{
    vocab_node_t *temp;

    while (head) {
        temp = head;
        head = head->next;
        free(temp->token);
        free(temp);
    }
}
