/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-bsminishell1-6
** File description:
** get_path.c
*/

#include "my.h"

char *get_path(node_t *head, char *cmd)
{
    node_t *temp = head;

    while (temp) {
        if (my_strncmp(temp->line, "PATH=", 5) == 0)
            return temp->line + 5;
        temp = temp->next;
    }
    return NULL;
}
