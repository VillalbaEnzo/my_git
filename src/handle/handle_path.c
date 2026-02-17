/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-bsminishell1-6
** File description:
** handle_cmd.c
*/

#include "my.h"

static int type_dir(char *cmd)
{
    for (int i = 0; cmd[i]; i++) {
        if (cmd[i] == '/')
            return 1;
    }
    return 0;
}

void handle_path(shell_t *shell, char **cmd)
{
    char *path = NULL;
    char *abs_path = NULL;

    if (!shell->env || !cmd || !cmd[0] || type_dir(cmd[0]))
        return;
    path = get_path(shell->env, cmd[0]);
    if (!path)
        return;
    abs_path = find_in_path(path, cmd[0]);
    if (abs_path) {
        free(cmd[0]);
        cmd[0] = abs_path;
    }
}
