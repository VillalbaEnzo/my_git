/*
** EPITECH PROJECT, 2026
** cpsh
** File description:
** inits data
*/
#include "mysh.h"

data_t *init_data(char **envp, local_var_t *local_var)
{
    data_t *temp = malloc(sizeof(data_t));

    if (!temp)
        return NULL;
    temp->root = NULL;
    temp->tokens = NULL;
    temp->local_vars = local_var;
    temp->envp = envp;
    return temp;
}
