/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-bsminishell1-6
** File description:
** free_list.c
*/

#include "my.h"

void free_list(node_t *head)
{
    node_t *tmp;

    while (head) {
        tmp = head->next;
        if (head->line)
            free(head->line);
        free(head);
        head = tmp;
    }
}
