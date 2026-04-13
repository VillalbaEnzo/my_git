/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-minishell2-7 [WSL: Ubuntu-24.04]
** File description:
** handle_redirection.c
*/

#include "my.h"

static int handle_redirect_stdout(char **cmds, int i)
{
    int fd = 0;

    if (my_strcmp(cmds[i], ">") == 0 && cmds[i + 1]) {
        fd = open(cmds[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (fd < 0) {
            write(2, cmds[i + 1], my_strlen(cmds[i + 1]));
            print_error(": Permission denied.\n", 21);
            return -1;
        }
        dup2(fd, 1);
        close(fd);
        return 1;
    }
    return 0;
}

static int handle_redirect_stdout_append(char **cmds, int i)
{
    int fd = 0;

    if (my_strcmp(cmds[i], ">>") == 0 && cmds[i + 1]) {
        fd = open(cmds[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
        if (fd < 0) {
            write(2, cmds[i + 1], my_strlen(cmds[i + 1]));
            print_error(": Permission denied.\n", 21);
            return -1;
        }
        dup2(fd, 1);
        close(fd);
        return 1;
    }
    return 0;
}

static int handle_redirect_stdin(char **cmds, int i)
{
    int fd[2];

    if (my_strcmp(cmds[i], "<") == 0 && cmds[i + 1]) {
        fd[0] = open(cmds[i + 1], O_RDONLY);
        if (fd[0] < 0) {
            write(2, cmds[i + 1], my_strlen(cmds[i + 1]));
            print_error(": No such file or directory.\n", 29);
            return -1;
        }
        dup2(fd[0], 0);
        close(fd[0]);
        return 1;
    }
    return 0;
}

static void read_heredoc(char *delim, int write_fd)
{
    char *line = NULL;
    size_t len = 0;

    while (1) {
        if (isatty(0))
            write(1, "? ", 2);
        if (getline(&line, &len, stdin) == -1)
            break;
        if (my_strncmp(line, delim, my_strlen(delim)) == 0 &&
            line[my_strlen(delim)] == '\n')
            break;
        write(write_fd, line, my_strlen(line));
    }
    if (line)
        free(line);
}

static int handle_heredoc(char **cmds, int i)
{
    int fd[2];

    if (my_strcmp(cmds[i], "<<") == 0 && cmds[i + 1]) {
        pipe(fd);
        read_heredoc(cmds[i + 1], fd[1]);
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
        return 1;
    }
    return 0;
}

static int check_and_apply(char **cmds, int i)
{
    int ret = 0;

    ret = handle_redirect_stdout(cmds, i);
    if (ret != 0)
        return ret;
    ret = handle_redirect_stdout_append(cmds, i);
    if (ret != 0)
        return ret;
    ret = handle_redirect_stdin(cmds, i);
    if (ret != 0)
        return ret;
    ret = handle_heredoc(cmds, i);
    return ret;
}

int handle_redirection(char **cmds)
{
    int cut_index = -1;
    int ret = 0;

    for (int i = 0; cmds[i]; i++) {
        ret = check_and_apply(cmds, i);
        if (ret == -1)
            return 0;
        if (ret == 1 && cut_index == -1)
            cut_index = i;
    }
    if (cut_index != -1)
        cmds[cut_index] = NULL;
    return 1;
}
