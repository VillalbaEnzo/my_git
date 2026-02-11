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

//passer en char **
char *handle_path(node_t *head, char *cmd)
{
    char *path = NULL;

    if (!head || !cmd)
        return;
    if (type_dir(cmd))
        return cmd;
    path = get_path(head, cmd);
    path = find_in_path(path, cmd);
    return;
}
