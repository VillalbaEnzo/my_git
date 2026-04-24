/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-42sh-2 [WSL: Ubuntu-24.04]
** File description:
** unset.c
*/

#include "mysh.h"
#include "builtin.h"
#include "utils.h"

static void free_one_node(local_var_t *head)
{
    free(head->name);
    free(head->value);
    free(head);
}

static local_var_t *remove_node(local_var_t *head, local_var_t *prev,
    local_var_t *curr)
{
    if (prev == NULL)
        head = curr->next;
    else
        prev->next = curr->next;
    free_one_node(curr);
    return head;
}

static local_var_t *del_one_node(local_var_t *head, const char *str)
{
    local_var_t *curr = head;
    local_var_t *prev = NULL;

    while (curr) {
        if (curr->name && strcmp(curr->name, str) == 0)
            return remove_node(head, prev, curr);
        prev = curr;
        curr = curr->next;
    }
    return head;
}

int unset(args_t *args)
{
    for (int i = 1; args->args[i]; i++)
        args->data->local_vars = del_one_node(args->data->local_vars,
            args->args[i]);
    return 0;
}
