/*
** EPITECH PROJECT, 2026
** 42sh [WSL: Ubuntu]
** File description:
** quote_rem
*/

#include "mysh.h"

static bool quote_rem_needed(char *arg)
{
    for (int i = 0; arg[i] != '\0'; i++) {
        if (arg[i] == '\'' || arg[i] == '"')
            return true;
    }
    return false;
}

static size_t get_unquoted_size(char *to_mod)
{
    size_t count = 0;

    for (int i = 0; to_mod[i] != '\0'; i++) {
        if (to_mod[i] != '\'' && to_mod[i] != '"')
            count++;
    }
    return count;
}

static char *remove_quote(char *to_mod)
{
    size_t new_size = get_unquoted_size(to_mod);
    char *new_arg = malloc(sizeof(char) * (new_size + 1));
    int pos_holder = 0;

    if (!new_arg)
        return NULL;
    for (int i = 0; to_mod[i] != '\0'; i++) {
        if (to_mod[i] != '\'' && to_mod[i] != '"') {
            new_arg[pos_holder] = to_mod[i];
            pos_holder++;
        }
    }
    new_arg[new_size] = '\0';
    free(to_mod);
    return new_arg;
}

char **quote_removal(char **args)
{
    for (int i = 0; args[i] != NULL; i++) {
        if (quote_rem_needed(args[i]))
            args[i] = remove_quote(args[i]);
        if (args[i] == NULL) {
            free_array((void **)args);
            return NULL;
        }
    }
    return args;
}
