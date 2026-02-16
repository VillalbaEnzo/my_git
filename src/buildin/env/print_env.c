/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-minishell1-5
** File description:
** printenv.c
*/

#include "my.h"

void print_env(char **cmd, shell_t *shell)
{
    node_t *temp = shell->env;

    if (!shell->env || !cmd || !cmd[0])
        return;
    if (cmd[1]) {
        write(2, "env: ‘", 9);
        write(2, cmd[1], my_strlen(cmd[1]));
        write(2, "’: No such file or directory\n", 32);
        return;
    }
    while (temp) {
        mini_printf("%s\n", temp->line);
        temp = temp->next;
    }
}
