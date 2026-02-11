/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-bsminishell1-6
** File description:
** get_env.c
*/

#include "my.h"

int get_env(char **env, node_t *head)
{
    for (int i = 0; env[i]; i++)
        head = add_node(head, env[i]);
    if (!head)
        return 0;
    return 1;
}
