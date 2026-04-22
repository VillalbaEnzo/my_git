/*
** EPITECH PROJECT, 2026
** minishell2 [WSL: Ubuntu]
** File description:
** comparisons
*/
#include "cmd_array.h"
#include "utils.h"

int is_operator(char *token)
{
    for (int i = 0; operators[i] != NULL; i++) {
        if (my_strcmp(token, operators[i]) == 0)
            return 1;
    }
    return 0;
}

int is_symbol(char *token)
{
    for (int i = 0; symbols[i] != NULL; i++) {
        if (my_strcmp(token, symbols[i]) == 0)
            return 1;
    }
    return 0;
}
