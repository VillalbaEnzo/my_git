/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-minishell2-7 [WSL: Ubuntu-24.04]
** File description:
** handle_redirection.c
*/

#include "my.h"

static int handle_redirect_stdout(char **cmds, int fd, int i)
{
    if (my_strcmp(cmds[i], ">") == 0 && cmds[i + 1]) {
        fd = open(cmds[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
        dup2(fd, 1);
        cmds[i] = NULL;
        return 1;
    }
    return 0;
}

static int handle_redirect_stdout_append(char **cmds, int fd, int i)
{
    if (my_strcmp(cmds[i], ">>") == 0 && cmds[i + 1]) {
        fd = open(cmds[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
        dup2(fd, 1);
        cmds[i] = NULL;
        return 1;
    }
    return 0;
}

static int handle_redirect_stdin(char **cmds, int fd, int i)
{
    if (my_strcmp(cmds[i], "<") == 0 && cmds[i + 1]) {
        fd = open(cmds[i + 1], O_RDONLY);
        dup2(fd, 0);
        cmds[i] = NULL;
        return 1;
    }
    return 0;
}

void handle_redirection(char **cmds)
{
    int fd = 0;

    for (int i = 0; cmds[i]; i++) {
        if (handle_redirect_stdout(cmds, fd, i))
            return;
        if (handle_redirect_stdout_append(cmds, fd, i))
            return;
        if (handle_redirect_stdin(cmds, fd, i))
            return;
    }
}
