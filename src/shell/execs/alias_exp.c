/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** alias_exp.c
*/

#include "mysh.h"
#include "utils.h"

static int get_arr_size(char **arr)
{
    int i = 0;

    while (arr && arr[i])
        i++;
    return i;
}

static char **create_new_args(char **a_toks, char **args)
{
    int s1 = get_arr_size(a_toks);
    int s2 = get_arr_size(args);
    char **new_a = my_calloc(s1 + s2, sizeof(char *));
    int pos = 0;

    if (!new_a)
        return NULL;
    for (int i = 0; a_toks[i]; i++) {
        new_a[pos] = my_strdup(a_toks[i]);
        pos++;
    }
    for (int i = 1; args[i]; i++) {
        new_a[pos] = my_strdup(args[i]);
        pos++;
    }
    return new_a;
}

void expand_aliases(ast_cmd_t *cmd, data_t *data)
{
    alias_t *tmp = data->aliases;
    char **a_toks = NULL;
    char **new_args = NULL;

    if (!cmd || !cmd->arguments || !cmd->arguments[0])
        return;
    while (tmp) {
        if (my_strcmp(tmp->name, cmd->arguments[0]) == 0) {
            a_toks = str_to_token_array_delim(tmp->value, ' ');
            new_args = create_new_args(a_toks, cmd->arguments);
            free_array((void **)cmd->arguments);
            cmd->arguments = new_args;
            free_array((void **)a_toks);
            return;
        }
        tmp = tmp->next;
    }
}
