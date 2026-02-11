/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-bsminishell1-6
** File description:
** sh.c
*/

#include "my.h"

static int exit_sh(char **cmd, ssize_t ret)
{
    if ((cmd[0] && my_strcmp(cmd[0], "exit") == 0) || ret == -1) {
        free_double_buf(cmd);
        return 1;
    }
    return 0;
}

int handle_sh(node_t *head, char **env)
{
    size_t len = 0;
    ssize_t ret;
    char **cmd = NULL;
    char *line = NULL;

    while (1) {
        mini_printf("$> ");
        ret = getline(&line, &len, stdin);
        cmd = str_to_tab(line);
        handle_path(head, cmd[0]);
        if (exit_sh(cmd, ret))
            break;
        free_double_buf(cmd);
    }
    free(line);
    return 0;
}
