/*
** EPITECH PROJECT, 2026
** my_llm
** File description:
** print_chained_list.c
*/

#include "my.h"

void print_chained_list(vocab_node_t *head)
{
    vocab_node_t *temp = head;

    if (!head)
        return;
    while (temp) {
        printf("%i: %s\n", temp->id, temp->token);
        temp = temp->next;
    }
}
