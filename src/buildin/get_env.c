/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-bsminishell1-6
** File description:
** get_env.c
*/

#include "my.h"

int get_env(char **env, shell_t *shell)
{
    for (int i = 0; env[i]; i++)
        shell->env = add_node(shell->env, my_strdup(env[i]));
    if (!shell->env)
        return 0;
    return 1;
}
