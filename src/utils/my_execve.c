/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-minishell2-7 [WSL: Ubuntu-24.04]
** File description:
** my_execve.c
*/

#include "my.h"

void my_execve(char **cmd, char **env)
{
    execve(cmd[0], cmd, env);
    if (errno == EACCES) {
        write(2, cmd[0], my_strlen(cmd[0]));
        write(2, ": Permission denied.\n", 21);
        exit(126);
    } else if (errno == ENOEXEC) {
        write(2, cmd[0], my_strlen(cmd[0]));
        write(2, ": Exec format error. Wrong Architecture.\n", 41);
        exit(1);
    } else {
        write(2, cmd[0], my_strlen(cmd[0]));
        write(2, ": Command not found.\n", 21);
    }
    exit(1);
}
