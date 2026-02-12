/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-minishell1-5
** File description:
** printenv.c
*/

#include "my.h"

void print_env(char **cmd, node_t *head)
{
    node_t *temp = head;

    if (!head || !cmd || !cmd[0] || cmd[1])
        return;
    while (temp) {
        mini_printf("%s\n", temp->line);
        temp = temp->next;
    }
}
