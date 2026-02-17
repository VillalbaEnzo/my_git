/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-bsminishell1-6
** File description:
** main.c
*/

#include "my.h"

int main(int ac, char **av, char **env)
{
    shell_t shell = {NULL, NULL, 0, 0, NULL};

    if (!get_env(env, &shell))
        return 84;
    handle_sh(&shell);
    free_list(shell.env);
    return shell.last_status;
}
