/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** unalias.c
*/

#include "mysh.h"
#include "builtin.h"
#include "utils.h"

static void free_one_alias(alias_t *head)
{
    free(head->name);
    free(head->value);
    free(head);
}

static alias_t *remove_alias(alias_t *head, alias_t *prev, alias_t *curr)
{
    if (prev == NULL)
        head = curr->next;
    else
        prev->next = curr->next;
    free_one_alias(curr);
    return head;
}

static alias_t *del_one_alias(alias_t *head, const char *str)
{
    alias_t *curr = head;
    alias_t *prev = NULL;

    while (curr) {
        if (curr->name && my_strcmp(curr->name, str) == 0)
            return remove_alias(head, prev, curr);
        prev = curr;
        curr = curr->next;
    }
    return head;
}

int unalias(args_t *args)
{
    if (!args->args[1]) {
        mini_printf(2, "unalias: Too few arguments.\n");
        return 1;
    }
    for (int i = 1; args->args[i]; i++)
        args->data->aliases = del_one_alias(args->data->aliases,
            args->args[i]);
    return 0;
}
