/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-42sh-2 [WSL: Ubuntu-24.04]
** File description:
** add_local_var.c
*/

#include "mysh.h"

static local_var_t *create_local_var(char *name, char *value)
{
    local_var_t *temp = malloc(sizeof(local_var_t));

    if (!temp)
        return NULL;
    temp->name = name;
    temp->value = value;
    temp->next = NULL;
    return temp;
}

static void update_local_var(local_var_t *node, char *name, char *value)
{
    free(node->value);
    node->value = value;
    free(name);
}

local_var_t *add_local_var(local_var_t *head, char *name, char *value)
{
    local_var_t *temp = head;
    local_var_t *last = NULL;
    local_var_t *new_node = NULL;

    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            update_local_var(temp, name, value);
            return head;
        }
        last = temp;
        temp = temp->next;
    }
    new_node = create_local_var(name, value);
    if (!new_node)
        return head;
    if (last == NULL)
        return new_node;
    last->next = new_node;
    return head;
}
