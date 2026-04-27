/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** alias.c
*/

#include "mysh.h"
#include "builtin.h"
#include "utils.h"

static alias_t *add_alias(alias_t *head, char *name, char *val)
{
    alias_t *tmp = head;
    alias_t *new = NULL;

    while (tmp) {
        if (my_strcmp(tmp->name, name) == 0) {
            free(tmp->value);
            tmp->value = val;
            return head;
        }
        if (!tmp->next)
            break;
        tmp = tmp->next;
    }
    new = malloc(sizeof(alias_t));
    new->name = my_strdup(name);
    new->value = val;
    new->next = NULL;
    if (tmp)
        tmp->next = new;
    return tmp ? head : new;
}

static char *get_alias_val(char **args)
{
    int len = 0;
    char *res = NULL;

    for (int i = 2; args[i]; i++)
        len += my_strlen(args[i]) + 1;
    res = my_calloc(len, sizeof(char));
    if (!res)
        return NULL;
    for (int i = 2; args[i]; i++) {
        my_strcat(res, args[i]);
        if (args[i + 1])
            my_strcat(res, " ");
    }
    return res;
}

static void print_aliases(alias_t *head)
{
    while (head) {
        mini_printf(1, "%s\t%s\n", head->name, head->value);
        head = head->next;
    }
}

int alias(args_t *args)
{
    char *val = NULL;

    if (!args->args[1]) {
        print_aliases(args->data->aliases);
        return 0;
    }
    if (!args->args[2])
        return 0;
    val = get_alias_val(args->args);
    args->data->aliases = add_alias(args->data->aliases, args->args[1], val);
    return 0;
}
