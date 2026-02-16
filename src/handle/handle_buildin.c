/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-minishell1-5
** File description:
** handle_buildin.c
*/

#include "my.h"

void handle_buildins(char **cmd, int build, shell_t *shell)
{
    if (!cmd || !cmd[0])
        return;
    if (build == 0)
        print_env(cmd, shell);
    if (build == 1)
        set_env(cmd, shell);
    if (build == 2)
        unset_env(cmd, shell);
    if (build == 3)
        my_cd(cmd, shell);
}
