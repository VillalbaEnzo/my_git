/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-42sh-2 [WSL: Ubuntu-24.04]
** File description:
** add_local_var.c
*/

#include "mysh.h"

local_var_t *add_local_var(local_var_t *head, char *name, char *value)
{
    local_var_t *new_node = malloc(sizeof(local_var_t));
    local_var_t *temp = NULL;

    if (!new_node)
        return head;
    new_node->name = name;
    new_node->value = value;
    new_node->next = NULL;
    if (head == NULL)
        return new_node;
    temp = head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = new_node;
    return head;
}
