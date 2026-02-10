/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-bsminishell1-6
** File description:
** main.c
*/

#include "my.h"

int main(int ac, char **av, char **env)
{
    node_t *head = NULL;
    char *line = NULL;

    // if (!get_env(env, head))
        // return 84;
    handle_sh(line, env);
    free(line);
    free_list(head);
    return 0;
}
