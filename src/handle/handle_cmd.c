/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-bsminishell1-6
** File description:
** handle_cmd.c
*/

#include "my.h"

void handle_path(node_t *head, char *cmd)
{
    char *path = NULL;

    if (!head || !cmd)
        return;
    path = get_path(head, cmd);
    find_in_path(path, cmd);
}
