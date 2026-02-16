/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-minishell1-5
** File description:
** unsetenv.c
*/

#include "my.h"

static void remove_node(node_t **head, node_t *tmp, node_t *prev)
{
    if (prev)
        prev->next = tmp->next;
    else
        *head = tmp->next;
    if (*head && !tmp->next)
        (*head)->end = prev;
    free(tmp->line);
    free(tmp);
}

void unset_env(char **cmd, shell_t *shell)
{
    node_t *tmp = shell->env;
    node_t *prev = NULL;

    if (!cmd || !cmd[1]) {
        write(2, "unsetenv: Too few arguments.\n", 29);
        return;
    }
    while (tmp) {
        if (my_strncmp(tmp->line, cmd[1], my_strlen(cmd[1])) == 0 &&
            tmp->line[my_strlen(cmd[1])] == '=') {
            remove_node(&shell->env, tmp, prev);
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }
}
